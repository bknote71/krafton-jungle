# 4월 8일 TIL (Today I Learned)


## parallelized dual pivot quick sort in java

``` java
static void sort(int[] a, int parallelism, int low, int high) {
    int size = high - low;

    // THRESHOLD
    if (parallelism > 1 && size > MIN_PARALLEL_SORT_SIZE) {
        int depth = getDepth(parallelism, size >> 12);
        int[] b = depth == 0 ? null : new int[size];
        new Sorter(null, a, b, low, size, low, depth).invoke();
    } else {
        sort(null, a, 0, low, high);
    }
}

```

MIN_PARALLEL_SORT_SIZE
- THRESHOLD (임계값)
- 병렬적이지 않은 정렬을 할 최소 사이즈이다.


## 순열 및 중복 순열

1. 순열(Permutation)
- 서로 다른 n개의 원소 중에서 r개를 선택하여 일렬로 배열하는 경우의 수
- 이 때, 원소의 순서가 중요하므로 순서를 고려해야 한다. 
- nPr

``` python
def nPr(n, r):
    if r == 0:
        print(npr)
        return

    for next in range(n):
        if not vst[next]:
            vst[next] = True
            npr.append(arr[next])
            nPr(n, r - 1)
            npr.pop()
            vst[next] = False

```

2. 조합(Combination)
- 서로 다른 n개의 원소 중에서 r개를 선택하는 경우의 수
- 이 때, 원소의 순서는 고려하지 않는다.
- nCr

``` python
def nCrv1(n, r):
    if r == 0:
        print(ncr)
        return

    for next in range(len(ncr), n):
        if not vst[next]:
            vst[next] = True
            ncr.append(arr[next])
            nCrv1(n, r - 1)
            ncr.pop()
            vst[next] = False


def nCrv2(n, r, prev):
    if r == 0:
        print(ncr)
        return

    for next in range(prev + 1, n):
        if not vst[next]:
            vst[next] = True
            ncr.append(arr[next])
            nCrv2(n, r - 1, next)
            ncr.pop()
            vst[next] = False
```

3. 중복 순열(Permutation with repetition)
- 서로 다른 n개의 원소 중에서 중복을 허용하여 r개를 선택하여 일렬로 배열하는 경우의 수
- 이 때, 원소의 순서가 중요하므로 순서를 고려해야 한다.
- n^r

``` python
def nPr(n, r):
    if r == 0:
        print(npr)
        return

    for next in range(n):
        npr.append(arr[next])
        nPr(n, r - 1)
        npr.pop()

```

4. 중복 조합(Combination with repetition)
- 서로 다른 n개의 원소 중에서 중복을 허용하여 r개를 선택하는 경우의 수
- 이 때, 원소의 순서는 고려하지 앟는다.
- nHr = (n+r-1)Cr

``` python
def nHr(n, r, prev):
    if r == 0:
        print(ncr)
        return

    for next in range(prev, n):
        ncr.append(arr[next])
        nCr(n, r - 1, next)
        ncr.pop()
```

## 이분 탐색 (Binary Search)

- 결정 문제 (Yes or No)
- 답이 이분적일 때
- TTTTTTTFFFFFFF or FFFFFFFTTTTTTT

### 불변식
- while(lo + 1 < hi)
- lo < mid < hi
- while 루프를 벗어난다면 lo + 1 == hi 이다.

많은 최적화 문제(최대값 or 최솟값)를 이분 탐색을 통해서 해결할 수 있다.

### 최대값:
- TTTTTTTFFFFFFF
- 조건을 만족 O: lo 를 mid 로 올린다.
- 조건을 만족 X: hi 를 mid 로 내린다.
- lo 는 평생 조건을 만족, hi 는 평생 조건을 만족하지 못한다.
- 초기값: lo = T, hi = F (F는 불가능한 값)


### 최소값:
- FFFFFFFTTTTTTT
- 조건을 만족 O: hi 를 mid 로 내린다.
- 조건을 만족 X: lo 를 mid 로 올린다.
- hi 는 평생 조건을 만족, lo 는 평생 조건을 만족하지 못한다.
- 초기값: lo = F, hi = T 

예제: 나무 자르기 (https://www.acmicpc.net/problem/2805)

``` c
#include <stdio.h>

int height[10000000];

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &height[i]);
    }

    // 최대값: lo = T, hi = F
    int lo = 0, hi = 1000000000;

    while (lo + 1 < hi)
    {
        int mid = (lo + hi) / 2;
        long long sum = 0;
        for (int i = 0; i < N; ++i)
        {
            int th = height[i] - mid;
            sum += th > 0 ? th : 0;
        }

        if (sum >= M)
        {
            lo = mid;
        }
        else
            hi = mid;
    }
    printf("%d\n", lo);

    return 0;
}
```