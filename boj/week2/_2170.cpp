#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int, int>> vt(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> vt[i].first >> vt[i].second;
    }

    sort(vt.begin(), vt.end());

    int left, right, ret = 0;
    left = right = vt[0].first;

    for (int i = 0; i < n; ++i)
    {
        if (right < vt[i].first)
        {
            ret += right - left;
            left = vt[i].first;
        }
        right = max(right, vt[i].second);
    }

    ret += right - left;
    cout << ret << '\n';

    return 0;
}