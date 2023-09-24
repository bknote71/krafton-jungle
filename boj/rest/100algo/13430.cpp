#include <iostream>

using namespace std;

typedef long long ll;

const ll mod = 1000000007;

int k, n;
ll arr[55][55];
ll ans[55][55];

void mul(ll x[55][55], ll y[55][55])
{
    ll temp[55][55] = {
        0,
    };

    for (int i = 0; i < k + 2; ++i)
    {
        for (int j = 0; j < k + 2; ++j)
        {
            for (int t = 0; t < k + 2; ++t)
                temp[i][j] = (temp[i][j] + (x[i][t] * y[t][j]) % mod) % mod;
        }
    }

    // temp to x
    for (int i = 0; i < 55; ++i)
    {
        for (int j = 0; j < 55; ++j)
            x[i][j] = temp[i][j];
    }
}

int main()
{
    cin >> k >> n;

    // 정답 행렬을 단위 행렬로 초기화
    for (int i = 0; i < k + 2; ++i)
        ans[i][i] = 1;

    for (int i = 0; i < k + 2; ++i)
        for (int j = 0; j < i + 1; ++j)
            arr[i][j] = 1;

    n--;

    while (n > 0)
    {
        if (n % 2 == 1)
            mul(ans, arr);

        mul(arr, arr);
        n /= 2;
    }

    ll sum = 0;

    for (int i = 0; i < k + 2; ++i)
    {
        sum = (sum + ans[k + 1][i]) % mod;
    }

    cout << sum << '\n';

    return 0;
}