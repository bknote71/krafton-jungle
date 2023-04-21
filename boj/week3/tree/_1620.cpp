#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, string> stoimap;
map<string, string> itosmap;

bool isInteger(string s)
{
    try
    {
        int num = stoi(s);
        return true;
    }
    catch (invalid_argument e)
    {
        return false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i < n + 1; ++i)
    {
        string x;
        cin >> x;
        stoimap.insert({ x, to_string(i) });
        itosmap.insert({ to_string(i), x });
    }

    for (int i = 0; i < m; ++i)
    {
        string x;
        cin >> x;
        auto ret = isInteger(x) ? itosmap.find(x) : stoimap.find(x);
        cout << ret->first << ' ' << ret->second << '\n';
    }

    return 0;
}