#include <iostream>
#include <queue>

using namespace std;

int box[101][101];
int vst[101];

int main()
{
    int n, m;
    cin >> n;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        box[a][b] = 1;
        box[b][a] = 1;
    }

    queue<int> q;
    q.push(1);
    vst[1] = 1;
    int ret = -1;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        ++ret;

        for (int i = 1; i < n + 1; ++i)
        {
            if (!vst[i] && box[cur][i])
            {
                vst[i] = 1;
                q.push(i);
            }
        }
    }

    cout << ret << '\n';

    return 0;
}