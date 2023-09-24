#include <algorithm>
#include <iostream>

using namespace std;

int arr[10000];
int ivl[10000];

int main()
{
    int n, k;
    cin >> n;
    cin >> k;

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    sort(arr, arr + n);

    for (int i = 0; i < n - 1; ++i)
        ivl[i] = arr[i + 1] - arr[i];

    // 내림차순 정렬
    sort(ivl, ivl + n - 1, greater<int>());

    long long sum = 0;
    for (int i = k - 1; i < n - 1; ++i)
        sum += ivl[i];

    cout << sum << '\n';

    return 0;
}