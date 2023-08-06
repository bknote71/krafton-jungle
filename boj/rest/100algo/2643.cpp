#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

pair<int, int> arr[102];
int n;

int dp[102][102];

int solve(int idx, int prev)
{
    if (idx == n + 1)
        return 0;

    int &ret = dp[idx][prev];
    if (ret != -1)
        return ret;

    // 안넣는다.
    ret = solve(idx + 1, prev);

    if (arr[idx].first <= arr[prev].first && arr[idx].second <= arr[prev].second)
        ret = max(ret, 1 + solve(idx + 1, idx));

    return ret;
}

bool cmp(pair<int, int> &a, pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second > b.second;

    return a.first > b.first;
}

int main()
{
    memset(dp, -1, sizeof(dp));

    cin >> n;

    arr[0] = { 1001, 1001 };

    for (int i = 1; i < n + 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        if (a < b)
        {
            int temp = a;
            a = b;
            b = temp;
        }
        arr[i] = { a, b };
    }

    sort(arr, arr + n + 1, cmp);

    cout << solve(1, 0) << '\n';

    return 0;
}