#include <iostream>
#include <queue>

using namespace std;

int tomato[101][101][101];
int vst[101][101][101];

int dr[4] = { 1, 0, -1, 0 };
int dc[4] = { 0, -1, 0, 1 };
int dh[2] = { 1, -1 };

struct point
{
    int h, r, c;
};

int main()
{
    int m, n, h;
    cin >> m >> n >> h;

    queue<point> q;

    int tcnt = 0;

    for (int k = 0; k < h; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                cin >> tomato[k][i][j];
                if (tomato[k][i][j] == 0)
                    tcnt++;
                else if (tomato[k][i][j] == 1)
                {
                    q.push({ k, i, j });
                    vst[k][i][j] = true;
                }
            }

    int day = 0;
    while (true)
    {
        queue<point> tq;
        while (!q.empty())
        {
            point p = q.front();
            q.pop();

            for (int d = 0; d < 4; ++d)
            {
                int nr = p.r + dr[d];
                int nc = p.c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                    continue;
                if (vst[p.h][nr][nc])
                    continue;
                // printf("dd %d %d %d %d %d %d\n", p.h, p.r, p.c, nr, nc, tomato[p.h][nr][nc]);
                if (tomato[p.h][nr][nc] == 0)
                {

                    vst[p.h][nr][nc] = true;
                    tomato[p.h][nr][nc] = 1;
                    tq.push({ p.h, nr, nc });
                    tcnt--;
                }
            }
            for (int i = 0; i < 2; ++i)
            {

                int nh = p.h + dh[i];
                if (nh < 0 || nh >= h)
                    continue;
                if (vst[nh][p.r][p.c])
                    continue;
                if (tomato[nh][p.r][p.c] == 0)
                {
                    vst[nh][p.r][p.c] = true;
                    tomato[nh][p.r][p.c] = 1;
                    tq.push({ nh, p.r, p.c });
                    tcnt--;
                }
            }
        }
        if (tq.empty())
            break;
        q = tq;
        day++;
    }
    // cout << tcnt << '\n';
    if (tcnt > 0)
        cout << "-1" << '\n';
    else
        cout << day << '\n';

    return 0;
}