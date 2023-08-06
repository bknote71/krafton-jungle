#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;

pair<ll, ll> find_coord(string x, ll i)
{
    if (i == x.length())
    {
        return { 0, 0 };
    }
    ll d = pow(2, x.length() - i - 1);
    if (x[i] == '1')
    {
        pair<ll, ll> coor = find_coord(x, i + 1);
        return { coor.first, coor.second + d };
    }
    else if (x[i] == '2')
    {
        pair<ll, ll> coor = find_coord(x, i + 1);
        return { coor.first, coor.second };
    }
    else if (x[i] == '3')
    {
        pair<ll, ll> coor = find_coord(x, i + 1);
        return { coor.first + d, coor.second };
    }
    else if (x[i] == '4')
    {
        pair<ll, ll> coor = find_coord(x, i + 1);
        return { coor.first + d, coor.second + d };
    }
}

void solve(ll x, ll y, ll n)
{
    if (n == 0)
        return;
    ll d = pow(2, n - 1);
    if (x < d && y < d)
    {
        std::cout << 2;
        solve(x, y, n - 1);
    }
    else if (x < d && y >= d)
    {
        cout << 1;
        solve(x, y - d, n - 1);
    }
    else if (x >= d && y < d)
    {
        cout << 3;
        solve(x - d, y, n - 1);
    }
    else
    {
        cout << 4;
        solve(x - d, y - d, n - 1);
    }
}

int main()
{
    ll n, x, y;
    string str;
    cin >> n >> str;
    cin >> x >> y;

    // find coord
    pair<ll, ll> coord = find_coord(str, 0);
    // printf("coord: %d %d\n", coord.first, coord.second);

    ll nx = coord.first - y;
    ll ny = coord.second + x;
    ll d = pow(2, n);
    if (nx < 0 || nx >= d || ny < 0 || ny >= d)
        cout << -1 << '\n';
    else
        solve(nx, ny, n);

    return 0;
}