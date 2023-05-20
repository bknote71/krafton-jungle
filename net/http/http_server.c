#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 1024
#define RESPONSESIZE 30000
#define BODYSIZE 20000
#define PORT 80

typedef struct httpheader
{
    char *name;
    char *value;
} httpheader;

typedef struct httprequest
{
    char *method;
    char *uri;
    char *version;
    struct httpheader headers[20];
    int header_size;
    char *body;
} httprequest;

void error(const char *msg)
{
    fputs(msg, stderr);
    exit(1);
}

httprequest *create_request()
{
    httprequest *req = (httprequest *)malloc(sizeof(struct httprequest));
    req->header_size = 0;
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

    request->method = strtok_r(line, " ", &start);
    request->uri = strtok_r(NULL, " ", &start);
    request->version = strtok_r(NULL, " ", &start);

    // header
    int idx = 0;
    while (line)
    {
        line = strtok_r(NULL, newline, &saveptr);
        hname = strtok_r(line, ":", &hvalue);
        request->headers[idx].name = hname;
        request->headers[idx++].value = hvalue;
        if (line != NULL && strncmp(saveptr, blankline, strlen(blankline)) == 0)
            break;
    }
    request->header_size = idx;
    request->body = saveptr + 3;

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
    char response[RESPONSESIZE];
    char body[BODYSIZE];
    for (;;)
    {
        memset(buf, 0, sizeof(buf));
        memset(response, 0, sizeof(response));
        memset(body, 0, sizeof(body));

        clilen = sizeof(cli);
        connfd = accept(sockfd, (struct sockaddr *)&cli, &clilen);
        n = read(connfd, buf, sizeof(buf));
        // parse
        httprequest *request = parse_request(buf);

        char statusline[100];
        char contenttype[100];

        // basic response header
        sprintf(statusline, "%s %d %s\r\n", request->version, 200, "OK");
        strcat(response, statusline);
        // sprintf(contenttype, "Content-Length:  %d\r\n", sizeof(body) - 1);
        // strcat(response, contenttype);
        strcat(response, "Date: Sat, 20 May 2023 09:50:53 GMT\r\n");
        strcat(response, "Content-Type: text/html; charset=UTF-8\r\n");
        strcat(response, "Connection: close\r\n");

        strcat(response, newline);
        // html file io
        // FILE
        char path[100] = "./mypath";
        strcat(path, request->uri);
        FILE *fp = fopen(path, "r");
        if (fp == NULL)
        {
            printf("파일을 열 수 없습니다. response 404 error\n");
        }

        fread(body, 1, BODYSIZE, fp);
        strcat(response, body);

        printf("response: %s\n", response);
        write(connfd, response, strlen(response));

        // close
        free(request);
        fclose(fp);
        close(connfd);
    }
    close(sockfd);

    return 0;
}