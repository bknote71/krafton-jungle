#include <iostream>

using namespace std;

int tree[100001];

void rightdfs(int lo, int hi)
{
    if (lo >= hi)
        return;

    if (lo + 1 == hi)
    {
        cout << tree[lo] << '\n';
        return;
    }
    int rIdx = lo + 1;

    while (rIdx < hi && tree[rIdx] < tree[lo])
    {
        rIdx++;
    }
    rightdfs(lo + 1, rIdx);
    rightdfs(rIdx, hi);
    cout << tree[lo] << '\n';
}

int main()
{
    int n, idx = 0;

    while (cin >> n)
    {
        tree[idx++] = n;
    }

    rightdfs(0, idx);

    return 0;
}