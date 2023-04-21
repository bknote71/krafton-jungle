#include <iostream>
#include <queue>
#include <string.h>
#include <vector>
using namespace std;

int arr[300][300];
bool vst[300][300];

int dr[4] = { 1, 0, -1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int n, m;

struct point
{
    int r, c, h;
};

void dfs(int r, int c)
{
    vst[r][c] = true;
    for (int d = 0; d < 4; ++d)
    {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m)
            continue;
        if (vst[nr][nc])
            continue;
        if (arr[nr][nc] > 0)
            dfs(nr, nc);
    }
}

int main()
{

    cin >> n >> m;

    vector<point> q;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> arr[i][j];
            if (arr[i][j] > 0)
                q.push_back({ i, j, arr[i][j] });
        }
    }

    int ret = 1;
    while (true)
    {
        // printf("ret? %d\n", ret);
        memset(vst, 0, sizeof(vst));
        vector<point> tq;
        vector<point> zq;
        int qs = q.size();
        for (int i = 0; i < qs; ++i)
        {
            point p = q.back();
            q.pop_back();
            int r = p.r;
            int c = p.c;
            int rm = 0;
            for (int d = 0; d < 4; ++d)
            {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                    continue;
                rm += (arr[nr][nc] == 0);
            }
            if (p.h - rm > 0)
                tq.push_back({ r, c, p.h - rm });
            else
                zq.push_back({ r, c, 0 });
        }

        // 큐에 남아있는 점들로 그.. dfs count를 세야 합니다.
        // 그 전에 업데이트
        if (tq.empty())
        {
            ret = 0;
            break;
        }
        for (int i = 0; i < tq.size(); ++i)
        {
            point p = tq[i];
            arr[p.r][p.c] = p.h;
        }

        for (int i = 0; i < zq.size(); ++i)
        {
            point p = zq[i];
            arr[p.r][p.c] = p.h;
        }

        int cnt = 0;
        for (int i = 0; i < tq.size(); ++i)
        {
            int r = tq[i].r;
            int c = tq[i].c;
            if (!vst[r][c])
            {
                if (++cnt >= 2)
                    break;
                dfs(r, c);
            }
        }
        if (cnt >= 2)
            break;
        ++ret;
        q = tq;
    }

    cout << ret << '\n';

    return 0;
}