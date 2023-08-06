#include <iostream>

using namespace std;

int prime[10000001];

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < 10000001; ++i)
    {
        prime[i] = true;
    }

    prime[0] = prime[1] = 1;

    for (int i = 2; i * i <= n; ++i)
        if (prime[i])
        {
            for (int j = i * i; j <= n; j += i)
                prime[j] = 0;
        }

    int p = 2;

    while (n > 1 && p <= n)
    {
        if (prime[p] == 1 && (n % p) == 0)
        {
            cout << p << '\n';
            n /= p;
        }
        else
            ++p;
    }

    return 0;
}