#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const int inf = 2000000000;

int cache[16][66000];
int n;
int W[16][16];

int dp(int idx, int bit)
{
    if (bit == (1 << n) - 1)
        return W[idx][0] != 0 ? W[idx][0] : inf;
    int &ret = cache[idx][bit];
    if (ret != -1)
        return ret;
    ret = inf;
    for (int i = 0; i < n; ++i)
    {
        if ((bit & (1 << i)) == 0 && W[idx][i])
        {
            ret = min(ret, W[idx][i] + dp(i, bit | (1 << i)));
        }
    }
    return ret;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> W[i][j];
    memset(cache, -1, sizeof(cache));
    cout << dp(0, 1) << '\n';
    return 0;
}