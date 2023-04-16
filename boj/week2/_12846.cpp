#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll solve(const vector<int> &money, int lo, int hi)
{
    if (lo > hi)
        return 0;
    if (lo == hi)
        return money[lo];

    int mid = (lo + hi) >> 1;
    int minMoney = min(money[mid], money[mid + 1]);
    ll ret = 2 * minMoney;

    int l = mid, r = mid + 1;
    while (lo < l || r < hi)
    {
        if (r < hi && (l == lo || money[l - 1] < money[r + 1]))
        {
            minMoney = min(minMoney, money[++r]);
        }
        else
        {
            minMoney = min(minMoney, money[--l]);
        }
        ret = max(ret, (r - l + 1) * (ll)minMoney);
    }
    return max({ ret, solve(money, lo, mid), solve(money, mid + 1, hi) });
}

int main()
{
    int n;
    cin >> n;
    vector<int> money(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> money[i];
    }

    printf("%lld\n", solve(money, 0, n - 1));

    return 0;
}