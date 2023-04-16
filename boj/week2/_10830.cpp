#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int N;
long long B;

vector<vector<ll>> mul(vector<vector<ll>> M, vector<vector<ll>> L)
{
    vector<vector<ll>> ret;

    for (int i = 0; i < N; ++i)
    {
        vector<ll> vt;
        for (int j = 0; j < N; ++j)
        {
            ll temp = 0;
            for (int k = 0; k < N; ++k)
            {
                temp = (temp + M[i][k] * L[k][j]) % 1000;
            }
            vt.push_back(temp);
        }
        ret.push_back(vt);
    }
    return ret;
}

vector<vector<ll>> solve(vector<vector<ll>> A, ll BB)
{
    if (BB == 1)
        return A;

    vector<vector<ll>> t = solve(A, BB / 2);
    vector<vector<ll>> t2 = mul(t, t);

    if (BB % 2 == 1)
        return mul(t2, A);

    return t2;
}

int main()
{
    scanf("%d %lld", &N, &B);

    vector<vector<ll>> M;

    for (int i = 0; i < N; ++i)
    {
        vector<ll> temp;
        for (int j = 0, t; j < N; ++j)
        {
            cin >> t;
            temp.push_back(t % 1000);
        }
        M.push_back(temp);
    }

    vector<vector<ll>> ret = solve(M, B);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printf("%lld ", ret[i][j]);
        printf("\n");
    }
    return 0;
}