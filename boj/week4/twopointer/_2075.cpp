#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n * n; ++i)
    {
        int t;
        cin >> t;
        if (pq.size() < n)
            pq.push(t);
        else if (pq.top() < t)
        {
            pq.pop();
            pq.push(t);
        }
    }

    cout << pq.top() << '\n';

    return 0;
}