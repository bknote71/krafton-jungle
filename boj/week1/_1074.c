#include <math.h>
#include <stdio.h>

int Z(int n, int r, int c)
{
    if (n == 0)
        return 1;

    int ret = 0, powpow = pow(2, n - 1);
    // printf("%d %d %d %d\n", n, r, c, powpow);
    if (r < powpow && c < powpow)
    {
        return Z(n - 1, r, c);
    }
    else
    {
        ret += powpow * powpow;
    }

    if (r < powpow && c >= powpow)
    {
        return ret + Z(n - 1, r, c - powpow);
    }
    else
    {
        ret += powpow * powpow;
    }
    if (r >= powpow && c < powpow)
    {
        printf("%d %d %d\n", n, r, c);
        return ret + Z(n - 1, r - powpow, c);
    }
    else
    {
        ret += powpow * powpow;
    }

    if (r >= powpow && c >= powpow)
    {
        return ret + Z(n - 1, r - powpow, c - powpow);
    }
    return 0;
}

int main()
{
    int N, r, c;
    scanf("%d %d %d", &N, &r, &c);

    printf("%d\n", Z(N, r, c) - 1);
    return 0;
}