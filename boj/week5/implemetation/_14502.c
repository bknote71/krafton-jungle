#include <stdio.h>
#include <string.h>

int arr[8][8], n, m;
int tarr[8][8];
int vst[8][8];
int ret;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, -1, 0, 1 };

void flooding(int r, int c)
{
    vst[r][c] = 1;
    for (int d = 0; d < 4; ++d)
    {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m)
            continue;
        if (vst[nr][nc])
            continue;
        if (tarr[nr][nc] == 0)
        {
            tarr[nr][nc] = 2;
            flooding(nr, nc);
        }
    }
}

int counting(int r, int c)
{
    vst[r][c] = 1;
    int a = 1;
    for (int d = 0; d < 4; ++d)
    {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m)
            continue;
        if (vst[nr][nc])
            continue;
        if (tarr[nr][nc] == 0)
            a += counting(nr, nc);
    }
    return a;
}

void coloring(int cnt)
{
    if (cnt == 0)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                tarr[i][j] = arr[i][j];
        memset(vst, 0, sizeof(vst));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (tarr[i][j] == 2 && !vst[i][j])
                    flooding(i, j);
        int cand = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (tarr[i][j] == 0 && !vst[i][j])
                    cand += counting(i, j);
        ret = ret > cand ? ret : cand;
        return;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (arr[i][j] == 0)
            {
                arr[i][j] = 1;
                coloring(cnt - 1);
                arr[i][j] = 0;
            }
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &arr[i][j]);

    coloring(3);

    printf("%d\n", ret);
    return 0;
}