#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const int inf = 2000000000;

int n, m;

int cache[10001][200];
int chk[10000];

int dp(int now, int x)
{
    if (now >= n - 1)
        return now == n - 1 ? 0 : inf;
    if (chk[now])
        return inf;
    int &ret = cache[now][x];
    if (ret != -1)
        return ret;
    ret = dp(now + x + 1, x + 1) + 1;
    ret = now == 0 ? ret : min(ret, 1 + dp(now + x, x));
    ret = x < 2 ? ret : min(ret, 1 + dp(now + x - 1, x - 1));
    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));
    cin >> n >> m;

    for (int i = 0, t; i < m; ++i)
    {
        cin >> t;
        chk[t - 1] = true;
    }

    int ret = dp(0, 0);
    if (ret >= inf)
        ret = -1;
    cout << ret << '\n';

    return 0;
}