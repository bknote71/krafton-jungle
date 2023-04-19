#include <functional>
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

int main()
{
    int k, n;
    cin >> k >> n;

    vector<ll> vt(k);
    priority_queue<ll, vector<ll>, greater<ll>> pq;

    for (int i = 0; i < k; ++i)
    {
        cin >> vt[i];
        pq.push(vt[i]);
    }

    int top;

    while (n--)
    {
        for (int i = 0; i < k; ++i)
        {
            top = pq.top();
            pq.push(vt[i] * top);

            if (top % vt[i] == 0)
                break;
        }

        if (!pq.empty())
            pq.pop();
    }

    cout << top << '\n';

    return 0;
}