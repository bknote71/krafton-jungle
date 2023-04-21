#include <iostream>

using namespace std;

int hvst[100];
int lvst[100];
int n, m;

vector<int> heavy[100];
vector<int> light[100];

int hdfs(int cur)
{
    hvst[cur] = true;
    int ret = 0; // 자기 자신
    for (auto next : heavy[cur])
    {
        if (hvst[next])
            continue;

        ret += hdfs(next) + 1;
    }
    return ret;
}

int ldfs(int cur)
{
    lvst[cur] = true;
    int ret = 0; // 자기 자신
    for (auto next : light[cur])
    {
        if (lvst[next])
            continue;

        ret += ldfs(next) + 1;
    }
    return ret;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        heavy[a].push_back(b);
        light[b].push_back(a);
    }

    int ret = 0;
    for (int i = 1; i < n + 1; ++i)
    {
        memset(hvst, 0, sizeof(hvst));
        memset(lvst, 0, sizeof(lvst));
        int cand1 = hdfs(i) >= (n + 1) / 2 ? 1 : 0;
        int cand2 = ldfs(i) >= (n + 1) / 2 ? 1 : 0;
        ret += (cand1 || cand2);
    }
    cout << ret << '\n';
    return 0;
}
