#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int cnt[102];
int arr[102][102];

int vst[102];
int n, k;

int main()
{
    cin >> n >> k;
    vector<int> v(k);
    for (int i = 0; i < k; ++i)
    {
        cin >> v[i];
        arr[v[i]][cnt[v[i]]++] = i;
    }

    int tn = n, idx = 0;
    memset(cnt, 0, sizeof(cnt));
    while (tn > 0 && idx < k)
    {
        int x = v[idx];
        cnt[x]++;
        if (vst[v[idx++]])
            continue;
        vst[x] = true;
        tn--;
    }

    int ret = 0;

    for (int i = idx; i < k; ++i)
    {
        // 만약 이미 존재하면 continue;

        if (vst[v[i]])
        {
            cnt[v[i]]++;
            continue;
        }
        // 없으면, 있는 것 들 중에서 가장 나중에 나오는 것을 제거해야 한다.
        ret++;
        int mv = 0, mi = -1;
        for (int j = 1; j < k + 1; ++j)
        {
            if (!vst[j])
                continue;
            if (arr[j][cnt[j]] == 0)
            {
                mv = j;
                break;
            }
            else if (mi < arr[j][cnt[j]])
            {
                mi = arr[j][cnt[j]];
                mv = j;
            }
        }
        vst[v[i]] = true;
        vst[mv] = false;
        cnt[v[i]]++;
    }

    cout << ret << '\n';

    return 0;
}