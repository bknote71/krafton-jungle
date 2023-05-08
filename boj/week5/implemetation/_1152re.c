#include <stdio.h>
#include <string.h>

char *trim(char *str)
{
    // 앞의 공백 제거
    while (*str != '\0' && *str == ' ')
        ++str;
    // str 끝의 문자열 포인팅
    char *end = str + strlen(str) - 1;
    while (end > str && *end == ' ')
        --end;
    *(end + 1) = 0;
    return str;
}

// 중요: char *str; 처음 선언 시 할당된 공간이 없다.
// 이런 상황에서 scanf 로 바로 입력을 받으려고 하면 오류가 발생한다.
// 왜? 할당된 공간이 없기 때문.
// 마찬가지로 strcpy 같은 연산에서도 에러가 발생한다.
// 하려면 할당된 공간이 존재하는 str 포인터로 해야한다.
char istr[1000000];

int main()
{
    scanf("%[^\n]", istr);

    // char *result 는 이미 할당되어있는 istr 공간을 가리킨다.
    char *result = trim(istr);
    int cnt = *result == '\0' ? 0 : 1;
    while (*result != '\0')
        cnt += (*result++ == ' ');
    printf("%d\n", cnt);
    return 0;
}