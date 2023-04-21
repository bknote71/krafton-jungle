#include <iostream>
#include <queue>

using namespace std;

char arr[100][100];
int vst[100][100];

int dr[4] = { 1, 0, -1, 0 };
int dc[4] = { 0, 1, 0, -1 };

struct point
{
    int r, c, d;
};

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> arr[i][j];

    queue<point> q;
    q.push({ 0, 0, 1 });
    vst[0][0] = 1;

    int ret;
    while (!q.empty())
    {
        point p = q.front();
        q.pop();

        if (p.r == n - 1 && p.c == m - 1)
        {
            ret = p.d;
            break;
        }

        for (int d = 0; d < 4; ++d)
        {
            int nr = p.r + dr[d];
            int nc = p.c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                continue;
            if (vst[nr][nc])
                continue;
            if (arr[nr][nc] == '0')
                continue;

            vst[nr][nc] = 1;
            q.push({ nr, nc, p.d + 1 });
        }
    }

    cout << ret << '\n';

    return 0;
}