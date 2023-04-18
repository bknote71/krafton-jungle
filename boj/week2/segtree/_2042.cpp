#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 3000000;

struct SegTree
{
    int n;
    long long tree[SIZE];

    SegTree(int n) : n(n)
    {
        memset(tree, 0, sizeof(tree));
        // fill(tree, tree + SIZE, 0);
    }

    void init(const vector<long long> &a, int node, int s, int e)
    {
        if (s == e)
        {
            tree[node] = a[s];
            return;
        }
        int mid = (s + e) >> 1;
        init(a, node * 2, s, mid);
        init(a, node * 2 + 1, mid + 1, e);
    }

    long long query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }

    long long query(int node, int s, int e, int l, int r)
    {
        if (r < s || e < l)
            return 0;
        if (l <= s && e <= r)
            return tree[node];
        int mid = (s + e) >> 1;
        return query(2 * node, s, mid, l, r) + query(2 * node + 1, mid + 1, e, l, r);
    }

    void update(int index, long long value)
    {
        update(1, 0, n - 1, index, value);
    }
    void update(int node, int s, int e, int index, long long value)
    {
        if (e < index || index < s)
            return;
        if (s == e)
        {
            tree[node] = value;
            return;
        }
        int mid = (s + e) >> 1;
        update(2 * node, s, mid, index, value);
        update(2 * node + 1, mid + 1, e, index, value);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
};

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);

    int n, m, k;

    cin >> n >> m >> k;

    SegTree st(n);

    for (int i = 0; i < n; ++i)
    {
        long long x;
        cin >> x;
        st.update(i, x);
    }

    for (int i = 0; i < m + k; ++i)
    {
        long long a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        {
            st.update(b - 1, c);
        }
        else
        {
            cout << st.query(b - 1, c - 1) << '\n';
        }
    }

    return 0;
}
