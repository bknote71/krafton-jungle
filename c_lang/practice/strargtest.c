#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func(char *arg)
{
    printf("arg: %p\n", arg);

    char *argv[64];
    int argc = 0;

    char *saveptr, *f;
    for (f = strtok_r(arg, " ", &saveptr); f != NULL; f = strtok_r(NULL, " ", &saveptr))
    {
        printf("f: %s\n", f);
    }

    printf("arg? %s\n", arg);
    return 0;
}

int main()
{
    func("child-simple abc def");
    return 0;
}