#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int R, C, M;

struct shark
{
    // s: 속력, d: 이동 방향, z: 크기 (크기가 큰녀석이 작은 녀석을 잡아먹음)
    int r, c, s, d, z;
};

// 위, 아래, 오른쪽, 왼쪽 순서
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };
int nd[4] = { 1, 0, 3, 2 };

int arr[100][100];
int copy_arr[100][100];
shark sharks[10001];

void put_shakrs(vector<shark> &q)
{
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (arr[i][j] > 0)
                q.push_back(sharks[arr[i][j]]);
}

void move_sharks(vector<shark> &q)
{
    memset(copy_arr, 0, sizeof(copy_arr));

    for (auto next_shark : q)
    {
        int d = next_shark.d;
        int s = next_shark.s;
        int z = next_shark.z;
        int nr = next_shark.r;
        int nc = next_shark.c;

        // 시간 초과
        // for (int i = 0; i < s; ++i)
        // {
        //     if ((d == 0 && nr == 0) || (d == 1 && nr == R - 1) || (d == 2 && nc == C - 1) || (d == 3 && nc == 0))
        //     { // 회전
        //         d = nd[d];
        //     }
        //     nr += dr[d];
        //     nc += dc[d];
        // }

        int nmove;
        if (d < 2)
        {
            nmove = s % ((R - 1) * 2);
        }
        else
        {
            nmove = s % ((C - 1) * 2);
        }

        for (int i = 0; i < nmove; ++i)
        {
            if ((d == 0 && nr == 0) || (d == 1 && nr == R - 1) || (d == 2 && nc == C - 1) || (d == 3 && nc == 0))
            { // 회전
                d = nd[d];
            }
            nr += dr[d];
            nc += dc[d];
        }

        sharks[z].d = d;
        sharks[z].r = nr;
        sharks[z].c = nc;
        copy_arr[nr][nc] = max(copy_arr[nr][nc], z);
    }

    // copy copy_arr to arr
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            arr[i][j] = copy_arr[i][j];
}

int main()
{
    cin >> R >> C >> M;
    for (int i = 1; i < M + 1; ++i) // 상어 번호는 1 번부터
    {
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        sharks[z] = { --r, --c, s, --d, z };
        arr[r][c] = z;
    }

    int ret = 0;

    for (int i = 0; i < C; ++i) // 1초에 한번씩 i 가 한칸 이동한다.
    {
        for (int j = 0; j < R; ++j)
        {
            if (arr[j][i] > 0) // 상어가 있다면
            {
                // 상어 잡음
                ret += arr[j][i];
                arr[j][i] = 0;
                break;
            }
        }
        // 있는 상어가 움직여야 한다. 있는 상어를 큐에 넣는다.
        // 레벨 순회
        vector<shark> q;
        put_shakrs(q);
        move_sharks(q);
    }

    cout << ret << '\n';

    return 0;
}