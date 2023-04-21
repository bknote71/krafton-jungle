#include <iostream>
#include <queue>

using namespace std;

const int inf = 1000000000;

int dist[1000];
vector<pair<int, int>> vt[1000];

int main()
{
    int n, m;
    cin >> n;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        vt[a].push_back({ b, c });
    }

    int s, e;
    cin >> s >> e;
    s--, e--;

    fill(dist, dist + n, inf);

    priority_queue<pair<int, int>> pq;
    pq.push({ 0, s });
    dist[s] = 0;

    while (!pq.empty())
    {
        pair<int, int> p = pq.top();
        int cur = p.second;
        int d = p.first * -1; // dist[cur] 후보
        pq.pop();

        if (dist[cur] < d)
            continue;

        for (auto &next : vt[p.second])
        {
            int ndist = next.second + d;
            if (dist[next.first] > ndist)
            {
                dist[next.first] = ndist;
                pq.push({ ndist * -1, next.first });
            }
        }
    }

    cout << dist[e] << '\n';

    return 0;
}