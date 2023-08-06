#include <algorithm>
#include <iostream>

using namespace std;

int arr[50][50];

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%1d", &arr[i][j]);

    int maxvalue = 1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int x = arr[i][j];
            for (int k = j + 1; k < m; ++k)
            {
                if (x == arr[i][k])
                {
                    // diff: k - j
                    // so boundary 안에서 arr[i + (k - j)][j]
                    // arr[i + (k - j)][k] 들이 같으면 max 값 갱신
                    if (i + k - j < n && arr[i + (k - j)][j] == x && arr[i + (k - j)][k] == x)
                        maxvalue = max(maxvalue, (k - j + 1) * (k - j + 1));
                }
            }
        }
    }

    printf("%d\n", maxvalue);

    return 0;
}