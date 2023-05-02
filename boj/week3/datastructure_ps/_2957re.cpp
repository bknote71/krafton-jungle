#include <iostream>
#include <map>
#include <set>

using namespace std;

map<int, long long> depth;
set<int> vst;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long cnt = 0, n;
    cin >> n;

    int minnode, maxnode;
    int mind, maxd;
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        if (i == 0)
        {
            maxnode = minnode = t;
            mind = maxd = 0;
            vst.insert(t);
            depth.insert({ t, 0 });
        }
        else
        {
            auto lower = vst.lower_bound(t);
            auto upper = vst.upper_bound(t);
            int d = 0;
            if (minnode > t)
            {
                d = mind;
            }
            else if (upper == vst.end())
            {
                d = maxd;
            }
            else
            {
                --lower;
                d = max(depth.find(*lower)->second, depth.find(*upper)->second);
            }
            if (minnode > t)
            {
                minnode = t;
                mind = d + 1;
            }
            if (maxnode < t)
            {
                maxnode = t;
                maxd = d + 1;
            }

            vst.insert(t);
            depth.insert({ t, d + 1 });
            cnt += d + 1;
        }

        printf("%lld\n", cnt);
    }

    return 0;
}