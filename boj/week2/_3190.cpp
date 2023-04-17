#include <iostream>
#include <queue>

using namespace std;

struct point
{
    int x, y, dir, live;
};

int apple[1001][1001];
char change[100001];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int main()
{
    queue<point> q;

    int N, K, L;
    cin >> N;
    cin >> K;

    for (int i = 0, r, c; i < K; ++i)
    {
        cin >> r >> c;
        apple[r][c] = 1;
    }

    cin >> L;
    for (int i = 0, idx; i < L; ++i)
    {
        char dir;
        cin >> idx >> dir;
        change[idx] = dir;
    }

    int ret = 0;
    q.push({ 1, 1, 0, 0 });

    while (true)
    {
        // 1. head 를 검사한다.
        point head = q.front();
        q.pop();
        // printf("%d %d %d %d\n", head.x, head.y, head.dir, head.live);
        // 벽
        if (head.x <= 0 || head.x > N || head.y <= 0 || head.y > N)
            break;

        // cout << eat << endl;

        // 몸통 체크 : head 이후 ~ 꼬리에서 만나는 점이 있으면 break;
        // 그럼 이제 head 이후부터 검사
        bool flag = true;
        queue<point> tmp;
        queue<point> chk = q;

        // 이동
        point last = head;
        head.x += dx[head.dir];
        head.y += dy[head.dir];
        // 방향 전환 체크
        if (change[++head.live] != 0)
        {
            head.dir = (head.dir + (change[head.live] == 'D' ? 1 : 3)) % 4;
        }
        // 사과 체크
        bool eat = apple[head.x][head.y]-- >= 1 ? 1 : 0;

        tmp.push(head);

        while (!chk.empty())
        {
            point body = chk.front();
            chk.pop();

            // 몸통 체크 : 헤드와 만나는지
            if (body.x == head.x && body.y == head.y)
            {
                flag = false;
                break;
            }
            last = body;
            // 이동
            body.x += dx[body.dir];
            body.y += dy[body.dir];
            if (change[++body.live] != 0)
            {
                body.dir = (body.dir + (change[body.live] == 'D' ? 1 : 3)) % 4;
            }

            tmp.push(body);
        }
        ret++;
        if (!flag)
            break;

        q = tmp;
        if (eat)
        {
            q.push({ last.x, last.y, last.dir, last.live });
        }
    }

    cout << ret << '\n';

    return 0;
}