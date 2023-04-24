#include <iostream>
#include <queue>

using namespace std;

vector<int> v[301];
int indeg[301];
int ret[301];

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            char t;
            cin >> t;

            if (t == '1')
            {
                v[j].push_back(i);
                ++indeg[i];
            }
        }

    priority_queue<int> pq;

    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0)
            pq.push(i);
    int m = n;
    while (!pq.empty())
    {
        int top = pq.top();
        pq.pop();

        ret[top] = m--;
        for (auto next : v[top])
        {
            if (--indeg[next] == 0)
                pq.push(next);
        }
    }

    if (m != 0)
    {
        cout << -1 << '\n';
    }
    else
    {
        for (int i = 0; i < n; ++i)
            cout << ret[i] << ' ';
    }

    return 0;
}