#include <cmath>
#include <iostream>

using namespace std;

int L, W, H, N;
int cube[20], flag = true;
const int inf = 2000000000;

int solve(int l, int w, int h)
{
    if (l == 0 || w == 0 || h == 0)
        return 0;

    int t = min({ l, w, h });
    int p = log2(t);

    for (int i = p; i >= 0; --i)
    {
        if (cube[i] > 0)
        {
            int P = pow(2, i);
            cube[i]--;
            return solve(l - P, P, h) + solve(l, w - P, h) + solve(P, P, h - P) + 1;
        }
    }

    printf("-1\n");
    exit(0);
}

int main()
{
    cin >> L >> W >> H;

    cin >> N;

    for (int i = 0, j; i < N; ++i)
    {
        cin >> j >> cube[j];
    }

    int ret = solve(L, W, H);
    if (flag == false)
    {
        printf("-1\n");
    }
    else
        printf("%d\n", ret);

    return 0;
}