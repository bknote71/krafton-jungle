#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, l;
    cin >> n >> l;

    // first: 값, second: index,
    // first를 기준으로 민 힙 << 반대로 해야한다.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> vt;
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        pq.push({ t, i });
        int value = t;

        while (!pq.empty())
        {
            pair<int, int> top = pq.top();
            value = top.first;
            if (i >= l - 1 && top.second < i - l + 1)
                pq.pop();
            else
            {
                break;
            }
        }

        vt.push_back(value);
    }
    for (int i = 0; i < vt.size(); ++i)
    {
        cout << vt[i] << ' ';
    }
    return 0;
}