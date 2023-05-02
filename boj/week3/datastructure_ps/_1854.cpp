#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

vector<pair<int, int>> vt[1001];
priority_queue<int> ret[1001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        vt[a].push_back({ b, c });
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({ 0, 1 });
    ret[1].push(0);

    while (!pq.empty())
    {
        int d = pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        for (auto np : vt[cur])
        {
            int next = np.first;
            int nd = d + np.second;
            if (ret[next].size() < k)
            {
                ret[next].push(nd);
                pq.push({ nd, next });
            }
            else
            {
                if (ret[next].top() > nd)
                {
                    ret[next].pop();
                    ret[next].push(nd);
                    pq.push({ nd, next });
                }
            }
        }
    }

    for (int i = 1; i < n + 1; ++i)
    {
        if (ret[i].size() < k)
            cout << "-1" << '\n';
        else
            cout << ret[i].top() << '\n';
    }

    return 0;
}