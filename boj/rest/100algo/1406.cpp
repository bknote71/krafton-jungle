#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

stack<char> ls;
stack<char> rs;

string str;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> str;
    int m;
    cin >> m;

    string lr = str;
    string rr = "";

    for (int i = 0; i < str.length(); ++i)
    {
        // ls.push(str[i]);
        // lr.append(str[])
    }

    for (int i = 0; i < m; ++i)
    {
        char cmd;
        // char arg;
        string arg;
        cin >> cmd;
        if (cmd == 'P')
        {
            cin >> arg;
            // ls.push(arg);
            lr.append(arg);
        }
        else if (cmd == 'L')
        {
            if (!lr.empty())
            {
                rr.append(string(1, lr.back()));
                lr.pop_back();
                // rs.push(ls.top());
                // ls.pop();
            }
        }
        else if (cmd == 'D')
        {
            if (!rr.empty())
            {
                lr.append(string(1, rr.back()));
                rr.pop_back();
            }
        }
        else
        {
            if (!lr.empty())
            {
                lr.pop_back();
            }
        }
    }

    // string ret;
    // while (!ls.empty())
    // {
    //     ret = ls.top() + ret;
    //     ls.pop();
    // }
    // while (!rs.empty())
    // {
    //     ret = ret + rs.top();
    //     rs.pop();
    // }

    // cout << ret << '\n';
    reverse(rr.begin(), rr.end());
    cout << lr + rr << '\n';

    return 0;
}