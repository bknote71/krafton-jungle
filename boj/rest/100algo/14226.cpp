#include <iostream>
#include <queue>

using namespace std;

typedef struct node
{
    int v, c;
};

int vst[2000][1000];

int main()
{
    int s;
    cin >> s;

    vst[1][0] = 1;
    queue<node> q;
    q.push({ 1, 0 });

    int ret = 0;
    while (!q.empty())
    {
        node n = q.front();
        int v = n.v;
        int c = n.c;
        int d = vst[v][c];
        q.pop();

        if (v == s)
        {
            ret = vst[v][c];
            break;
        }

        // 1. 클립보드에 복사 : [v][v]
        if (!vst[v][v])
        {

            q.push({ v, v });
            vst[v][v] = d + 1;
        }

        // 2. 붙혀넣기: [v + c][v]
        if (c > 0 && !vst[v + c][c])
        {
            q.push({ v + c, c });
            vst[v + c][c] = d + 1;
        }

        // 3. 하나 삭제: [v - 1][c]
        if (v > 0 && !vst[v - 1][c])
        {
            q.push({ v - 1, c });
            vst[v - 1][c] = d + 1;
        }
    }

    cout << ret - 1 << '\n';

    return 0;
}