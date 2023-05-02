#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> vt(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> vt[i].second >> vt[i].first;
    }

    sort(vt.begin(), vt.end());

    int ret = 0, pe = -1;
    for (int i = 0; i < n; ++i)
    {
        if (pe <= vt[i].second)
        {
            ret++;
            pe = vt[i].first;
        }
    }

    cout << ret << '\n';

    return 0;
}