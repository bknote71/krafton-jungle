#include <iostream>
#include <queue>

using namespace std;

char arr[100][100];
int vst[100][100];
int dist[100][100];
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };

int main()
{
    int w, h, first = true;
    cin >> w >> h;

    queue<pair<int, int>> q;
    pair<int, int> dest;

    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 'C')
            {
                if (first)
                {
                    q.push({ i, j });
                    vst[i][j] = true;
                    first = false;
                }
                else
                {
                    dest = { i, j };
                }
            }
        }

    while (!q.empty())
    {
        pair<int, int> p = q.front();
        q.pop();
        int r = p.first;
        int c = p.second;

        if (dest.first == r && dest.second == c)
        {
            break;
        }

        for (int d = 0; d < 4; ++d)
        {
            int i = 0;
            while (true)
            {
                ++i;
                int nr = r + dr[d] * i;
                int nc = c + dc[d] * i;
                if (nr < 0 || nr >= h || nc < 0 || nc >= w)
                    break;
                if (vst[nr][nc])
                    continue;
                if (arr[nr][nc] == '*')
                    break;

                vst[nr][nc] = true;
                q.push({ nr, nc });
                dist[nr][nc] = dist[r][c] + 1;
            }
        }
    }

    cout << dist[dest.first][dest.second] - 1 << '\n';

    return 0;
}