#include <iostream>
#include <vector>

using namespace std;

vector<pair<char, char>> vt(30);
void leftdfs(char node)
{
    cout << node;
    char left = vt[node - 'A'].first;
    char right = vt[node - 'A'].second;
    if (left != '.')
        leftdfs(left);
    if (right != '.')
        leftdfs(right);
}

void middfs(char node)
{
    char left = vt[node - 'A'].first;
    char right = vt[node - 'A'].second;
    if (left != '.')
        middfs(left);
    cout << node;
    if (right != '.')
        middfs(right);
}

void rightdfs(char node)
{
    char left = vt[node - 'A'].first;
    char right = vt[node - 'A'].second;
    if (left != '.')
        rightdfs(left);
    if (right != '.')
        rightdfs(right);
    cout << node;
}
int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        char A, B, C;
        cin >> A >> B >> C;
        vt[A - 'A'].first = B;
        vt[A - 'A'].second = C;
    }

    leftdfs('A');
    cout << '\n';
    middfs('A');
    cout << '\n';
    rightdfs('A');
    cout << '\n';

    return 0;
}