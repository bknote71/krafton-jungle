#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

int parent[1000001];

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

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;

    fill(parent, parent + n + 1, -1);

    for (int i = 0; i < m; ++i)
    {
        int o, a, b;
        cin >> o >> a >> b;

        if (o == 0)
            merge(a, b);
        else
            cout << (find(a) == find(b) ? "YES" : "NO") << '\n';
    }

    return 0;
}