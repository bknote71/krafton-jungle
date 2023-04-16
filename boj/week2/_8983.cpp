#include <iostream>

using namespace std;

pair<int, int> points[100001];
int gunner[100001];

int main()
{
    int M, N, L;
    scanf("%d %d %d", &M, &N, &L);

    for (int i = 0; i < M; ++i)
    {
        scanf("%d ", &gunner[i]);
    }

    for (int i = 0, x, y; i < N; ++i)
    {
        scanf("%d %d", &x, &y);
        points[i] = { x, y };
    }

    sort(gunner, gunner + M);
    int ret = 0;

    for (int i = 0; i < N; ++i)
    {
        pair<int, int> p = points[i];
        int x = p.first;
        int y = p.second;
        int lo = 0, hi = M - 1;

        while (lo + 1 < hi)
        {
            int mid = (lo + hi) >> 1;

            if (gunner[mid] < x)
                lo = mid;
            else
                hi = mid;
        }
        int cand = (abs(gunner[lo] - x) + y <= L) || (abs(gunner[hi] - x) + y <= L);

        // printf("%d %d %d %d %d\n", x, y, lo, hi, cand);

        ret += cand;
    }
    printf("%d\n", ret);

    return 0;
}