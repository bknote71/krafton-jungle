#include <iostream>

using namespace std;

long long arr[100001];

int main()
{
    int n, m, lo = 0;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        lo = arr[i] > lo ? arr[i] : lo;
    }

    lo--;

    long long hi = 1000000000;

    while (lo + 1 < hi)
    {
        long long mid = (lo + hi) >> 1;

        // cmp 함수
        int cnt = 1;
        long long sum = 0;

        for (int i = 0; i < n; ++i)
        {
            if (sum + arr[i] > mid)
            {
                cnt++;
                sum = 0;
            }

            sum += arr[i];
        }

        if (cnt > m)
            lo = mid;
        else
            hi = mid;
    }

    cout << hi << '\n';

    return 0;
}
