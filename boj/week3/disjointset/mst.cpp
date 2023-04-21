#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
int parent[10002];
int find(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = find(parent[x]);
}
bool merge(int a, int b)
{
    a = find(a), b = find(b);
    if (a == b)
        return false;

    // a 가 많이 담고있다.
    if (parent[a] < parent[b])
        parent[a] += parent[b], parent[b] = a;

    else
        parent[b] += parent[a], parent[a] = b;
    return true;
}
struct Edge
{
    int u, v, w;
    bool operator<(const Edge &x) const
    {
        return w < x.w;
    }
} edge[100001];
int main()
{
    int V, E, s, e, w;
    cin >> V >> E;
    for (int i = 0; i < E; ++i)
    {
        cin >> s >> e >> w;

        edge[i] = { s, e, w };
    }

    sort(edge, edge + E);
    memset(parent, -1, sizeof(parent));

    long long ret = 0;

    for (int i = 0; i < E; ++i)
        if (merge(edge[i].u, edge[i].v))
            ret += edge[i].w;
    cout << ret << '\n';
    return 0;
}
