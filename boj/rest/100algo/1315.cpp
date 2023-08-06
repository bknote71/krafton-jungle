#include <iostream>

using namespace std;

typedef struct quest
{
    int str;
    int in;
    int pnt;
};

bool cmp(quest &a, quest &b)
{
    if (a.str == b.str)
        return a.in < b.in;
    return a.str < b.str;
}

int n;
quest arr[51];

int solve(int str, int in)
{

    int pnt = 0;
    int q = 0;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i].str <= str || arr[i].in <= in)
        {
            q++;
            pnt += arr[i].pnt;
        }
    }

    // 포인트 분배
    int ret = 0;
    for (int i = 0; i < pnt; ++i)
    {
        ret = max(ret, solve(str + pnt - i, in + i));
    }

    return ret + q;
}

int main()
{

    for (int i = 0; i < n; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        arr[i] = { a, b, c };
    }

    cout << solve(1, 1) << '\n';

    return 0;
}