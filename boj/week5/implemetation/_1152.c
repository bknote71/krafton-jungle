#include <stdio.h>
#include <string.h>

char str[1000000];

char *trim(char *str)
{
    // 앞의 공백 제거
    while (*str == ' ')
        ++str;
    // str 끝의 문자열 포인팅
    char *end = str + strlen(str) - 1;
    while (end > str && *end == ' ')
        --end;
    *(end + 1) = 0;
    return str;
}

int main()
{

    scanf("%[^\n]", str);
    int i = 0, len = strlen(str);
    for (; i < len; ++i)
        if (str[i] != ' ')
            break;

    int ret = 1;
    for (int j = i; j < len; ++j)
        ret += (j != len - 1 && str[j] == ' ');

    printf("%d\n", i == len ? 0 : ret);

    return 0;
}