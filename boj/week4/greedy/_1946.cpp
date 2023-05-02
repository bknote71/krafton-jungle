#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<pair<int, int>> vt(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> vt[i].first >> vt[i].second;
        }

        sort(vt.begin(), vt.end());

        int p = 100001, ret = 0;
        for (int i = 0; i < n; ++i)
        {
            if (p > vt[i].second)
            {
                p = vt[i].second;
                ++ret;
            }
        }

        cout << ret << '\n';
    }
    return 0;
}