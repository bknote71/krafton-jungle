#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

ll sum(vector<ll> &tree, int i)
{
    ll ret = 0;
    while (i > 0)
    {
        ret += tree[i];
        i -= (i & -i);
    }
    return ret;
}

void update(vector<ll> &tree, int i, ll diff)
{
    while (i < tree.size())
    {
        tree[i] += diff;
        i += (i & -i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, q;
    cin >> n >> q;

    vector<ll> vt(n + 1);
    vector<ll> tree(n + 1);

    for (int i = 1; i < n + 1; ++i)
    {
        cin >> vt[i];
        update(tree, i, vt[i]);
    }

    while (q--)
    {
        ll x, y, a, b;
        cin >> x >> y >> a >> b;
        if (x > y)
            swap(x, y);
        cout << sum(tree, y) - sum(tree, x - 1) << '\n';
        update(tree, a, b - vt[a]);
        vt[a] = b;
    }

    return 0;
}