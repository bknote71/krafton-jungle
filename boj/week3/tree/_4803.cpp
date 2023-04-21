#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

vector<int> vt[500];
bool vst[500];
bool fnsh[500];

bool dfs(int cur, int before)
{
    vst[cur] = true;
    for (auto next : vt[cur])
    {
        if (next == before)
            continue;
        if (vst[next])
            return false;
        if (!dfs(next, cur))
            return false;
    }
    return true;
}

int main()
{
    int cnt = 0;
    while (true)
    {
        memset(vst, 0, sizeof(vst));
        int n, m;
        cin >> n >> m;

        if (n == 0 && m == 0)
            break;

        for (int i = 0; i < n; ++i)
            vt[i].clear();

        for (int i = 0; i < m; ++i)
        {
            int a, b;
            cin >> a >> b;
            a--, b--;
            vt[a].push_back(b);
            vt[b].push_back(a);
        }
        int ret = 0;

        for (int i = 0; i < n; ++i)
        {
            if (!vst[i])
                ret += dfs(i, -1);
        }
        printf("Case %d: ", ++cnt);
        if (ret == 0)
            cout << "No Trees" << '\n';
        else if (ret == 1)
            cout << "There is one tree." << '\n';
        else
            cout << "A forest of " << ret << " trees." << '\n';
    }
    return 0;
}