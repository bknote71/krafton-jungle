#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 400000;
const int MAX = 1000000000;

struct SegTree
{
    int n;
    int tree[SIZE];
    SegTree(int n) : n(n) {}

    void init(const vector<int> &vt)
    {
        init(vt, 1, 0, n - 1);
    }

    void init(const vector<int> &vt, int node, int s, int e)
    {
        if (s == e)
        {
            tree[node] = vt[s];
            return;
        }
        int mid = (s + e) >> 1;
        init(vt, 2 * node, s, mid);
        init(vt, 2 * node + 1, mid + 1, e);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int index, int value)
    {
        update(1, 0, n - 1, index, value);
    }
    void update(int node, int s, int e, int index, int value)
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
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
    int query(int node, int s, int e, int l, int r)
    {
        if (r < s || e < l)
            return MAX;
        // 노드의 표현 범위가 l, r에 완전히 포함된다면
        if (l <= s && e <= r)
            return tree[node];
        int mid = (s + e) >> 1;
        return min(query(2 * node, s, mid, l, r), query(2 * node + 1, mid + 1, e, l, r));
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    SegTree st(n);
    vector<int> vt(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> vt[i];
    }

    st.init(vt); // O(N)

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << st.query(a - 1, b - 1) << '\n';
    }

    return 0;
}