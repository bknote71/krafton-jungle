#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int inf = 1000000001;

vector<pair<int, int>> vt[10001];

int vst[10001];
int n, m, s, e;
int maxweight;

bool bfs(int w)
{
    memset(vst, 0, sizeof(vst));

    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        if (cur == e)
            return true;

        for (auto next : vt[cur])
        {
            int nnode = next.first;
            int nw = next.second;

            if (!vst[nnode] && w <= nw)
            {
                vst[nnode] = true;
                q.push(nnode);
            }
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        int A, B, C;
        cin >> A >> B >> C;
        vt[A].push_back({ B, C });
        vt[B].push_back({ A, C });
    }

    cin >> s >> e;

    // s to e 갈 수 있는 경로는 여러가지가 존재할 수 있다.
    // 만들 수 있는 "여러 경로" 중에서 가장 최소값이 큰 경로

    // 물품 중량
    int lo = 0, hi = inf;
    while (lo + 1 < hi)
    {
        int mid = (lo + hi) >> 1;

        if (bfs(mid))
            lo = mid;
        else
            hi = mid;
    }
    cout << lo << '\n';

    return 0;
}

/*

void dfs(int cur, int minweight)
{
    if (cur == e)
    {
        maxweight = max(maxweight, minweight);
        return;
    }

    vst[cur] = true;

    for (auto next : vt[cur])
    {
        int nnode = next.first;
        int nweight = next.second;
        if (vst[nnode])
            continue;

        dfs(nnode, min(minweight, nweight));
    }

    vst[cur] = false;
}
*/

/*
// int dp[10001][10001];

int dfs(int cur, int prev)
{
    if (cur == e)
    {
        return inf;
    }

    // int &ret = dp[cur][prev];
    // if (ret != -1)
    //     return ret;

    int cand = 0;
    for (auto next : vt[cur])
    {
        int nnode = next.first;
        int nweight = next.second;
        if (nnode != prev)
        {
            cand = max(cand, min(nweight, dfs(nnode, cur)));
        }
    }
    // return ret = cand;
    return cand;
}
*/