#include <algorithm>
#include <iostream>

using namespace std;

const int SIZE = 1 << 18; // 75000 * 2;
typedef long long ll;

struct SegTree
{
    int arr[SIZE];
    SegTree() { fill(arr, arr + SIZE, 0); }
    void inc(int n)
    {
        n += SIZE / 2;
        while (n > 0)
        {
            arr[n]++;
            n /= 2;
        }
    }
    int sum(int s, int e) { return sum(s, e, 1, 0, SIZE / 2); }
    int sum(int s, int e, int node, int ns, int ne)
    {
        if (e <= ns || ne <= s)
            return 0;
        if (s <= ns && ne <= e)
            return arr[node];
        int mid = (ns + ne) / 2;
        return sum(s, e, node * 2, ns, mid) + sum(s, e, node * 2 + 1, mid, ne);
    }
};

bool cmp(const pair<int, int> &u, const pair<int, int> &v)
{
    if (u.first == v.first)
        return u.second > v.second;
    return u.first < v.first;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        SegTree ST;

        int N;
        cin >> N;

        vector<pair<int, int>> p(N);

        for (int i = 0; i < N; ++i)
        {
            cin >> p[i].first >> p[i].second;
        }

        sort(p.begin(), p.end(), [](pair<int, int> &u, pair<int, int> &v)
             { return u.second < v.second; });
        // 서로 구분되는 y좌표 개수를 세며 y좌표 재설정 << 구간 트리: 0 부터 끝까지 == 그렇기 때문에 음수 y좌표를 옮겨야 함 + 정규화 (그냥 모아놓는다고 보면 된다.)
        int newY[750000], range = 0;
        for (int i = 0; i < N; i++)
        {
            if (i > 0 && p[i].second != p[i - 1].second)
                range++;
            newY[i] = range;
        }
        for (int i = 0; i < N; i++)
            p[i].second = newY[i];
        sort(p.begin(), p.end(), cmp);
        ll result = 0;
        for (int i = 0; i < N; ++i)
        {
            result += ST.sum(p[i].second, SIZE / 2);
            ST.inc(p[i].second);
        }

        cout << result << '\n';
    }
    return 0;
}
