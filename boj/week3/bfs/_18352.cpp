#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int>> vt;
bool vst[300001];

struct point
{
    int x, d;
};

int main()
{
    int n, m, k, x;
    cin >> n >> m >> k >> x;

    x--;

    vt.resize(n);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        vt[a].push_back(b);
    }

    queue<point> q;
    q.push({ x, 0 });
    vst[x] = 1;

    vector<int> ret;

    while (!q.empty())
    {
        point cur = q.front();
        q.pop();

        if (cur.d == k)
        {
            ret.push_back(cur.x + 1);
        }

        for (auto next : vt[cur.x])
        {
            if (vst[next])
                continue;
            vst[next] = true;
            q.push({ next, cur.d + 1 });
        }
    }

    if (ret.empty())
        cout << "-1" << '\n';
    else
    {
        sort(ret.begin(), ret.end());
        for (int i = 0; i < ret.size(); ++i)
            cout << ret[i] << '\n';
    }

    return 0;
}