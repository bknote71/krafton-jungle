#include <iostream>
#include <vector>
using namespace std;

vector<int> v[100001];
int parent[100001];
int vst[100001];
int n;

void dfs(int cur)
{
    for (int i = 0; i < v[cur].size(); ++i)
    {
        int next = v[cur][i];
        if (next && !vst[next])
        {
            parent[next] = cur;
            vst[next] = 1;
            dfs(next);
        }
    }
}

int main()
{

    cin >> n;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    vst[1] = 1;
    dfs(1);

    for (int i = 2; i < n + 1; ++i)
    {
        cout << parent[i] << '\n';
    }

    return 0;
}