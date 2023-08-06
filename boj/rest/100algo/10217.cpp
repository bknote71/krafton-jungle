#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int inf = 1000000000;

typedef struct edge
{
    int u;
    int c;
    int d;
};

struct cmp
{
    bool operator()(const edge &a, const edge &b)
    {
        return a.d > b.d;
    }
};

vector<vector<edge>> vt; // 매번 생성하는게 비용이 큰가봄??
int dist[101][10002];    //
priority_queue<edge, vector<edge>, cmp> pq;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int TC;
    cin >> TC;
    while (TC--)
    {
        int n, m, k;

        cin >> n >> m >> k;

        vt.clear();
        vt.resize(n + 1);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m + 1; ++j)
                dist[i][j] = inf;

        for (int i = 0; i < k; ++i)
        {
            int u, v, c, d;
            cin >> u >> v >> c >> d;
            u--, v--;
            vt[u].push_back({ v, c, d });
        }

        dist[0][0] = 0;
        pq.push({ 0, 0, 0 }); // 정점 비용 시간

        while (!pq.empty())
        {
            // 2 개의 상태: 다음 노드와 비용 (남은)
            edge e = pq.top();
            int d = e.d;
            pq.pop();

            if (e.u == n - 1)
                break;

            if (dist[e.u][e.c] < d)
                continue;

            for (auto &next : vt[e.u])
            {
                int nextu = next.u;
                int nextcost = next.c + e.c;
                int nextd = next.d + e.d;

                if (nextcost > m)
                    continue;
                if (dist[next.u][nextcost] <= nextd)
                    continue;

                for (int i = nextcost; i <= m; ++i)
                    if (dist[next.u][i] > nextd)
                        dist[next.u][i] = nextd;
                    else
                        break;
                pq.push({ next.u, nextcost, nextd });
            }
        }

        if (dist[n - 1][m] != inf)
            printf("%d\n", dist[n - 1][m]);
        else
            printf("Poor KCM\n");

        return 0;
    }
}