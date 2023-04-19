#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const int SIZE = 3 * 30000;

struct SegTree
{
    int n;
    int tree[SIZE];
    int arr[SIZE];
    SegTree(int n) : n(n)
    {
        memset(tree, 0, sizeof(tree));
        memset(arr, 0, sizeof(arr));
    }

    int query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
    int query(int node, int s, int e, int l, int r)
    {
        if (r < s || e < l)
            return 0;
        if (l <= s && e <= r)
            return arr[node];
        int mid = (s + e) >> 1;
        int ret = query(2 * node, s, mid, l, r) + query(2 * node + 1, mid + 1, e, l, r);
        return ret;
    }

    void update(int l, int r, int value)
    {
        update(1, 0, n - 1, l, r, value);
    }
    void update(int node, int s, int e, int l, int r, int value)
    {
        if (r < s || e < l)
            return;
        if (l <= s && e <= r)
        {
            tree[node] += value;
        }
        else
        {
            int mid = (s + e) >> 1;
            update(2 * node, s, mid, l, r, value);
            update(2 * node + 1, mid + 1, e, l, r, value);
        }

        if (tree[node] == 0)
        {
            if (s != e)
            {
                arr[node] = arr[2 * node] + arr[2 * node + 1];
            }
            else
                arr[node] = 0;
        }
        else
            arr[node] = e - s + 1;
    }
};

struct point
{
    int x;
    int sy, ey;
    int dir; // 1: in, -1: out

    bool operator<(const point &o) const
    {
        return x < o.x;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<point> p(2 * n);
    SegTree st(30000);

    for (int i = 0; i < n; ++i)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        p[2 * i] = { a, b, d, 1 };
        p[2 * i + 1] = { c, b, d, -1 };
    }

    sort(p.begin(), p.end());

    int ret = 0;

    for (int i = 0; i < 2 * n; ++i)
    {
        point now = p[i];
        if (i != 0)
        {
            int y = st.query(0, 30000);
            ret += (now.x - p[i - 1].x) * y;
        }
        st.update(now.sy, now.ey - 1, now.dir);
    }

    cout << ret << '\n';

    return 0;
}