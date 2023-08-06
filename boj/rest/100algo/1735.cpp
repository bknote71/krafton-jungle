#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int inf = 1000000000;

int main()
{
    int v, e, k;
    cin >> v >> e;
    cin >> k;

    vector<pair<int, int>> vt[20001];
    int dist[20001];

    for (int i = 0; i < e; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        vt[a].push_back({ b, c });
    }

    // -dist, node (최대 힙): dist가 가장 작은 것을 선택
    fill(dist, dist + v, inf);

    priority_queue<pair<int, int>> pq;
    pq.push({ 0, --k });
    dist[k] = 0;

    while (!pq.empty())
    {
        pair<int, int> p = pq.top();
        int d = p.first * -1;
        int n = p.second;
        pq.pop();

        if (dist[n] < d)
            continue;

        for (auto next : vt[n])
        {
            int nn = next.first;
            int nd = next.second;

            if (dist[nn] > d + nd)
            {
                dist[nn] = d + nd;
                pq.push({ -dist[nn], nn });
            }
        }
    }

    for (int i = 0; i < v; ++i)
    {
        if (dist[i] == inf)
            cout << "INF" << '\n';
        else
            cout << dist[i] << '\n';
    }

    return 0;
}