#include <iostream>
#include <queue>
#include <vector>

using namespace std;

char arr[51][51];
bool vst[50][50][2500][2];

int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };

struct point
{
    int r, c;
    int d;
    int ishog;
};

int main()
{
    int R, C;
    cin >> R >> C;

    pair<int, int> E;
    pair<int, int> S;
    vector<pair<int, int>> wt;

    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            cin >> arr[i][j];
            if (arr[i][j] == '*')
                wt.push_back({ i, j });
            else if (arr[i][j] == 'D')
                E = { i, j };
            else if (arr[i][j] == 'S')
                S = { i, j };
        }
    }

    queue<point> q;
    q.push({ S.first, S.second, 0, 1 });
    vst[S.first][S.second][0][1] = true;

    for (int i = 0; i < wt.size(); ++i)
    {
        q.push({ wt[i].first, wt[i].second, 0, 0 });
        vst[wt[i].first][wt[i].second][0][0] = true;
    }

    int ret = -1;
    while (!q.empty())
    {
        point p = q.front();
        q.pop();

        if (p.ishog && arr[p.r][p.c] == '*')
            continue;

        if (arr[p.r][p.c] == 'D')
        {
            ret = p.d;
            break;
        }
        for (int d = 0; d < 4; ++d)
        {
            int nr = p.r + dr[d];
            int nc = p.c + dc[d];
            int nd = p.d + 1;

            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;

            if (vst[nr][nc][nd][p.ishog])
                continue;
            if (p.ishog)
            {
                if (arr[nr][nc] == '.' || arr[nr][nc] == 'D')
                {
                    vst[nr][nc][nd][p.ishog] = true;
                    q.push({ nr, nc, nd, p.ishog });
                }
            }
            else
            {
                if (arr[nr][nc] == '.')
                {
                    vst[nr][nc][nd][p.ishog] = true;
                    q.push({ nr, nc, nd, p.ishog });
                    arr[nr][nc] = '*';
                }
            }
        }
    }

    if (ret == -1)
        cout << "KAKTUS" << '\n';
    else
        cout << ret << '\n';

    return 0;
}