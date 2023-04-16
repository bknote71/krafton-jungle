#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> lis;

    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        auto it = lower_bound(lis.begin(), lis.end(), t);

        if (it == lis.end())
            lis.push_back(t);
        else
        {
            printf("it: %d\n", *it);
            *it = t;
        }
    }

    printf("%lu\n", lis.size());

    return 0;
}