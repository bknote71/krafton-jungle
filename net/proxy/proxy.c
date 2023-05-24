#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 30000
#define RESPONSESIZE 30000
#define BODYSIZE 20000
#define PORT 8090

typedef struct httpheader
{
    char *name;
    char *value;
} httpheader;

typedef struct httprequest
{
    // char *method;
    char *uri;
    // char *version;
    // struct httpheader headers[20];
    // int header_size;
    // char *body;
    char *hostname;
} httprequest;

void error(const char *msg)
{
    fputs(msg, stderr);
    exit(1);
}

httprequest *create_request()
{
    httprequest *req = (httprequest *)malloc(sizeof(struct httprequest));
    // req->header_size = 0;
    return req;
}

const char blankline[] = "\n\r";
const char newline[] = "\r\n";

httprequest *parse_request(const char *http)
{
    httprequest *request;
    request = create_request();

    char *line, *saveptr;
    char *start;
    char *hname, *hvalue;
    line = strtok_r(http, newline, &saveptr);

    strtok_r(line, " ", &start);
    request->uri = strtok_r(NULL, " ", &start);
    // request->version = strtok_r(NULL, " ", &start);

    // header
    int idx = 0;
    while (line)
    {
        line = strtok_r(NULL, newline, &saveptr);
        hname = strtok_r(line, ":", &hvalue);
        if (strcmp(hname, "Host") == 0)
            request->hostname = ++hvalue;
        if (line != NULL && strncmp(saveptr, blankline, strlen(blankline)) == 0)
            break;
    }

    return request;
}

int main()
{
    int sockfd, connfd, clilen;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error on socket()\n");

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
        error("Error on bind()\n");

    if (listen(sockfd, 5) == -1)
        error("Error on listen()\n");

    int n;
    char buf[BUFSIZE];
    char org[BUFSIZE];
    char res[BUFSIZE];
    char response[RESPONSESIZE];
    char body[BODYSIZE];
    for (;;)
    {
        memset(buf, 0, sizeof(buf));
        memset(response, 0, sizeof(response));
        memset(body, 0, sizeof(body));
        memset(org, 0, sizeof(org));
        memset(res, 0, sizeof(res));

        clilen = sizeof(cli);
        connfd = accept(sockfd, (struct sockaddr *)&cli, &clilen);
        printf("connfd: %d\n", connfd);
        n = read(connfd, buf, sizeof(buf));
        printf("readn: %d, buf: \n%s\n", n, buf);
        strcpy(org, buf);
        // parse
        httprequest *request = parse_request(buf);

        // 원래 서버에게 요청
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        printf("hostname: %s\n\n", request->hostname);

        if (getaddrinfo(request->hostname, NULL, &hints, &res) != 0)
        {
            perror("Failed to resolve hostname");
            exit(1);
        }

        struct sockaddr_in *server_addr = (struct sockaddr_in *)res->ai_addr;
        char *ip_address = inet_ntoa(server_addr->sin_addr);

        int proxyfd = socket(AF_INET, SOCK_STREAM, 0), readn;
        struct sockaddr_in upserver;
        memset(&upserver, 0, sizeof(upserver));
        upserver.sin_family = AF_INET;
        upserver.sin_port = htons(80);
        upserver.sin_addr.s_addr = inet_addr(ip_address);

        if (connect(proxyfd, (struct sockaddr *)&upserver, sizeof(upserver)) != 0)
        {
            printf("connection with the upserver failed...\n");
        }
        else
            printf("connected to the upserver..\n");

        // make http request
        write(proxyfd, org, sizeof(org));
        read(proxyfd, org, sizeof(org));
        // org[readn] = 0;
        printf("in upserver's response: \n%s\n", org);

        // response
        char statusline[100];
        char contenttype[100];

        // basic response header
        sprintf(statusline, "%s %d %s\r\n", "HTTP/1.1", 200, "OK");
        strcat(response, statusline);
        sprintf(contenttype, "Content-Length: %d\r\n", 12);
        strcat(response, contenttype);
        strcat(response, "Date: Sat, 20 May 2023 09:50:53 GMT\r\n");
        strcat(response, "Content-Type: text/html; charset=UTF-8\r\n");
        strcat(response, "Connection: close\r\n");

        strcat(response, newline);
        strcat(response, "hello world!");

        // char path[100] = "./mypath";
        // strcat(path, request->uri);
        // FILE *fp = fopen(path, "r");
        // if (fp == NULL)
        // {
        //     printf("파일을 열 수 없습니다. response 404 error\n");
        // }

        // fread(body, 1, BODYSIZE, fp);
        // strcat(response, body);

        printf("response: \n%s\n", response);
        write(connfd, response, strlen(response));

        // close
        freeaddrinfo(res);
        free(request);
        // fclose(fp);
        close(connfd);
    }
    close(sockfd);

    return 0;
}