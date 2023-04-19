#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

pair<int, int> jewl[300001];
int n, k;
int bag[300001];

int main()
{
    cin >> n >> k;

    for (int i = 0; i < n; ++i)
    {
        cin >> jewl[i].first >> jewl[i].second;
    }

    for (int i = 0; i < k; ++i)
        cin >> bag[i];

    sort(jewl, jewl + n);
    sort(bag, bag + k);

    // 기본 맥스힙?
    priority_queue<int> pq;

    long long ret = 0, idx = 0;
    for (int i = 0; i < k; ++i)
    {
        while ((idx < n) && (jewl[idx].first <= bag[i]))
            pq.push(jewl[idx++].second);
        if (!pq.empty())
        {
            ret += (long long)pq.top();
            pq.pop();
        }
    }
    cout << ret << '\n';

    return 0;
}