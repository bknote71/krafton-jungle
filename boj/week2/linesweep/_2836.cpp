#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> vt;

    for (int i = 0, a, b; i < N; ++i)
    {
        cin >> a >> b;
        if (a > b)
        {
            vt.push_back({ b, a });
        }
    }

    sort(vt.begin(), vt.end());

    int left = 0, right = 0;
    ll ret = 0;
    for (int i = 0; i < vt.size(); ++i)
    {
        if (right < vt[i].first)
        {
            ret += 2 * (ll)(right - left);
            left = vt[i].first;
        }
        right = max(right, vt[i].second);
    }
    ret += 2 * (ll)(right - left);
    cout << ret + M << '\n';

    return 0;
}