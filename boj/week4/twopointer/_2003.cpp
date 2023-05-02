#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> vt(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> vt[i];
    }

    int lo = 0, hi = 0;
    int ret = 0, sum = 0;

    while (true)
    {
        if (sum >= m)
            sum -= vt[lo++];
        else if (hi == n)
            break;
        else
            sum += vt[hi++];
        ret += (sum == m);
    }
    cout << ret << '\n';
    return 0;
}