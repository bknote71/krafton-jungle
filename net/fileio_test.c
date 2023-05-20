#include <stdio.h>

int main()
{
    FILE *fp = fopen("./http/mypath/hello.html", "r");
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c", c);
    }

    fseek(fp, 0, SEEK_SET);

    printf("\n-------------------------\n");
    char buffer[30000];
    fread(buffer, 1, 30000, fp);
    printf("%s\n", buffer);

    fclose(fp);

    return 0;
}