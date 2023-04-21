#include <iostream>

using namespace std;

int parent[10000];

int find(int node)
{
    if (parent[node] < 0)
        return node;
    return parent[node] = find(parent[node]);
}

void merge(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return;
    if (parent[a] < parent[b])
        parent[a] += parent[b], parent[b] = a;
    else
        parent[b] += parent[a], parent[a] = b;
}

struct edge
{
    int s, e, c;
    bool operator<(const edge &e) const
    {
        return c < e.c;
    }
};

edge ed[100000];

int main()
{
    int v, e;
    cin >> v >> e;
    fill(parent, parent + v, -1);
    for (int i = 0; i < e; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        ed[i] = { a, b, c };
    }

    sort(ed, ed + e);
    int ret = 0;
    for (int i = 0; i < e; ++i)
    {
        edge t = ed[i];
        int sf = find(t.s);
        int ef = find(t.e);
        if (sf == ef)
            continue;
        else
        {
            ret += t.c;
            merge(sf, ef);
        }
    }

    cout << ret << '\n';

    return 0;
}