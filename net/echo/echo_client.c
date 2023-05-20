#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

#define MAX 256
#define PORT 8080

void func(int sockfd)
{
    char buff[MAX];
    int n, readn;
    for (;;)
    {
        n = 0, readn = 0;
        memset(buff, 0, sizeof(buff));

        printf("Input message: ");
        while ((buff[n++] = getchar()) != '\n')
            ;

        if (!strcmp(buff, "exit"))
        {
            printf("exit connection\n");
            break;
        }
        write(sockfd, buff, sizeof(buff));

        readn = read(sockfd, buff, sizeof(buff));
        buff[readn] = 0;
        printf("From Echo Server : %s\n", buff);
    }
}
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    memset(&servaddr, 0, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}