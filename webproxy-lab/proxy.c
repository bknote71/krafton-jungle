#include "csapp.h"
#include <pthread.h>
#include <stdio.h>

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
#define NTHREADS 20

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr =
    "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 "
    "Firefox/10.0.3\r\n";

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *host, char *port, char *filename, char *cgiargs);
void get_filetype(char *filename, char *filetype);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg,
                 char *longmsg);
void request_upstream(int fd, char *uri, char *port, char *filename);
void read_responsehdrs(rio_t *rp, char *data);
void serve_upstreamfile(int fd, char *filename, int filesize);

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER;
int in, out, count;

int buffer[1024];
const int capacity = 1024;

void put(int fd);
int take();
void *thread(void *vargp);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    pthread_t tid[NTHREADS];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    /* Check command line args */
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    listenfd = Open_listenfd(argv[1]);

    for (int i = 0; i < NTHREADS; ++i) /* Create worker threads */
        Pthread_create(&tid[i], NULL, thread, NULL);

    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr,
                        &clientlen); // line:netp:tiny:accept
        Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE,
                    0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
        put(connfd);
    }
}

void doit(int fd)
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char host[MAXLINE], port[MAXLINE], filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    printf("Request headers:\n");
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);
    if (strcasecmp(method, "GET")) // 0 이 아니라면 == 다르다면
    {
        clienterror(fd, method, "501", "Not implemented", "Tiny does not implement this method");
        return;
    }
    // 필요한 헤더?
    printf("read_request hdrs\n\n");
    read_requesthdrs(&rio);

    /* Parse URI from GET request */
    is_static = parse_uri(uri, host, port, filename, cgiargs);
    printf("host: %s, port: %s, filename: %s\n", host, port, filename);
    char fname[MAXLINE] = { 0 };
    strcpy(fname, ".");
    strcat(fname, filename);
    if (stat(fname, &sbuf) < 0)
    {
        // 파일이 없으면 원 서버에 요청
        printf("새로 생성\n");
        request_upstream(fd, host, port, filename);
    }
    else if (is_static)
    {
        // 파일이 있으면? If-Modified-Since 추가
        printf("기존\n");
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) // 무슨 에러죠?
        {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't read the file");
            return;
        }
        printf("file date: %s", ctime(&sbuf.st_ctime));
        serve_upstreamfile(fd, fname, sbuf.st_size);
    }
    else
    { /* Serve dunamic content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode))
        {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program");
            return;
        }
    }
}

void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
    char buf[MAXLINE], body[MAXLINE];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor="
                  "ffffff"
                  ">\r\n",
            body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web Server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}

void read_requesthdrs(rio_t *rp)
{
    char buf[MAXLINE];
    Rio_readlineb(rp, buf, MAXLINE);
    while (strcmp(buf, "\r\n"))
    {
        Rio_readlineb(rp, buf, MAXLINE);
        printf("%s", buf);
    }
    return;
}

int parse_uri(char *uri, char *host, char *port, char *filename, char *cgiargs)
{
    printf("parse uri: %s\n", uri);
    char *ptr;
    char org[MAXLINE] = { 0 };
    if (!strstr(uri, "cgi-bin")) /* Static content */
    {
        // 여기서 우선은 원서버:숫자 를 제거해야 한다.
        strcpy(cgiargs, "");
        strcpy(filename, "/");
        sscanf(uri, "http://%[^:]:%[^/]/%s", host, port, org);
        if (strlen(port) == 0)
            strcpy(port, 80);
        if (strlen(org) == 0)
            strcat(filename, "home.html");
        else
            strcat(filename, org);
        return 1;
    }
    else /* Dynamic content */
    {
        ptr = index(uri, "?");
        if (ptr)
        {
            strcpy(cgiargs, ptr + 1);
            *ptr = '\0';
        }
        else
            strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}

void get_filetype(char *filename, char *filetype)
{
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".png"))
        strcpy(filetype, "image/png");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else
        strcpy(filetype, "text/plain");
}

void request_upstream(int fd, char *host, char *port, char *filename)
{
    int srcfd, clientfd;
    char *srcp, buf[MAXBUF];
    char status[MAXLINE], date[MAXLINE], body[MAXLINE], fname[MAXLINE];
    rio_t rio;
    ssize_t n;

    sprintf(buf, "GET %s HTTP/1.1\r\n", filename);
    sprintf(buf, "%sConnection: close\r\n", buf);
    sprintf(buf, "%sAccept: */*\r\n", buf);
    sprintf(buf, "%sAccept-Encoding: gzip, deflate\r\n\r\n", buf);
    printf("buf: \n%s\n", buf);

    // connect
    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
    // request
    Rio_writen(clientfd, buf, strlen(buf));
    Rio_readlineb(&rio, buf, MAXLINE);
    printf("Response headers:\n");
    printf("%s", buf);
    sscanf(buf, "%*s %s %*s", status);

    if (strcmp(status, "404") == 0)
    {
        clienterror(fd, filename, "404", "Not found", "Tiny couldn't find this file");
        return;
    }
    read_responsehdrs(&rio, date);
    // 이제부터 본문
    // 계속 read 하면서 파일에 쓰기
    strcpy(fname, ".");
    strcat(fname, filename);
    printf("fname: %s\n", fname);
    FILE *fp = fopen(fname, "w");
    // Rio_readlineb(&rio, body, MAXLINE);
    while ((n = Rio_readlineb(&rio, body, MAXLINE)) > 0)
    {
        // 바디 데이터 처리 로직
        // 여기서는 단순히 출력만 수행하도록 예시로 작성되었습니다.
        fwrite(body, sizeof(char), n, fp);
    }
    fclose(fp);
    // 본문
    // 전송 후 쓰기작업
    struct stat sbuf;
    int x = stat(fname, &sbuf);
    serve_upstreamfile(fd, fname, sbuf.st_size);
}

// status: 200 이였을 때 Date 받아오기
// status: 300 이면? 필요 없음
void read_responsehdrs(rio_t *rp, char *date)
{
    char buf[MAXLINE];
    Rio_readlineb(rp, buf, MAXLINE);
    while (strcmp(buf, "\r\n"))
    {
        if (strstr(buf, "Date:"))
        {
            sscanf(buf, "Date: %[^\r\n]", date);
            printf("date!!: %s\n", date);
        }
        Rio_readlineb(rp, buf, MAXLINE);
        printf("%s", buf);
    }
    return;
}

void serve_upstreamfile(int fd, char *filename, int filesize)
{
    printf("filename:?? %s\n", filename);
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Proxy Web Server\r\n", buf);
    sprintf(buf, "%sConnection: close\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));
    printf("My Response headers:\n");
    printf("%s", buf);

    srcfd = Open(filename, O_RDONLY, 0);
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
}

void put(int fd)
{
    // buffer 요소와 count에 대한 락
    pthread_mutex_lock(&m);
    while (count == capacity)
        pthread_cond_wait(&notfull, &m);
    buffer[in] = fd;
    in = (in + 1) % capacity;
    count++;
    pthread_cond_signal(&notempty);
    pthread_mutex_unlock(&m);
}

int take()
{
    int data;
    pthread_mutex_lock(&m);
    while (count == 0)
        pthread_cond_wait(&notempty, &m);
    data = buffer[out];
    out = (out + 1) % capacity;
    count--;

    pthread_cond_signal(&notfull);
    pthread_mutex_unlock(&m);
    return data;
}

void *thread(void *vargp)
{
    Pthread_detach(pthread_self());
    for (;;)
    {
        int connfd = take();
        doit(connfd);
        Close(connfd); // line:netp:tiny:close
    }
}