#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> vt(100001);

void rightdfs(int node)
{
    int left = vt[node].first;
    int right = vt[node].second;
    if (left != 0)
        rightdfs(left);
    if (right != 0)
        rightdfs(right);
    cout << node << '\n';
}

int parent[100003];

// 아니 이게 왜 안대;;
int main()
{
    int n, root = -1, prev = 100001, cur;
    while (cin >> n)
    {
        if (n == -1)
            break;
        if (root == -1)
        {
            cur = root = n;
            continue;
        }

    start:
        if (n < cur)
        {
            vt[cur].first = n;
            parent[n] = cur;
            // printf("f %d %d\n", cur, vt[cur].first);
        }
        else if (cur < n && n < prev)
        {
            vt[cur].second = n;
            parent[n] = cur;
            // printf("s %d %d\n", cur, vt[cur].second);
        }
        else
        {
            cur = prev;
            prev = cur == root ? 100001 : parent[cur];
            // printf("빠꾸 후 %d %d\n", cur, prev);
            goto start;
        }

        prev = cur;
        cur = n;
    }

    rightdfs(root);
    return 0;
}