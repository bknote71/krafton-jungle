#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;

    string str;
    cin >> str;

    string seg;
    long long ret = 0;
    int scount = 0;

    for (int i = 0; i < str.length(); ++i)
    {
        if ('0' <= str[i] && str[i] <= '9')
        {
            scount++;
            if (scount > 6)
            {
                seg = "";
                continue;
            }
            seg += str[i];
        }
        else
        {
            if (seg.empty())
                continue;
            scount = 0;
            ret = ret + stoll(seg);
            seg = "";
        }
    }

    if (!seg.empty())
        ret += stoll(seg);
    cout << ret << '\n';

    return 0;
}