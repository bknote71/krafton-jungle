#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[20][20], t_arr[20][20];

void print_arr(int parr[20][20])
{
    printf("------------------\n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", parr[i][j]);
        }
        printf("\n");
    }
    printf("------------------\n");
}

void sumtocn(int sarr[20][20]) // n 쪽으로 합치기, d: 열방향, 행방향 합치기
{
    // shallow copy
    // printf("cn\n");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            t_arr[i][j] = sarr[i][j];

    for (int c = 0; c < n; ++c)
    {
        int pos = 0, iter = 1;
        while (pos < n - 1 && iter < n)
        {
            if (t_arr[iter][c] == 0)
            {
                iter++;
                continue;
            }

            if (t_arr[pos][c] == 0)
            {
                t_arr[pos][c] += t_arr[iter][c];
                t_arr[iter][c] = 0;
                continue;
            }
            else if (t_arr[pos][c] == t_arr[iter][c])
            {
                t_arr[pos][c] += t_arr[iter][c];
                t_arr[iter][c] = 0;
            }
            else
            {
                t_arr[pos + 1][c] = t_arr[iter][c];
                if (pos + 1 != iter)
                    t_arr[iter][c] = 0;
            }

            pos++;
            iter = pos + 1;
        }
    }
    // printf("cn 완\n");
}
void sumtorn(int sarr[20][20]) // n 쪽으로 합치기, d: 열방향, 행방향 합치기
{
    // shallow copy
    // printf("rn\n");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            t_arr[i][j] = sarr[i][j];

    for (int r = 0; r < n; ++r)
    {
        int pos = 0, iter = 1;
        while (pos < n - 1 && iter < n)
        {
            if (t_arr[r][iter] == 0)
            {
                iter++;
                continue;
            }

            if (t_arr[r][pos] == 0)
            {
                t_arr[r][pos] += t_arr[r][iter];
                t_arr[r][iter] = 0;
                continue;
            }
            else if (t_arr[r][pos] == t_arr[r][iter])
            {
                t_arr[r][pos] += t_arr[r][iter];
                t_arr[r][iter] = 0;
            }
            else
            {
                t_arr[r][pos + 1] = t_arr[r][iter];
                if (pos + 1 != iter)
                    t_arr[r][iter] = 0;
            }

            pos++;
            iter = pos + 1;
        }
    }
    // printf("rn 완\n");
}

void sumtoc0(int sarr[20][20]) // n 쪽으로 합치기, d: 열방향, 행방향 합치기
{
    // shallow copy
    // printf("c0\n");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            t_arr[i][j] = sarr[i][j];

    for (int c = 0; c < n; ++c)
    {
        int pos = n - 1, iter = n - 2;
        while (pos >= 1 && iter >= 0)
        {
            // printf("pos:%d, iter:%d\n", pos, iter);
            if (t_arr[iter][c] == 0)
            {
                iter--;
                continue;
            }

            if (t_arr[pos][c] == 0)
            {
                t_arr[pos][c] += t_arr[iter][c];
                t_arr[iter][c] = 0;
                continue;
            }
            else if (t_arr[pos][c] == t_arr[iter][c])
            {
                t_arr[pos][c] += t_arr[iter][c];
                t_arr[iter][c] = 0;
            }
            else
            {
                t_arr[pos - 1][c] = t_arr[iter][c];
                if (pos - 1 != iter)
                    t_arr[iter][c] = 0;
            }

            pos--;
            iter = pos - 1;
        }
    }
    // printf("c0 완\n");
}

void sumtor0(int sarr[20][20]) // n 쪽으로 합치기, d: 열방향, 행방향 합치기
{
    // shallow copy
    // printf("r0\n");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            t_arr[i][j] = sarr[i][j];

    for (int r = 0; r < n; ++r)
    {
        int pos = n - 1, iter = n - 2;
        while (pos >= 1 && iter >= 0)
        {
            if (t_arr[r][iter] == 0)
            {
                iter--;
                continue;
            }

            if (t_arr[r][pos] == 0)
            {
                t_arr[r][pos] += t_arr[r][iter];
                t_arr[r][iter] = 0;
                continue;
            }
            else if (t_arr[r][pos] == t_arr[r][iter])
            {
                t_arr[r][pos] += t_arr[r][iter];
                t_arr[r][iter] = 0;
            }
            else
            {
                t_arr[r][pos - 1] = t_arr[r][iter];
                if (pos - 1 != iter)
                    t_arr[r][iter] = 0;
            }

            pos--;
            iter = pos - 1;
        }
    }
    // printf("r0완\n");
}

int maxvalue;

void solve(int sarr[20][20], int cnt)
{
    if (cnt == 0)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                maxvalue = max(maxvalue, sarr[i][j]);
        return;
    }

    int tmp[20][20];

    sumtocn(sarr);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            tmp[i][j] = t_arr[i][j];
    solve(tmp, cnt - 1);

    sumtorn(sarr);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            tmp[i][j] = t_arr[i][j];
    solve(tmp, cnt - 1);

    sumtoc0(sarr);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            tmp[i][j] = t_arr[i][j];
    solve(tmp, cnt - 1);

    sumtor0(sarr);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            tmp[i][j] = t_arr[i][j];
    solve(tmp, cnt - 1);
}

int main()
{
    cin >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> arr[i][j];

    solve(arr, 5);
    cout << maxvalue << '\n';

    // sumtocn(arr);
    // print_arr(t_arr);

    // sumtorn(arr);
    // print_arr(t_arr);

    // sumtoc0(arr);
    // print_arr(t_arr);

    // sumtor0(arr);
    // print_arr(t_arr);

    return 0;
}