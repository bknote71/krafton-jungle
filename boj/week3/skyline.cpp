#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int END = 1000000001;

struct point
{
    int x, h, o, d;
    bool operator<(const point &p) const
    {
        if (x == p.x)
        {
            if (d == p.d)
                return h > p.h;
            return d > p.d;
        }
        return x < p.x;
    }
};

struct pqpoint
{
    int rx, h;
};

struct cmp
{
    bool operator()(const pqpoint &u, const pqpoint &v)
    {
        if (u.h == v.h)
            return u.rx > v.rx;
        return u.h < v.h;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<point> p(2 * n);

    for (int i = 0; i < n; ++i)
    {
        int l, h, r;
        cin >> l >> h >> r;

        p[2 * i] = { l, h, r, 1 };
        p[2 * i + 1] = { r, h, l, -1 };
    }

    sort(p.begin(), p.end());

    priority_queue<pqpoint, vector<pqpoint>, cmp> pq;
    vector<pair<int, int>> ret;
    pq.push({ END, 0 });

    for (int i = 0; i < 2 * n; ++i)
    {
        point now = p[i];
        if (now.d > 0)
        {
            if (pq.top().h < now.h)
                ret.push_back({ now.x, now.h });
            pq.push({ now.o, now.h });
        }
        else // pop
        {
            if (pq.top().h > now.h)
                continue;
            else
            {
                int rx = pq.top().rx;
                if (END == rx)
                    break;
                while (!pq.empty() && pq.top().rx <= rx)
                {
                    pq.pop();
                }
                if (now.h != pq.top().h)
                    ret.push_back({ rx, pq.top().h });
            }
        }
    }

    for (int i = 0; i < ret.size(); ++i)
        cout << ret[i].first << ' ' << ret[i].second << ' ';
    return 0;
}