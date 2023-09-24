#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

int prime[10000];
int vst[10000];

int main()
{
    // 소수인지 1만까지 확인을 ㄱㄱ
    for (int i = 0; i < 10000; ++i)
    {
        prime[i] = true;
    }

    prime[0] = prime[1] = 1;

    for (int i = 2; i * i <= 10000; ++i)
        if (prime[i])
        {
            for (int j = i * i; j <= 10000; j += i)
                prime[j] = 0;
        }

    int T;
    cin >> T;

    while (T--)
    {
        memset(vst, 0, sizeof(vst));
        int a, b;
        cin >> a >> b;

        // 한자리씩 변경
        queue<int> q;
        q.push(a);
        vst[a] = 1;
        int ret = 0;

        while (!q.empty())
        {
            int X = q.front();
            int D = vst[X];
            q.pop();

            if (X == b)
            {
                ret = vst[X];
                break;
            }

            for (int i = 0, p = 1; i < 4; ++i)
            {
                for (int j = 0; j < 10; ++j)
                {
                    int d = (X % (10 * p)) / p;

                    if (i == 3 && j == 0)
                        continue;

                    if (!vst[X + (-d + j) * p] && prime[X + (-d + j) * p])
                    {
                        vst[X + (-d + j) * p] = D + 1;
                        q.push(X + (-d + j) * p);
                    }
                }
                p *= 10;
            }
        }

        if (ret == 0)
            cout << "Impossible" << '\n';
        else
            cout << ret - 1 << '\n';
    }

    return 0;
}