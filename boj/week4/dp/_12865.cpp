#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int dp[100][100001];
int n, k;

struct bag
{
    int w, v;
};

vector<bag> vt;

int solve(int idx, int put)
{
    if (idx == n || put == 0)
        return 0;
    int &ret = dp[idx][put];
    if (ret != -1)
        return ret;
    ret = solve(idx + 1, put);
    if (put - vt[idx].w >= 0)
        ret = max(ret, solve(idx + 1, put - vt[idx].w) + vt[idx].v);
    return ret;
}

int main()
{
    cin >> n >> k;
    vt.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> vt[i].w >> vt[i].v;
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(0, k) << '\n';
    return 0;
}