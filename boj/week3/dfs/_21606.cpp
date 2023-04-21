#include <algorithm>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

string str;
int n;
vector<int> vt[200001];
bool vst[200001];

long long dfs(int cur)
{
    vst[cur] = true;
    long long ret = 0;
    for (auto next : vt[cur])
    {
        if (vst[next])
            continue;
        if (str[next - 1] == '1')
        {
            ++ret;
        }
        else
        {
            ret += dfs(next);
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    cin >> str;
    long long ret = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;
        if (str[a - 1] == '1' && str[b - 1] == '1')
            ret += 2;
        else
        {
            vt[a].push_back(b);
            vt[b].push_back(a);
        }
    }

    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == '0')
        {
            if (!vst[i + 1])
            {
                // 검은점의 개수 구하기 (나제외 ^^)
                long long cand = dfs(i + 1);
                ret += cand * (cand - 1);
            }
        }
    }
    cout << ret << '\n';

    return 0;
}