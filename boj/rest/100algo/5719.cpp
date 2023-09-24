#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int inf = 1000000000;

int vt[501][501];
int dist[501];

int main()
{
    while (true)
    {
        int n, m, S, D;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;

        // init
        for (int i = 0; i < n; ++i)
        {
            dist[i] = inf;
            for (int j = 0; j < n; ++j)
                vt[i][j] = 0;
        }

        cin >> S >> D;

        for (int i = 0; i < m; ++i)
        {
            int u, v, p;
            cin >> u >> v >> p;
            vt[u][v] = p;
        }

        // 최소 힙: (greader)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, S });
        dist[S] = 0;

        while (!pq.empty())
        {
            pair<int, int> p = pq.top();
            pq.pop();
            int d = p.first * -1; // 가중치
            int u = p.second;     // 현재 위치

            // 기존 방식: 최단 거리
            if (dist[u] < d)
                continue;

            for (int v = 0; v < n; ++v)
            {
                // 다음 위치
                int nd = vt[u][v];
                if (dist[v] > dist[u] + nd)
                {
                    dist[v] = dist[u] + nd;
                    pq.push({ -dist[v], v });
                }
            }
        }

        // 최단 경로를 제외해야 함
        int vst[501];
        memset(vst, 0, sizeof(vst));
        queue<int> q;
        q.push(D);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            for (int u = 0; u < n; ++u)
            {
                int d = vt[u][v];
                if (dist[u] + d == dist[v]) // 경로 제거
                {
                    vt[u][v] = 0;
                }

                if (!vst[u])
                {
                    q.push(u);
                    vst[u] = true;
                }
            }
        }
    }
    return 0;
}