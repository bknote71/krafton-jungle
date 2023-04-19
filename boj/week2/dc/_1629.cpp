#include <stdio.h>

typedef long long ll;

ll A, B, C;

ll solve(ll x, ll y)
{
    if (y == 1)
        return x % C;
    ll t1 = solve(x, y / 2);
    return ((t1 * t1) % C * (y % 2 == 0 ? 1 : x)) % C;
}

int main()
{
    scanf("%ld %ld %ld", &A, &B, &C);
    printf("%ld\n", solve(A, B));
    return 0;
}