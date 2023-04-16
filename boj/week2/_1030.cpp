#include <cmath>
#include <iostream>

using namespace std;

int s, N, K, R1, R2, C1, C2;

char find_color(int s, int r, int c)
{
    if (s == 0)
        return '0';
    int t = pow(N, s - 1);
    if ((N - K) * t / 2 <= r && r < (N - K) * t / 2 + K * t &&
        (N - K) * t / 2 <= c && c < (N - K) * t / 2 + K * t)
        return '1';

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i * t <= r && r < (i + 1) * t && j * t <= c && c < (j + 1) * t)
                return find_color(s - 1, r - (i * t), c - (j * t));
    return '0';
}

int main()
{

    cin >> s >> N >> K >> R1 >> R2 >> C1 >> C2;

    for (int i = R1; i < R2 + 1; ++i)
    {
        for (int j = C1; j < C2 + 1; ++j)
            cout << find_color(s, i, j);
        cout << '\n';
    }
    return 0;
}