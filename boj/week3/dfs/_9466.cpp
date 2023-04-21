#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int vst[100001];
int fsh[100001];
int cnt, ret;

int g[100001];

void dfs(int node)
{
    vst[node] = ++cnt;
    int next = g[node];
    if (!vst[next])
        dfs(next);
    else if (!fsh[next])
        ret += vst[node] - vst[next] + 1;

    fsh[node] = true;
}

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        memset(vst, 0, sizeof(vst));
        memset(fsh, 0, sizeof(fsh));
        cnt = 0;
        ret = 0;

        int n;
        cin >> n;

        for (int i = 1; i < n + 1; ++i)
        {
            int x;
            cin >> x;
            g[i] = x;
        }

        for (int i = 1; i < n + 1; ++i)
        {
            if (!fsh[i])
            {
                dfs(i);
            }
        }
        cout << n - ret << '\n';
    }
    return 0;
}