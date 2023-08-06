#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> vt[100001];
int n, a, b;
int total_legnth, max_length;
bool dfs_total_length(int cur, int prev, int sum)
{
    if (cur == b)
    {
        total_legnth = sum;
        return true;
    }
    for (auto next : vt[cur])
    {
        int next_node = next.first;
        if (next_node == prev)
            continue;
        if (dfs_total_length(next_node, cur, sum + next.second))
        {
            max_length = max(max_length, next.second);
            return true;
        }
    }
    return false;
}

int main()
{

    cin >> n >> a >> b;
    a--, b--;
    for (int i = 0; i < n - 1; ++i)
    {
        int s, e, c;
        cin >> s >> e >> c;
        s--, e--;
        vt[s].push_back({ e, c });
        vt[e].push_back({ s, c });
    }

    // a to b
    // 1. total_length 를 구한다.
    dfs_total_length(a, -1, 0);
    // 2. 가장 큰 길이를 구한다

    cout << total_legnth - max_length << '\n';

    return 0;
}