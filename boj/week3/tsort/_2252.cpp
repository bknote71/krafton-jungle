#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> vt[32001];
int indeg[32001];

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        vt[a].push_back(b);
        indeg[b]++;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i)
    {
        if (indeg[i] == 0)
            q.push(i);
    }

    vector<int> ret;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        ret.push_back(cur);

        for (auto &next : vt[cur])
        {
            if (indeg[next] > 0)
            {
                if (--indeg[next] == 0)
                    q.push(next);
            }
        }
    }

    for (auto next : ret)
        cout << next + 1 << ' ';

    return 0;
}