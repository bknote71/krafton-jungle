#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

int dp[500][500], n, arr[500][500];

int solve(int idx, int prev)
{
    if (idx == n)
        return 0;

    int &ret = dp[idx][prev];
    if (ret != -1)
        return ret;

    // 가운데
    ret = solve(idx + 1, prev) + arr[idx][prev];

    // // 대각선 왼쪽
    // if (prev > 0)
    //     ret = max(ret, solve(idx + 1, prev - 1) + arr[idx][prev - 1]);

    // 대각선 오른쪾
    if (prev < idx)
        ret = max(ret, solve(idx + 1, prev + 1) + arr[idx][prev + 1]);

    return ret;
}

int main()
{
    memset(dp, -1, sizeof(dp));

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i + 1; ++j)
        {
            cin >> arr[i][j];
        }
    }

    cout << solve(0, 0) << '\n';

    return 0;
}