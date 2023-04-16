#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 1000000000;

int N;

int main()
{
    cin >> N;
    vector<int> vt(N);
    for (int i = 0, t; i < N; ++i)
    {
        cin >> t;
        vt[i] = t;
    }

    sort(vt.begin(), vt.end());
    int minValue = inf * 2;
    int left = -1, right = -1;

    for (int i = 0; i < N - 1; ++i)
    {
        int lo = i + 1, hi = N - 1, org = vt[i], neg = vt[i] < 0, to = abs(vt[i]);
        while (lo + 1 < hi)
        {
            int mid = (lo + hi) >> 1;
            if (vt[mid] < to)
                lo = mid;
            else
                hi = mid;
        }

        if (abs(org + vt[lo]) < minValue)
        {
            minValue = abs(org + vt[lo]);
            left = i;
            right = lo;
        }

        if (abs(org + vt[hi]) < minValue)
        {
            minValue = abs(org + vt[hi]);
            left = i;
            right = hi;
        }
    }
    printf("%d %d\n", vt[left], vt[right]);

    return 0;
}