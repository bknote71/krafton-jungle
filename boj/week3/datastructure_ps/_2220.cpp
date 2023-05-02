#include <iostream>

using namespace std;

int arr[100000];
void swap(int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
int main(void)
{
    int n;
    cin >> n;

    arr[1] = 1;
    for (int i = 2; i < n + 1; i++)
    {
        arr[i] = i;

        // 1과 i 바꾸기
        swap(i - 1, i);

        // 최대힙 구성
        for (int j = i - 1; j > 1; j /= 2)
        {
            swap(j, j / 2);
        }
    }

    for (int i = 1; i <= n; i++)
        cout << arr[i] << " ";
    return 0;
}