#include <iostream>

using namespace std;

pair<int, int> arr[6];
int cnt[5];

int main()
{
    int k;

    cin >> k;

    for (int i = 0, d, l; i < 6; ++i)
    {
        cin >> d >> l;
        arr[i] = { d, l };
        cnt[d]++;
    }

    int area = 1, sub = 1;

    for (int i = 0; i < 6; ++i)
    {
        if (cnt[arr[i].first] == 1)
        {
            area *= arr[i].second;
            continue;
        }

        int nnext = arr[(i + 2) % 6].first;
        if (arr[i].first == nnext)
        {
            sub *= arr[(i + 1) % 6].second;
        }
    }
    // printf("%d %d\n", area, sub);

    cout << k * (area - sub) << '\n';

    return 0;
}
