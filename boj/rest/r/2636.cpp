#include <iostream>
#include <queue>

using namespace std;

int n, m;
int arr[100][100];
int vst[100][100];
int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };

void init_start_queue(int r, int c, queue<pair<int, int>> &q)
{
    q.push({ r, c });
    vst[r][c] = true;

    for (int d = 0; d < 4; ++d)
    {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m)
            continue;
        if (!vst[nr][nc] && arr[nr][nc] == 0)
        {
            init_start_queue(nr, nc, q);
        }
    }
}

int main()
{
    cin >> n >> m;

    int cnt = 0, day = 0;

    queue<pair<int, int>> q;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            cin >> arr[i][j];
            cnt += (arr[i][j] == 1);
        }

    init_start_queue(0, 0, q);

    // start
    while (!q.empty())
    {
        ++day;
        int qsize = q.size();
        int flag = false;
        int tcnt = 0;
        for (int i = 0; i < qsize; ++i)
        {
            pair<int, int> p = q.front();
            q.pop();

            for (int d = 0; d < 4; ++d)
            {
                int nr = p.first + dr[d];
                int nc = p.second + dc[d];

                if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                    continue;

                if (vst[nr][nc] || arr[nr][nc] == 0)
                    continue;

                flag = true;
                vst[nr][nc] = 1;
                arr[nr][nc] = 0;
                q.push({ nr, nc });
                ++tcnt;
            }
        }
        if (!flag)
        {
            break;
        }
        // printf("day: %d, cnt: %d\n", day, cnt);

        if (cnt == tcnt)
            break;
        cnt -= tcnt;

        queue<pair<int, int>> tq;
        // tq 를 순회하면서 근처에 0이면 무조건 넣기
        tq = q;
        while (!tq.empty())
        {
            pair<int, int> tp = tq.front();
            tq.pop();
            init_start_queue(tp.first, tp.second, q);
        }
    }

    cout << day << '\n';
    cout << cnt << '\n';
    return 0;
}