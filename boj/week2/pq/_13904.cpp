#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n;
    cin >> n;
    pair<int, int> p[1001];
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i].first >> p[i].second;
    }

    sort(p, p + n, [](pair<int, int> &u, pair<int, int> &v)
         { return u.first > v.first; });

    int ret = 0, idx = 0;
    priority_queue<int> pq;
    for (int i = 0; i < 1000; ++i)
    {
        while ((idx < n) && (1000 - i) <= p[idx].first)
            pq.push(p[idx++].second);
        if (!pq.empty())
        {
            ret += pq.top();
            pq.pop();
        }
    }

    cout << ret << '\n';

    return 0;
}

// bool cmp(const pair<int, int> &u, const pair<int, int> &v)
// {
//     if (u.first == v.first)
//         return u.second > v.second;
//     return u.first < v.first;
// }

// int main()
// {
//     int n;
//     cin >> n;
//     vector<pair<int, int>> vt(n);
//     // 정렬 기준이 딱봐도 과제 일수가 적게 남은 순
//     // ++ 과제가 큰 수로 정렬한다.

//     for (int i = 0; i < n; ++i)
//     {
//         cin >> vt[i].first >> vt[i].second;
//     }

//     sort(vt.begin(), vt.end(), cmp);

//     int ret = 0;
//     for (int i = 0; i < n; ++i)
//     {
//         if (i > 0 && vt[i].first == vt[i - 1].first)
//             continue;
//         ret += vt[i].second;
//     }

//     cout << ret << '\n';

//     return 0;
// }
