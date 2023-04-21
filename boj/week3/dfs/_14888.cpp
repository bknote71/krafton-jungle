#include <iostream>

using namespace std;

int arr[101];
int vst[101][4];
int opr[4];
int n;

int minvalue = 1000000000;
int maxvalue = -1000000000;

void mindfs(int cur, int value)
{
    if (cur == n)
    {
        minvalue = min(minvalue, value);
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (opr[i] > 0)
        {
            --opr[i];
            if (i == 0)
                mindfs(cur + 1, value + arr[cur]);
            else if (i == 1)
                mindfs(cur + 1, value - arr[cur]);
            else if (i == 2)
                mindfs(cur + 1, value * arr[cur]);
            else
                mindfs(cur + 1, value / arr[cur]);
            ++opr[i];
        }
    }
}

void maxdfs(int cur, int value)
{
    if (cur == n)
    {
        maxvalue = max(maxvalue, value);
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (opr[i] > 0)
        {
            --opr[i];
            if (i == 0)
                maxdfs(cur + 1, value + arr[cur]);
            else if (i == 1)
                maxdfs(cur + 1, value - arr[cur]);
            else if (i == 2)
                maxdfs(cur + 1, value * arr[cur]);
            else
                maxdfs(cur + 1, value / arr[cur]);
            ++opr[i];
        }
    }
}

int main()
{

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cin >> opr[0] >> opr[1] >> opr[2] >> opr[3];

    maxdfs(1, arr[0]);
    cout << maxvalue << '\n';

    mindfs(1, arr[0]);
    cout << minvalue << '\n';

    return 0;
}