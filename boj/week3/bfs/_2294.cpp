#include <iostream>
#include <queue>

using namespace std;

int cost[100];
bool vst[10002][10002];

int main()
{
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i)
        cin >> cost[i];

    queue<pair<int, int>> q;
    q.push({ 0, 0 });
    vst[0][0] = true;
    int ret = 0;
    while (!q.empty())
    {
        pair<int, int> p = q.front();
        q.pop();
        int c = p.first;
        int use = p.second;

        if (c == k)
        {
            ret = use;
            break;
        }

        for (int i = 0; i < n; ++i)
        {
            int ncost = c + cost[i];
            int nuse = use + 1;
            if (ncost > k)
                continue;
            if (vst[ncost][nuse])
                continue;
            vst[ncost][nuse] = true;
            q.push({ ncost, nuse });
        }
    }

    cout << ret << '\n';

    return 0;
}