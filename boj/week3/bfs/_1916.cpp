#include <iostream>
#include <queue>

using namespace std;

char arr[51][51];
bool vst[51][51][2501];

struct point
{
    int r, c, d;
};

int dr[4] = { 1, 0, -1, 0 };
int dc[4] = { 0, 1, 0, -1 };

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> arr[i][j];

    queue<point> q;
    q.push({ 0, 0, 0 });
    vst[0][0][0] = 1;

    int ret = 100000;
    while (!q.empty())
    {
        point p = q.front();
        q.pop();

        if (p.r == n - 1 && p.c == n - 1)
        {
            ret = min(ret, p.d);
        }
        for (int d = 0; d < 4; ++d)
        {
            int nr = p.r + dr[d];
            int nc = p.c + dc[d];
            // printf("? %d %d\n", nr, nc);

            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                continue;
            int nd = p.d + (arr[nr][nc] == '0');
            if (vst[nr][nc][nd])
                continue;
            vst[nr][nc][nd] = 1;
            q.push({ nr, nc, nd });
        }
    }
    cout << ret << '\n';

    return 0;
}