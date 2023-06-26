#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int asum[1001];
int bsum[1001];
vector<int> vt;

int main()
{
    ll T, n, m;
    cin >> T;

    cin >> n;
    for (ll i = 1, t; i < n + 1; ++i)
    {
        cin >> t;
        asum[i] = asum[i - 1] + t;
    }

    cin >> m;
    for (ll i = 1, t; i < m + 1; ++i)
    {
        cin >> t;
        bsum[i] = bsum[i - 1] + t;
    }

    ll acnt = 0, bcnt = 0;

    // for (int i = 1; i < n + 1; ++i)
    //     for (int j = i; j < n + 1; ++j)
    //         aarr[acnt++] = asum[j] - asum[i - 1];

    for (int i = 1; i < m + 1; ++i)
        for (int j = i; j < m + 1; ++j)
            vt.push_back(bsum[j] - bsum[i - 1]);

    sort(vt.begin(), vt.end());

    ll ret = 0;

    for (ll i = 1; i < n + 1; ++i)
    {
        for (ll j = i; j < n + 1; ++j)
        {
            ll target = T - (asum[j] - asum[i - 1]);
            // lower bound
            ll lo = -1, hi = vt.size();
            while (lo + 1 < hi)
            {
                ll mid = (lo + hi) / 2;
                if (vt[mid] >= target)
                    hi = mid;
                else
                    lo = mid;
            }

            // upper bound
            ll ulo = -1, uhi = vt.size();
            while (ulo + 1 < uhi)
            {
                ll mid = (ulo + uhi) / 2;
                if (vt[mid] > target)
                    uhi = mid;
                else
                    ulo = mid;
            }
            ret += (uhi - hi);

            // auto lower = lower_bound(vt.begin(), vt.end(), target);
            // auto upper = upper_bound(vt.begin(), vt.end(), target);
            // ret += (upper - lower);
        }
    }
    cout << ret << '\n';

    return 0;
}