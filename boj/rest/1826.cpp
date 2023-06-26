#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct point
{
    int a;
    int b;

    bool operator<(const point &p) const
    {
        return a < p.a;
    }
};

point arr[10001];
int fuel[1000001];

int main()
{
    int n, L, P;
    cin >> n;
    for (int i = 0, a, b; i < n; ++i)
    {
        cin >> a >> b;
        arr[i] = { a, b };
        fuel[a] = b;
    }

    sort(arr, arr + n);

    cin >> L >> P;

    priority_queue<int, vector<int>, less<int>> pq;
    int ret = 0, limit = P;
    for (int i = 0; i < L; ++i)
    {
        if (fuel[i] > 0)
            pq.push(fuel[i]);
        if (i == limit)
        {
            if (pq.empty())
            {
                printf("-1\n");
                return 0;
            }
            ++ret;
            limit += pq.top();
            pq.pop();
        }
    }

    cout << ret << '\n';

    return 0;
}