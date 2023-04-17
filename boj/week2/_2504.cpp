#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<string> st;
bool flag = true;

bool isInteger(const std::string &str)
{
    try
    {
        std::stoi(str);
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
}

void process(string t)
{
    bool found = false;
    int sum = 0;
    while (!st.empty())
    {
        string top = st.top();
        st.pop();

        if (top == t)
        {
            found = true;
            break;
        }

        if (!isInteger(top))
        {
            flag = false;
            return;
        }
        sum += stoi(top);
    }
    if (!found)
    {
        flag = false;
        return;
    }
    int w = t == "(" ? 2 : 3;
    st.push(to_string(sum == 0 ? w : w * sum));
}

int main()
{
    string str;
    cin >> str;

    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == '(' || str[i] == '[')
            st.push(string(1, str[i]));
        else if (str[i] == ')')
        {
            process("(");
        }
        else if (str[i] == ']')
        {
            process("[");
        }
    }

    int ret = 0;
    while (!st.empty())
    {
        string top = st.top();
        st.pop();

        if (!isInteger(top))
        {
            flag = false;
            break;
        }
        ret += stoi(top);
    }

    if (!flag)
        cout << 0 << '\n';
    else
        cout << ret << '\n';

    return 0;
}