#include <iostream>
#include <queue>

using namespace std;

struct point
{
    int r;
    int c;
    int dir;
};

int arr[101][101];
int dist[101][101][5];
int vst[101][101][5];
int rot[2][4] = { { 2, 3, 1, 0 }, { 3, 2, 0, 1 } }; // right, left

int dr[4] = { 0, 0, 1, -1 };
int dc[4] = { 1, -1, 0, 0 };

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> arr[i][j];

    int sr, sc, sd;
    int er, ec, ed;
    cin >> sr >> sc >> sd;
    cin >> er >> ec >> ed;

    sr--, sc--, sd--;
    er--, ec--, ed--;

    queue<point> q;
    q.push({ sr, sc, sd });
    vst[sr][sc][sd] = 1;
    dist[sr][sc][sd] = 1;

    while (!q.empty())
    {
        point p = q.front();
        q.pop();

        int r = p.r;
        int c = p.c;
        int d = p.dir;
        int dst = dist[r][c][d];
        // printf("%d %d %d %d\n", r, c, d, dst);
        if (er == r && ec == c && ed == d)
        {
            break;
        }

        // go 1,2,3
        for (int i = 1; i < 4; ++i)
        {
            int nr = r + dr[d] * i; // d = 0, 1, 2, 3
            int nc = c + dc[d] * i;

            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                continue;
            if (arr[nr][nc])
                break;

            if (vst[nr][nc][d])
                continue;

            vst[nr][nc][d] = true;
            dist[nr][nc][d] = dst + 1;
            q.push({ nr, nc, d });
        }

        for (int i = 0; i < 2; ++i)
        {
            int nd = rot[i][d];
            if (vst[r][c][nd])
                continue;

            vst[r][c][nd] = true;
            dist[r][c][nd] = dst + 1;
            q.push({ r, c, nd });
        }
    }

    printf("%d\n", dist[er][ec][ed] - 1);

    return 0;
}