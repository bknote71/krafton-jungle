#include <iostream>

using namespace std;

int arr[3000][3000];
int cnt[3]; // -1 , 0, 1 --> 0 1 2

bool check_all_same(int r, int c, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (arr[i + r][j + c] != arr[r][c])
                return false;

    return true;
}

void solve(int r, int c, int n)
{
    if (n == 1)
    {
        cnt[arr[r][c] + 1]++;
        return;
    }
    if (!check_all_same(r, c, n))
    {
        int nunint = n / 3;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                solve(r + nunint * i, c + nunint * j, nunint);
            }
        }
        return;
    }
    cnt[arr[r][c] + 1]++;
    return;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            cin >> arr[i][j];
    }

    solve(0, 0, n);

    for (int i = 0; i < 3; ++i)
        cout << cnt[i] << '\n';

    return 0;
}