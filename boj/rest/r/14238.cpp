#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

int cnt[3];
int dp[51][51][51][3][3];
int n;

int solve(int a, int b, int c, int pb, int pc) // pb: b가 나오면 안되는 횟수, pc: c가 나오면 안되는 횟수
{
    if (a + b + c == n)
        return true;

    int &ret = dp[a][b][c][pb][pc];
    if (ret != -1)
        return ret;

    ret = 0;

    if (a < cnt[0])
    {
        if ((ret = solve(a + 1, b, c, pb > 0 ? pb - 1 : 0, pc > 0 ? pc - 1 : 0)) == true)
        {
            cout << 'A';
            return true;
        }
    }
    if (b < cnt[1] && pb == 0)
    {
        if ((ret = solve(a, b + 1, c, 1, pc > 0 ? pc - 1 : 0)) == true)
        {
            cout << 'B';
            return true;
        }
    }
    if (c < cnt[2] && pc == 0)
    {
        if ((ret = solve(a, b, c + 1, pb > 0 ? pb - 1 : 0, 2)) == true)
        {
            cout << 'C';
            return true;
        }
    }
    return ret;
}

int main()
{
    memset(dp, -1, sizeof(dp));

    string str;
    cin >> str;

    n = str.length();

    for (int i = 0; i < n; ++i)
    {
        cnt[str[i] - 'A']++;
    }

    if (!solve(0, 0, 0, 0, 0))
        cout << -1 << '\n';

    return 0;
}

// void solve(int b, int c, int n, vector<char> &vt)
// {
//     if (n == 0)
//     {
//         // print vt
//         for (auto next : vt)
//             cout << next;
//         cout << '\n';
//         exit(0);
//     }

//     for (int i = 2; i >= 0; --i)
//     {
//         if ((i == 1 && b != 0) || (i == 2 && c != 0))
//             continue;
//         if (cnt[i] == 0)
//             continue;
//         int nb = i == 1 ? 1 : (b > 0 ? b - 1 : 0);
//         int nc = i == 2 ? 2 : (c > 0 ? c - 1 : 0);

//         cnt[i]--;
//         vt.push_back('A' + i);

//         solve(nb, nc, n - 1, vt);

//         cnt[i]++;
//         vt.pop_back();
//     }
// }