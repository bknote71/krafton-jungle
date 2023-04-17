#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;

    vector<char> vt(N);
    stack<char> st;

    for (int i = 0; i < N; ++i)
    {
        cin >> vt[i];
    }

    st.push(vt[0]);

    for (int i = 1; i < N; ++i)
    {
        if (st.top() >= vt[i])
            st.push(vt[i]);
        else
        {
            while (!st.empty() && st.size() + N - i > N - K)
            {
                // pop 가능
                char top = st.top();
                if (top < vt[i])
                    st.pop();
                else
                {
                    break;
                }
            }
            st.push(vt[i]);
        }
    }

    int i = 0, ssize = st.size();
    while (!st.empty())
    {
        vt[i++] = st.top();
        st.pop();
    }

    for (int i = 0; i < (N - K); ++i)
    {
        cout << vt[ssize - 1 - i];
    }

    return 0;
}