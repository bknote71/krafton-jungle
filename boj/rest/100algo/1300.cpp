#include <iostream>

using namespace std;

int main()
{
    int n, k;

    cin >> n >> k;

    int lo = 0, hi = n * n;

    while (lo + 1 < hi)
    {
        int mid = (lo + hi) >> 1;
        long long sum = 0;
        for (int i = 1; i < n + 1; ++i)
        {
            sum += min((mid) / i, n); // 나보다 작은 것들을 모두 더한다.
        }

        if (sum >= k)
            hi = mid;
        else
            lo = mid;
    }

    cout << hi << '\n';

    return 0;
}