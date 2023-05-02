#include <iostream>
#include <stack>

using namespace std;

int n;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    long long ret = 0;
    stack<pair<long long, long long>> st;
    for (int i = 0; i < n; ++i)
    {
        long long k;
        cin >> k;
        int sk = 0;
        while (!st.empty())
        {
            int h = st.top().first;
            int r = st.top().second;
            ret += 1 + (h > k ? 0 : r);
            if (h > k)
                break;
            else if (h == k)
            {
                sk = r + 1;
            }
            st.pop();
        }
        st.push({ k, sk });
    }

    cout << ret << '\n';

    return 0;
}