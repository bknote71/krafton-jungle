#include <stdio.h>

const int max;

int main()
{
    const int min = 5;

    int n;
    scanf("%d", &n);
    int arr[n];
    int arr2[min];
    int arr3[max];

    for (int i = 0; i < n; ++i)
    {
        arr[i] = i;
        printf("%d\n", arr[i]);
    }

    printf("%d\n", arr3[0]);

    int t;
    printf("%d\n", t);

    // int arr4[2][] = { { 4, 5, 6 }, { 7, 8, 9 } };
    int arr4[][2] = { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7 } };
    printf("arr4 %d\n", *(arr4[3] + 0));
    printf("arr4 %d\n", arr4[3][1]);
    printf("arr4 %d\n", *(arr4[2] + 1));

    int a = 2;
    // 16진수 출력
    printf("%p\n", &a);
    // int값을 부호없는 16진수로 출력  10~15은  'a'~'f'로 표시
    printf("%x \n", &a);

    return 0;
}