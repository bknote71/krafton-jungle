#include <iostream>

using namespace std;

typedef long long ll;

int arr[500001];
int n;
int L[500001], R[500001];

ll merge(int lo, int hi, int m)
{
    int n1 = m - lo + 1;
    int n2 = hi - m;

    for (int i = 0; i < n1; ++i)
        L[i] = arr[lo + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[m + 1 + i];

    int i, j, w, k = lo;
    ll ret = 0;
    i = j = w = ret = 0;

    while (i < n1 && j < n2)
    {
        if (L[i] > R[j])
        {
            arr[k++] = R[j++];
        }
        else
        {
            arr[k++] = L[i++];
            ret += j;
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
        ret += j;
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
    }

    return ret;
}

ll solve(int lo, int hi)
{
    if (lo >= hi)
        return 0;

    ll ret = 0;
    int mid = lo + hi >> 1;
    ret += solve(lo, mid);
    ret += solve(mid + 1, hi);
    ret += merge(lo, hi, mid);
    return ret;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cout << solve(0, n - 1) << '\n';
    return 0;
}