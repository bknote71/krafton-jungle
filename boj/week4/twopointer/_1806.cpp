#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, s;
    cin >> n >> s;
    vector<int> vt(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> vt[i];
    }

    int lo = 0, hi = 0, ret = 0;
    long long sum = 0;
    while (lo < hi + 1)
    {
        if (sum >= s)
            sum -= vt[lo++];
        else if (hi == n)
            break;
        else
            sum += vt[hi++];
        if (sum >= s)
        {
            ret = ret == 0 ? hi - lo : min(ret, hi - lo);
        }
    }
    cout << (s == 0 ? 1 : ret) << '\n';
    return 0;
}