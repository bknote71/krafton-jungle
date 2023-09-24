#include <stdio.h>
#include <string.h>

#define MAXLINE 10000

int main()
{
    char host[MAXLINE], port[MAXLINE], filename[MAXLINE];
    const char *str = "http://localhost:80";
    sscanf(str, "http://%[^:]:%[^/]/%s", host, port, filename);
    printf("host: %s, port: %s, filename: %s\n", host, port, filename);
    printf("hlen: %d, plen: %d, flen: %d\n", strlen(host), strlen(port), strlen(filename));
    return 0;
}