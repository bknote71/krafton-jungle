#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

struct point
{
    int x;
    int center;
    int dir; // 0: push할 것, 1: pop할 것
    int checked = 0;
};

stack<point> st;
vector<point> vt;

bool cmp(const point &u, const point &v)
{
    if (u.x == v.x)
        return u.center < v.center;
    return u.x < v.x;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0, x, r; i < n; ++i)
    {
        cin >> x >> r;
        vt.push_back({ x - r, x, 0, 0 });
        vt.push_back({ x + r, x, 1, 0 });
    }
    // push: 0, pop: 1
    sort(vt.begin(), vt.end(), cmp);

    int ret = 1;
    point pop;

    for (int i = 0, pdir = 0; i < vt.size(); ++i)
    {
        if (i != 0)
        {
            point now = vt[i];
            int dir = now.dir;

            if (pdir == 0 && dir == 1)
            {
                st.pop();
                pop = now;
                ret += 1;
            }
            else if (pdir == 1 && dir == 1)
            {
                if (pop.x != now.x)
                    st.top().checked = 1;
                pop = now;
                ret += st.top().checked == 0 ? 2 : 1;
                st.pop();
            }
            else if (pdir == 0 && dir == 0)
            {
                if (st.top().x != now.x)
                    st.top().checked = 1;
                st.push(now);
            }
            else if (pdir == 1 && dir == 0)
            {
                if (pop.x != now.x)
                    st.top().checked = 1;
                st.push(now);
            }

            pdir = dir;
        }
        else
        {
            st.push(vt[i]);
        }
    }

    cout << ret << '\n';

    return 0;
}