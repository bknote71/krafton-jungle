#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct point
{
    int x, y;
    point() {}
    point(int x, int y) : x(x), y(y) {}

    bool operator<(const point &p) const
    {
        if (y == p.y)
            return x < p.x;
        return y < p.y;
    }
};

point p[100002];
const int inf = 2000000000;

bool cmp(const point &a, const point &b)
{
    return a.x < b.x;
}

int dist(const point &a, const point &b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main()
{
    int n;
    cin >> n;

    p[0] = { -20000, -20000 };

    for (int i = 1, r, c; i < n + 1; ++i)
    {
        cin >> r >> c;
        p[i] = { r, c };
    }

    sort(p, p + n + 1, cmp);

    int minDist = 2000000000, prev = 0;
    set<point> cand = { p[0] };
    for (int i = 1; i < n + 1; ++i)
    {
        // find prev
        while (prev < i)
        {
            if (minDist < (p[prev].x - p[i].x) * (p[prev].x - p[i].x))
            {
                cand.erase(p[prev++]);
            }
            else
                break;
        }
        int d = (int)sqrt((double)minDist) + 1;
        auto lop = point(-100000, p[i].y - d);
        auto hip = point(100000, p[i].y + d);
        auto lo = cand.lower_bound(lop);
        auto hi = cand.lower_bound(hip);
        for (auto it = lo; it != hi; ++it)
        {
            minDist = min(minDist, dist(*it, p[i]));
        }
        cand.insert(p[i]);
    }

    printf("%d\n", minDist);

    return 0;
}