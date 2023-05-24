#include <arpa/inet.h>
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

int main()
{
    char hostname[40] = "yes24.com";
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0)
    {
        perror("Failed to resolve hostname");
        exit(1);
    }

    struct sockaddr_in *server_addr = (struct sockaddr_in *)res->ai_addr;
    char *ip_address = inet_ntoa(server_addr->sin_addr);

    int proxyfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in upserver;
    memset(&upserver, 0, sizeof(upserver));
    upserver.sin_family = AF_INET;
    upserver.sin_port = htons(PORT);
    upserver.sin_addr.s_addr = inet_addr(ip_address);

    // if (inet_pton(AF_INET, ip_address, &(upserver.sin_addr)) <= 0)
    // {
    //     perror("Invalid address or address not supported");
    //     exit(1);
    // }

    if (connect(proxyfd, (struct sockaddr *)&upserver, sizeof(upserver)) != 0)
    {
        printf("connection with the upserver failed...\n");
    }
    else
        printf("connected to the upserver..\n");

    char request[20000] = "GET http://yes24.com/ HTTP/1.1\r\n"
                          "User-Agent: PostmanRuntime/7.32.2\r\n"
                          "Accept: */*\r\n"
                          "Postman-Token: e3dd1e51-d663-474d-98f7-f3842894bf53\r\n"
                          "Host: yes24.com\r\n"
                          "Accept-Encoding: gzip, deflate, br\r\n"
                          "Connection: keep-alive\r\n\r\n";

    printf("request: \n%s\n", request);

    write(proxyfd, request, sizeof(request));
    char response[30000] = { 0 };
    int n = read(proxyfd, response, sizeof(response));
    printf("readn: %d, response: \n%s\n", n, response);

    freeaddrinfo(res); // 반드시 free해야함!
    close(proxyfd);
    return 0;
}