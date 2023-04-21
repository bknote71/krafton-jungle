#include <algorithm>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

string str;
int n;
vector<vector<int>> vt;
vector<bool> vst;

long long dfs(int cur)
{
    long long ret = 0;
    for (int i = 0; i < vt[cur].size(); ++i)
    {
        int next = vt[cur][i];
        if (str[next - 1] == '1')
        {
            if (!vst[next])
            {
                vst[next] = true;
                ret += 1;
            }
        }
        else
        {
            if (!vst[next])
            {
                vst[next] = true;
                ret += dfs(next);
            }
        }
    }
    return ret;
}

int main()
{
    cin >> n;
    cin >> str;

    vt.resize(n + 1);
    vst.resize(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        vt[a].push_back(b);
        vt[b].push_back(a);
    }

    long long ret = 0;
    for (int i = 0; i < str.length(); ++i)
    {
        fill(vst.begin(), vst.end(), 0);
        if (str[i] == '1')
        {
            vst[i + 1] = true;
            long long cand = dfs(i + 1);
            ret += cand;
        }
    }
    cout << ret << '\n';

    return 0;
}