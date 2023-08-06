#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int NODE = 32001;

vector<int> vt[NODE];
int indeg[NODE];

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        vt[a].push_back(b);
        indeg[b]++;
    }

    // 가능하면 쉬운 문제: 최소 힙!!
    // pq 는 기본적으로 최대힙이다 !! <<
    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 1; i < n + 1; ++i)
        if (!indeg[i])
            q.push(i);

    while (!q.empty())
    {
        int cur = q.top();
        q.pop();

        cout << cur << ' ';

        for (auto next : vt[cur])
        {
            if (--indeg[next] == 0)
                q.push(next);
        }
    }

    return 0;
}