#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct cmp
{
    bool operator()(int a, int b)
    {
        return a > b; // 작은 값이 우선순위가 높음
    }
};

int main()
{
    // 기본이 min heap 인가연?
    priority_queue<int, vector<int>, cmp> pq;

    int n;
    cin >> n;

    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        pq.push(t);
    }

    int ret = 0;
    while (!pq.empty())
    {
        int left = pq.top();
        pq.pop();

        if (pq.empty())
            break;

        int right = pq.top();
        pq.pop();

        int sum = left + right;
        ret += sum;
        pq.push(sum);
    }

    cout << ret << '\n';

    return 0;
}