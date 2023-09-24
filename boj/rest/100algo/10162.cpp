#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

// A: 5
// B: 1
// C: 10

int button[3] = { 300, 60, 10 };
int dp[10001];

const int inf = 1000000000;

int solve(int t)
{
    if (t <= 0)
        return t < 0 ? inf : 0;

    int &ret = dp[t];
    if (ret != -1)
        return ret;

    ret = inf;

    for (int i = 0; i < 3; ++i)
    {
        if (t - button[i] >= 0)
        {
            ret = min(ret, solve(t - button[i]) + 1);
        }
    }

    return ret;
}

int S[3];

void reconstruct(int t)
{
    if (t <= 0)
        return;

    for (int i = 0; i < 3; ++i)
    {
        if (t - button[i] >= 0)
        {
            int cand = solve(t - button[i]) + 1;
            if (cand == dp[t])
            {
                reconstruct(t - button[i]);
                S[i]++;
                break;
            }
        }
    }
}

int main()
{
    memset(dp, -1, sizeof(dp));
    int t;
    cin >> t;

    int ret = solve(t);

    if (ret == inf)
        cout << -1 << '\n';
    else
    {
        reconstruct(t);
        for (int i = 0; i < 3; ++i)
        {
            cout << S[i] << ' ';
        }
    }

    return 0;
}