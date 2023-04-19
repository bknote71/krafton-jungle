#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>

using namespace std;

struct point
{
    int idx, height;
};

point p[100001];

int main()
{
    int n;
    cin >> n;

    stack<point> st;
    st.push({ -1, 0 });
    int ret = 0;

    for (int i = 0, h; i < n + 1; ++i)
    {
        if (i < n)
            cin >> h;
        else
            h = 0;

        while (!st.empty() && st.top().height > h)
        {
            int h = st.top().height;
            st.pop();
            int w = i - st.top().idx - 1;
            ret = max(ret, h * w);
        }
        st.push({ i, h });
    }
    cout << ret << '\n';
}