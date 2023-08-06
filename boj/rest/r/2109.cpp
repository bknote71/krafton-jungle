#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> vt[10001];

int main()
{
    int n, maxp = 0;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int d, p;
        cin >> d >> p;
        vt[p].push_back(d);
        maxp = max(maxp, p);
    }

    priority_queue<int, vector<int>, less<int>> pq; // 강연료 큰 순
    int ret = 0;
    for (int i = maxp; i > 0; --i)
    {
        if (!vt[i].empty())
        {
            for (int j = 0; j < vt[i].size(); ++j)
                pq.push(vt[i][j]);
        }
        // pq 에서 가장 큰 값 선택
        if (!pq.empty())
        {
            ret += pq.top();
            pq.pop();
        }
    }

    cout << ret << '\n';
    return 0;
}