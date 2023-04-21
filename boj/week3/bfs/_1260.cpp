#include <iostream>
#include <queue>

using namespace std;

int box[1001][1001];
int N, M, V;

bool vst[1001];

void dfs(int cur)
{
    cout << cur << ' ';

    for (int i = 1; i < N + 1; ++i)
    {
        if (!vst[i] && box[cur][i] == 1)
        {
            vst[i] = true;
            dfs(i);
        }
    }
}

void bfs(int start)
{
    memset(vst, 0, sizeof(vst));

    queue<int> q;
    q.push(start);
    vst[start] = true;

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        cout << cur << ' ';

        for (int i = 1; i < N + 1; ++i)
        {
            if (!vst[i] && box[cur][i] == 1)
            {
                vst[i] = true;
                q.push(i);
            }
        }
    }
}

int main()
{
    cin >> N >> M >> V;
    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        box[a][b] = 1;
        box[b][a] = 1;
    }

    vst[V] = true;
    dfs(V);
    cout << '\n';
    bfs(V);

    return 0;
}