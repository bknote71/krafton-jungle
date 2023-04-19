#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<long long> arr;
vector<long long> A, B;

void dfs(int l, int r, vector<long long> &vt, long long sum)
{
    if (l > r)
    {
        vt.push_back(sum);
        return;
    }

    dfs(l + 1, r, vt, sum);
    dfs(l + 1, r, vt, sum + arr[l]);
}

int main()
{
    int N, S;
    cin >> N >> S;

    arr.resize(N);
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    dfs(0, N / 2, A, 0);
    dfs(N / 2 + 1, N - 1, B, 0);

    sort(B.begin(), B.end());

    long long ret = 0;
    for (int i = 0; i < A.size(); i++)
    {
        auto upper = upper_bound(B.begin(), B.end(), S - A[i]);
        auto lower = lower_bound(B.begin(), B.end(), S - A[i]);
        ret += upper - lower;
    }
    cout << ret - (S == 0) << '\n';
}