#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<pair<int, int>> vt[101];
int indeg[101];
int sum[101];

int main()
{
    int n, m;

    cin >> n;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;

        vt[a].push_back({ b, c });
        indeg[b]++;
    }

    // node, cost
    vector<pair<int, int>> ret;
    queue<pair<int, int>> q;
    q.push({ n, 1 });
    while (!q.empty())
    {
        int curr = q.front().first;
        int w = q.front().second;
        q.pop();

        if (vt[curr].size() == 0)
        {
            ret.push_back({ curr, w });
            continue;
        }

        for (auto p : vt[curr])
        {
            int next = p.first;
            int k = p.second;

            sum[next] += w * k;

            if (--indeg[next] == 0)
                q.push({ next, sum[next] });
        }
    }

    sort(ret.begin(), ret.end());

    for (auto next : ret)
        cout << next.first << ' ' << next.second << '\n';

    return 0;
}