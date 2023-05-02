#include <iostream>
#include <map>
#include <set>

using namespace std;

map<int, long long> depth;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long cnt = 0;
    int n;
    cin >> n;

    depth.insert({ 0, -1 });
    depth.insert({ 300001, -1 });

    int minnode, maxnode;
    int mind, maxd;
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        auto upper = depth.upper_bound(t);
        int d;
        auto lower = upper;
        --lower;

        d = max(lower->second, upper->second) + 1;
        depth.insert({ t, d });
        cnt += d;
        printf("%lld\n", cnt);
    }

    return 0;
}