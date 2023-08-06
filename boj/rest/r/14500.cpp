#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, -1, 0, 1 };

int arr[500][500];
int vst[500][500];
int minf = -1000000000;
int n, m;
int solve(int r, int c, int num) // 가운데 튀나온거 제외
{
    if (num == 1)
        return arr[r][c];
    vst[r][c] = true;
    int maxvalue = 0;
    for (int d = 0; d < 4; ++d)
    {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m || vst[nr][nc])
            continue;
        maxvalue = max(maxvalue, solve(nr, nc, num - 1) + arr[r][c]);
    }
    vst[r][c] = false;
    return maxvalue;
}

int tr[4][4] = { { 0, 0, 0, 1 }, { 0, 1, 2, 1 }, { 0, 0, 0, -1 }, { 0, -1, 0, 1 } };
int tc[4][4] = { { 0, 1, 2, 1 }, { 0, 0, 0, 1 }, { 0, 1, 2, 1 }, { 0, 1, 1, 1 } };

int solve2(int r, int c)
{
    int maxvalue = 0;
    for (int d = 0; d < 4; ++d)
    {
        int cand = 0;
        for (int t = 0; t < 4; ++t)
        {
            int nr = r + tr[d][t];
            int nc = c + tc[d][t];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
            {
                cand = -1;
                break;
            }
            cand += arr[nr][nc];
        }
        if (cand != -1)
            maxvalue = max(maxvalue, cand);
    }
    return maxvalue;
}

int main()
{
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &arr[i][j]);

    int maxvalue = 0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            maxvalue = max(maxvalue, solve(i, j, 4));
            maxvalue = max(maxvalue, solve2(i, j));
        }
    printf("%d\n", maxvalue);

    return 0;
}

/*
    maxvalue = solve(r + 1, c, num - 1);
    maxvalue = max(maxvalue, solve(r, c + 1, num - 1));
    maxvalue = max(maxvalue, solve(r + 1, c, 1) + solve(r, c + 1, num - 2));
    maxvalue = max(maxvalue, solve(r + 1, c, num - 2) + solve(r, c + 1, 1));
    maxvalue = max(maxvalue, solve(r - 1, c, num - 1));
*/