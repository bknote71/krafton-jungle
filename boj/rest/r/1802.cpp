#include <iostream>
#include <string>

using namespace std;

string str;

bool solve(int lo, int hi, int idx)
{
    if (lo == hi)
        return true; // ?? 이게 맞나?

    int mid = (lo + hi) / 2;

    if (mid == idx)
        return true;

    if (idx < mid && str[idx] != str[mid + (mid - idx)])
        return solve(lo, mid - 1, idx);
    else if (idx > mid)
        return solve(mid + 1, hi, idx);

    return false;
}

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        cin >> str;
        int ret = 1;

        for (int i = 0; i < str.length(); ++i)
        {
            ret = solve(0, str.length() - 1, i);
            if (ret == 0)
                break;
        }

        if (ret)
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
    }
    return 0;
}

/*
if (str[mid] == '0')
    {
        if (str[lmid] != str[rmid])
            ret = solve(lo, mid - 1, dir) && solve(mid + 1, hi, 1 - dir);
        else
            return false;
    }
    else if (str[mid] == '1')
    {
        if (str[lmid] != str[rmid])
            ret = solve(lo, mid - 1, 1 - dir) && solve(mid + 1, hi, dir);
        else
            return false;
    }
*/