#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct edge
{
    int u;
    int v;
    int w;
};

int parent[1001];

int find(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = find(parent[x]);
}

void merge(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    // 큰 쪽으로 합치기
    if (parent[a] < parent[b])
        parent[b] = a;
    else
        parent[a] = b;
}

int cmp(const edge &e1, const edge &e2)
{
    return e1.w < e2.w;
}

int main()
{
    memset(parent, -1, sizeof(parent));
    vector<edge> vt;
    int n, m;
    cin >> n;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;

        vt.push_back({ u, v, w });
    }

    sort(vt.begin(), vt.end(), cmp);

    // n - 1 번 엣지를 연결
    int ret = 0;
    for (int i = 0; i < m; ++i)
    {
        int a = find(vt[i].u);
        int b = find(vt[i].v);
        if (find(a) != find(b))
        {
            ret += vt[i].w;
            merge(a, b);
        }
    }

    cout << ret << '\n';

    return 0;
}