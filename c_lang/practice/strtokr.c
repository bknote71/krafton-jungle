#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(char *argv[], int argc, char **sp)
{
    printf("sp 목표 지점: %p\n", *sp);
    int slen = 4;
    for (int i = argc - 1; i >= 0; --i)
    {
        *sp = *sp - (strlen(argv[i]) + 1);
        printf("a sp: %p\n", *sp);
        strncpy(*sp, argv[i], strlen(argv[i]) + 1);
        printf("a str: %s\n", *sp);
        slen += strlen(argv[i]) + 1;
    }

    int rm = slen % 8 == 0 ? 8 : slen % 8;
    *sp -= 8 - rm;
    memset(*sp, 0, 8 - rm);

    printf("b sp: %p\n", *sp);

    *sp -= 1;
    **sp = 0;

    printf("ac sp: %p\n", *sp);

    for (int i = argc - 1; i >= 0; --i)
    {
        uint64_t ref = (uint64_t)argv[i];
        *sp -= sizeof(char *);
        memcpy(*sp, &ref, sizeof(char *));
        printf("d sp: %p\n", *sp);
    }
    *sp -= 1;
    **sp = 0;

    printf("e sp: %p\n", *sp);

    printf("vsize: %d\n", sizeof(void (*)()));
    printf("vsize: %d\n", sizeof(uint8_t));
}

int main()
{
    char f_name[] = "/bin/ls -l foo bar";
    char *saveptr, *f;

    char *argv[6];
    int argc = 0;

    for (f = strtok_r(f_name, " ", &saveptr); f != NULL; f = strtok_r(NULL, " ", &saveptr))
    {
        argv[argc++] = f;
    }

    printf("file name: %s\n", f_name);
    printf("f name: %s\n", argv[0]);

    for (int i = 0; i < argc; ++i)
    {
        printf("arvg[%d]: %s\n", i, argv[i]);
    }

    printf("==============================\n");

    // 스택에 쌓아 보기
    for (int i = 0; i < argc; ++i)
    {
        printf("arvg[%d]주소: %d\n", i, argv[i]);
    }

    printf("==============================\n");

    char *str = (char *)malloc(sizeof(char) * 100);
    printf("str: %p\n", str);
    func(argv, argc, &str);

    return 0;
}