#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>

using namespace std;

int m;
string A, B;

vector<int> solve(const string &str)
{
    vector<int> ret(m + 1);
    int cur = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(')
            cur++;
        else
        {
            cur--;
            if (str[i - 1] == '(')
            {
                ret[cur]++;
            }
        }
    }
    for (int i = 0; i < ret.size() - 1; i++)
    {
        ret[i + 1] += ret[i] / 2;
        ret[i] %= 2;
    }
    return ret;
}

string sol()
{
    vector<int> pa = solve(A);
    vector<int> pb = solve(B);

    for (int i = pa.size() - 1; i >= 0; i--)
    {
        if (pa[i] < pb[i])
            return "<";
        if (pa[i] > pb[i])
            return ">";
    }
    return "=";
}

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        cin >> A;
        cin >> B;
        m = max(A.size(), B.size());
        m /= 2;
        cout << sol() << '\n';
    }
    return 0;
}