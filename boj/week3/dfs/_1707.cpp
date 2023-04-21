#include <iostream>

using namespace std;

vector<int> vt[20001];
int vst[20001];

void dfs(int cur)
{
    for (int i = 0; i < vt[cur].size(); ++i)
    {
        int next = vt[cur][i];
        if (next != 0 && !vst[next])
        {
            vst[next] = true;
            dfs(next);
        }
    }
}

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int v, e;
        cin >> v >> e;

        for (int i = 1; i < v + 1; ++i)
            vt[i].clear();

        memset(vst, 0, sizeof(vst));

        // count == 2 인지 확인

        for (int i = 0; i < e; ++i)
        {
            int a, b;
            cin >> a >> b;
            vt[a].push_back(b);
            vt[b].push_back(a);
        }

        int cand = 0;
        for (int i = 1; i < v + 1; ++i)
        {
            if (!vst[i])
            {
                ++cand;
                dfs(i);
            }
        }
        cout << (cand == 2 ? "YES" : "NO") << '\n';
    }
    return 0;
}