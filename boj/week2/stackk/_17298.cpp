#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> vt;

int main()
{
    int n;
    cin >> n;
    stack<pair<int, int>> st;

    vt.resize(n);
    fill(vt.begin(), vt.end(), -1);

    for (int i = 0, lasth = 0; i < n; ++i)
    {
        int e;
        cin >> e;

        if ((i > 0) && lasth < e)
        {
            while (!st.empty())
            {
                int top = st.top().second;
                if (top < e)
                {
                    vt[st.top().first] = e;
                    st.pop();
                }
                else
                    break;
            }
        }
        lasth = e;
        st.push({ i, e });
    }

    for (int i = 0; i < n; ++i)
    {
        cout << vt[i] << ' ';
    }

    return 0;
}