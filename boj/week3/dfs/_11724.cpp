#include <iostream>

using namespace std;

int box[1001][1001];
bool vst[1001];
int N, M;

void dfs(int cur)
{
    for (int i = 1; i < N + 1; ++i)
    {
        if (!vst[i] && box[cur][i])
        {
            vst[i] = true;
            dfs(i);
        }
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < M; ++i)
    {
        int u, v;
        cin >> u >> v;

        box[u][v] = 1;
        box[v][u] = 1;
    }

    int ret = 0;
    for (int i = 1; i < N + 1; ++i)
    {
        if (!vst[i])
        {
            ++ret;
            dfs(i);
        }
    }

    cout << ret << '\n';

    return 0;
}