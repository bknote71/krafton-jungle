#include <iostream>

using namespace std;

typedef long long ll;

ll arr[10000];

int main()
{
    int n, k;
    cin >> k >> n;

    ll lo = 1, hi = 0;
    for (int i = 0; i < k; ++i)
    {
        cin >> arr[i];
        if (arr[i] > hi)
            hi = arr[i] + 1;
    }

    // TTT .... TTFF .... FFF

    while (lo + 1 < hi)
    {
        ll mid = lo + hi >> 1;
        ll cnt = 0;
        for (int i = 0; i < k; ++i)
            cnt += arr[i] / mid;

        if (cnt >= n)
            lo = mid;
        else
            hi = mid;
    }

    cout << lo << '\n';

    return 0;
}