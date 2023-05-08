#include <stdio.h>

int cnt[10000];
int sum = 0;
int max = -5000, min = 5000;
int unique = 0;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        int t;
        scanf("%d", &t);
        sum += t;
        cnt[t + 4000]++;
        max = max < t ? t : max;
        min = min > t ? t : min;
    }

    // 중앙값
    int middle = 0;
    for (int i = 0, c = (int)((float)n / 2 + 0.5); i < 8001;)
    {
        if (c <= cnt[i])
        {
            middle = i - 4000;
            break;
        }
        c -= cnt[i++];
    }

    int mcnt = 0, mfidx = 10000, msidx = 10000;
    for (int i = 0; i < 8001; ++i)
    {
        if (mcnt < cnt[i])
        {
            mcnt = cnt[i];
            mfidx = msidx = i - 4000;
        }
        else if (mcnt == cnt[i])
        {
            msidx = msidx == mfidx ? i - 4000 : msidx;
        }
    }

    printf("%d\n", (int)((float)sum / n + (sum < 0 ? -0.5 : 0.5)));
    printf("%d\n", middle);
    printf("%d\n", msidx);
    printf("%d\n", max - min);

    return 0;
}