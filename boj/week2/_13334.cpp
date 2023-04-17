#include <cmath>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

vector<pair<int, int>> vt;

bool cmp(pair<int, int> u, pair<int, int> v)
{
    if (u.second == v.second)
        return u.first < v.first;
    return u.second < v.second;
}

int main()
{
    int n, d;
    cin >> n;
    vt.resize(n);

    for (int i = 0, a, b; i < n; ++i)
    {
        cin >> a >> b;
        vt[i] = { min(a, b), max(a, b) };
    }
    cin >> d;

    sort(vt.begin(), vt.end(), cmp);

    priority_queue<int, vector<int>, greater<int>> pq;
    int ret = 0;
    for (int i = 0; i < n; ++i)
    {
        if (vt[i].second - vt[i].first <= d)
            pq.push(vt[i].first);

        while (!pq.empty())
        {
            if (vt[i].second - pq.top() > d)
                pq.pop();
            else
                break;
        }
        ret = max(ret, (int)pq.size());
    }

    cout << ret << '\n';

    return 0;
}