#include <iostream>

using namespace std;

int dp[40][2000001][2], N, S;
int arr[40];

int solve(int idx, int sum, bool minus)
{
    if (idx == N)
        return sum == 0;
    int &ret = dp[idx][sum][minus];

    if (ret != -1)
        return ret;
    ret = solve(idx + 1, sum, minus);
    int nsum = sum * (minus ? -1 : 1);
    bool nminus = nsum - arr[idx] < 0;

    ret += solve(idx + 1, abs(nsum - arr[idx]), nminus);
    return ret;
}

int main()
{
    cin >> N >> S;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];
    memset(dp, -1, sizeof(dp));
    cout << solve(0, S, S < 0) - (S == 0) << '\n';

    return 0;
}
