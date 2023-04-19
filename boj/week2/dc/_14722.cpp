#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

ll height[100001];

ll histo(int lo, int hi)
{
    if (lo > hi)
        return 0;
    if (lo == hi)
        return height[lo];

    int mid = (lo + hi) >> 1;
    int left = mid, right = mid + 1;
    ll h = min(height[left], height[right]);
    ll area = h * 2;
    while (lo < left || right < hi)
    {
        if (right < hi && (left == lo || height[left - 1] < height[right + 1]))
        {
            h = min(h, height[++right]);
        }
        else
        {
            h = min(h, height[--left]);
        }
        area = max(area, h * (right - left + 1));
    }

    return max({ area, histo(lo, mid), histo(mid + 1, hi) });
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    memset(height, 0, sizeof(height));

    for (int i = 0; i < n; ++i)
    {
        cin >> height[i];
    }

    cout << histo(0, n - 1) << '\n';

    return 0;
}