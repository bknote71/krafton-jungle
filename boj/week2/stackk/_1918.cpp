#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

stack<char> st;
vector<char> vt;

int priority(char x)
{
    if ('A' <= x && x <= 'Z')
        return -1;
    if (x == ')')
        return 0;
    if (x == '*' || x == '/')
        return 1;
    if (x == '+' || x == '-')
        return 2;
    if (x == '(')
        return 3;
    return -2;
}

int main()
{
    string str;
    cin >> str;

    for (int i = 0; i < str.size(); ++i)
    {
        int p = priority(str[i]);
        if (p < 0)
            vt.push_back(str[i]);
        else
        {
            while (!st.empty())
            {
                char top = st.top();
                if (top == '(' && str[i] == ')')
                {
                    st.pop();
                    break;
                }
                else if (top != '(' && priority(top) < p)
                {
                    vt.push_back(top);
                    st.pop();
                }
                else
                    break;
            }
            if (str[i] != ')')
                st.push(str[i]);
        }
    }

    for (int i = 0; i < vt.size(); ++i)
        cout << vt[i];

    return 0;
}