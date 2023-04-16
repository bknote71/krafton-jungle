#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct point
{
    int x, y;
};
bool cmp(point a, point b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
bool cmp2(point a, point b)
{
    return a.y < b.y;
}

vector<point> p;
const int inf = 2000000000;

int dist(int x1, int x2, int y1, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int closeSet(int left, int right)
{
    if (left + 2 >= right)
    {
        int minL = inf;
        for (int i = left; i < right; ++i)
            for (int j = i + 1; j <= right; ++j)
                minL = min(minL, dist(p[i].x, p[j].x, p[i].y, p[j].y));
        return minL;
    }

    int mid = (left + right) >> 1;
    int minL = min(closeSet(left, mid), closeSet(mid + 1, right));

    vector<point> vt;

    for (int i = left; i < right + 1; ++i)
        if (minL > (p[mid].x - p[i].x) * (p[mid].x - p[i].x))
            vt.push_back(p[i]);

    sort(vt.begin(), vt.end(), cmp2);
    int s = vt.size();
    for (int i = 0; i < s; ++i)
        for (int j = i + 1; j < s; ++j)
        {
            if (minL > (vt[i].y - vt[j].y) * (vt[i].y - vt[j].y))
                minL = min(minL, dist(vt[i].x, vt[j].x, vt[i].y, vt[j].y));
            else
                break;
        }

    return minL;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0, r, c; i < n; ++i)
    {
        cin >> r >> c;
        p.push_back({ r, c });
    }

    sort(p.begin(), p.end(), cmp);

    cout << closeSet(0, n - 1) << '\n';

    return 0;
}