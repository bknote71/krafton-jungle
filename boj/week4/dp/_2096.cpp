#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    int tx[3];
    int mindp[3][2] = { 0 };
    int maxdp[3][2] = { 0 };
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> tx[j];
            mindp[j][(i + 1) % 2] = tx[j] + min(mindp[1][i % 2], (j != 1 ? mindp[j][i % 2] : min(mindp[0][i % 2], mindp[2][i % 2])));
            maxdp[j][(i + 1) % 2] = tx[j] + max(maxdp[1][i % 2], (j != 1 ? maxdp[j][i % 2] : max(maxdp[0][i % 2], maxdp[2][i % 2])));
        }
    }

    cout << max({ maxdp[0][n % 2], maxdp[1][n % 2], maxdp[2][n % 2] })
         << ' ' << min({ mindp[0][n % 2], mindp[1][n % 2], mindp[2][n % 2] }) << '\n';

    return 0;
}