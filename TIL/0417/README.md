# Weekly I Learned (0411 ~ 0417)


## 알고리즘 주차
- 개념 정리 및 문제 풀이 정리 (배울만한 점 체크)

## 에라토스테네스의 체
- 소수 구하는 알고리즘
- 소수의 배수는 소수가 아니기 때문에 이를 거르는 방법이다.
- 0410 TIL 에 정리!!

## 순열 및 조합
- 말 그대로 순열 및 조합 + 중복 순열 및 중복 조합

### 순열 (permutation)
- 순서가 있는 배열
- 수를 선택하여 나열
- nPr (n 개 중에서 r 개를 선택하여 나열)

``` python
arr = ['A', 'B', 'C']

npr = []
vst = [False for i in range(len(arr))]


def nPr(n, r):
    if r == 0:
        print(npr)
        return

    for next in range(n):
        if not vst[next]:
            # vst 배열로 한 번 npr 배열에 담은 요소는 담지 않도록 한다.
            vst[next] = True
            # arr[next]요소를 npr 배열에 담는다.
            npr.append(arr[next])
            nPr(n, r - 1)
            npr.pop()
            vst[next] = False


nPr(len(arr), 3)
```

### 조합 (combination)
- 순서 없이 뽑기만한 배열
- 수를 선택만 한다.
- nCr (n 개 중에서 r 개를 선택)

``` python
arr = ['A', 'B', 'C']

def nCr(n, r, prev):
    if r == 0:
        print(ncr)
        return

    # prev(전에 선택한 수) 이후부터 선택하게 하여 중복 선택을 막는다. 
    for next in range(prev + 1, n):
        if not vst[next]:
            vst[next] = True
            ncr.append(arr[next])
            nCrv2(n, r - 1, next)
            ncr.pop()
            vst[next] = False


nCr(3, 1, -1)
nCr(3, 2, -1)
nCr(3, 3, -1)
```

### 중복 순열 (repetive permutation)
- 수를 중복해서 선택한 후 나열
- n^r

``` python
arr = ['A', 'B', 'C']

npr = []
vst = [False for i in range(len(arr))]


def nPr(n, r):
    if r == 0:
        print(npr)
        return

    # not vst 배열 << 중복해서 담을 수 있기 때문에
    for next in range(n):
        npr.append(arr[next])
        nPr(n, r - 1)
        npr.pop()


nPr(3, 1)
nPr(3, 2)
nPr(3, 3)
```

### 중복 조합 (repetive combination)
- 수를 중복해서 선택
- nHr

``` python
arr = ['A', 'B', 'C']

ncr = []
vst = [False for i in range(len(arr))]


def nHr(n, r, prev):
    if r == 0:
        print(ncr)
        return
    
    # prev(전에 선택한 수)부터 선택할 수 있게 한다.
    for next in range(prev, n):
        ncr.append(arr[next])
        nCr(n, r - 1, next)
        ncr.pop()


nHr(3, 1, 0)
nHr(3, 2, 0)
nHr(3, 3, 0)
```

예제: 차이를 최대로 (https://www.acmicpc.net/problem/10819)
- 수열 사용
``` python
N = int(input())
A = [0 for j in range(N)]
B = []

chk = [False for i in range(N)]
maxValue = 0

arr = input().split()

for i in range(N):
    A[i] = int(arr[i])


def permutation(cnt):
    global maxValue
    if cnt == N:
        result = 0
        for i in range(N - 1):
            result += abs(B[i] - B[i + 1])
        maxValue = max(maxValue, result)
        
    for i in range(N):
        if chk[i] == False:
            chk[i] = True
            B.append(A[i])
            permutation(cnt + 1)
            B.pop()
            chk[i] = False


permutation(0)
print(maxValue)
```

## 완전 탐색 (브루트 포스)
- 모든 경우의 수를 모두 확인하는 방법이다.
- 모든 경우의 수를 확인하기 때문에 시간 복잡도가 높다.

예제: 외판원 순회 2 (https://www.acmicpc.net/problem/10971)
- 포인트 1: 어느 도시에서나 출발해도 된다. (출발 도시: 0번)
- 포인트 2: 현재 도시에서 방문하지 않은 모든 도시를 갈 수 있으면 가보도록 한다.
- 포인트 3: count 라는 변수를 재귀함수 호출 시에 같이 넘겨 cnt == N - 1 일 때, 즉 모든 도시를 돌아봤을 때 다시 출발 도시(0번 도시)로 돌아올 수 있게 한다.
- 포인트 4: 다시 출발 도시로 돌아올 때 돌아올 수 없는 경우 (W == 0) 일 때 infinite 값을 던진다. (최소 비용 구하는 문제기 때문에 이 경우 값이 무시된다고 생각하면 된다.)

``` python
N = int(input())
W = [[0 for j in range(N + 1)] for i in range(N + 1)]

vst = [False for i in range(N + 1)]


def travel(currentnode, cnt):
    if cnt == N - 1:
        if W[currentnode][0] != 0:
            return W[currentnode][0]
        else:
            return 1000000000

    sum = 1000000000
    for nextnode in range(N):
        if nextnode != currentnode and vst[nextnode] == False and W[currentnode][nextnode] != 0:
            vst[nextnode] = True
            sum = min(sum, W[currentnode][nextnode] +
                      travel(nextnode, cnt + 1))
            vst[nextnode] = False

    return sum


for i in range(N):
    arr = input().split()
    for j in range(N):
        W[i][j] = int(arr[j])

vst[0] = True
print(int(travel(0, 0)))
```

예제: 안전 영역 (https://www.acmicpc.net/source/58928159)
- 포인트 1: 물에 잠긴 영역을 컬러링 한다.
- 포인트 2: 한 번 컬러링 된 영역은 다시 할 필요가 없다. (계속 물에 잠기기 때문에)
- 포인트 3: 컬러링 한 이후 고립된 영역을 카운트한다.
- 포인트 4: 컬러링 방법을 2가지로 구현함 (재귀 vs map)
``` java
// 컬러링 방법 1: 재귀 호출을 사용한 완전 탐색
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

    static int[][] box = new int[100][100];
    static int[] dx = {0, 1, 0, -1};
    static int[] dy = {1, 0, -1, 0};

    static boolean[][] fld = new boolean[100][100];
    static boolean[][] chk = new boolean[100][100];

    static int N, minh = 1000, maxh = 0;


    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        N = Integer.valueOf(in.readLine());

        for (int i = 0; i < N; ++i) {
            String[] tls = in.readLine().split(" ");
            for (int j = 0; j < N; ++j) {
                box[i][j] = Integer.valueOf(tls[j]);
                minh = Math.min(minh, box[i][j]);
                maxh = Math.max(maxh, box[i][j]);
            }
        }

        int ret = 1;

        for (int h = minh; h < maxh; ++h) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    chk[i][j] = false;
                }
            }

            int cand = 0;
            // find and flood
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (box[i][j] <= h && !fld[i][j]) {
                        flood(i, j, h);
                    }
                }
            }
            // check
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (!fld[i][j] && !chk[i][j]) {
                        check(i, j, h);
                        ++cand;
                    }
                }
            }
            ret = Math.max(ret, cand);
        }

        System.out.println(ret);
    }

    private static void flood(int r, int c, int h) {
        fld[r][c] = true;

        for (int d = 0; d < 4; ++d) {
            int nr = r + dx[d];
            int nc = c + dy[d];

            if (floodbound(nr, nc) && box[nr][nc] <= h) {
                flood(nr, nc, h);
            }
        }
    }

    private static boolean floodbound(int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N || fld[r][c]) {
            return false;
        }
        return true;
    }

    private static void check(int r, int c, int h) {
        chk[r][c] = true;

        for (int d = 0; d < 4; ++d) {
            int nr = r + dx[d];
            int nc = c + dy[d];

            if (checkbound(nr, nc) && box[nr][nc] > h) {
                check(nr, nc, h);
            }
        }
    }

    private static boolean checkbound(int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N || chk[r][c]) {
            return false;
        }
        return true;
    }
}
// 컬러링 방법 2: "높이에 대응하는 좌표"를 미리 매핑하여 for 루프에서 h를 증가시키면서 h 에 대응하는 좌표만 색칠한다.
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {

    static int[][] box = new int[100][100];
    static int[] dx = {0, 1, 0, -1};
    static int[] dy = {1, 0, -1, 0};

    static boolean[][] clr = new boolean[100][100];
    static boolean[][] chk = new boolean[100][100];

    static int N, minh = 1000, maxh = 0;

    static Map<Integer, List<Point>> map = new HashMap<>();

    static class Point {
        int r, c;

        public Point(int i, int j) {
            r = i;
            c = j;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        N = Integer.valueOf(in.readLine());

        for (int i = 0; i <= 100; ++i) {
            map.put(i, new ArrayList<>());
        }

        for (int i = 0; i < N; ++i) {
            String[] tls = in.readLine().split(" ");
            for (int j = 0; j < N; ++j) {
                box[i][j] = Integer.valueOf(tls[j]);
                minh = Math.min(minh, box[i][j]);
                maxh = Math.max(maxh, box[i][j]);

                List<Point> points = map.get(box[i][j]);
                points.add(new Point(i, j));
            }
        }



        int ret = 1;

        for (int h = minh; h < maxh; ++h) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    chk[i][j] = false;
                }
            }
            int cand = 0;
            // coloring
            List<Point> points = map.get(h);
            for (Point point : points) {
                clr[point.r][point.c] = true;
            }

            // check
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (!clr[i][j] && !chk[i][j]) {
                        check(i, j, h);
                        ++cand;
                    }
                }
            }
            ret = Math.max(ret, cand);
        }

        System.out.println(ret);
    }

    private static void flood(int r, int c, int h) {
        clr[r][c] = true;

        for (int d = 0; d < 4; ++d) {
            int nr = r + dx[d];
            int nc = c + dy[d];

            if (floodbound(nr, nc) && box[nr][nc] <= h) {
                flood(nr, nc, h);
            }
        }
    }

    private static boolean floodbound(int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N || clr[r][c]) {
            return false;
        }
        return true;
    }

    private static void check(int r, int c, int h) {
        chk[r][c] = true;

        for (int d = 0; d < 4; ++d) {
            int nr = r + dx[d];
            int nc = c + dy[d];

            if (checkbound(nr, nc) && box[nr][nc] > h) {
                check(nr, nc, h);
            }
        }
    }

    private static boolean checkbound(int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N || chk[r][c]) {
            return false;
        }
        return true;
    }
}
```

## 이분 탐색 (Binary Search)
- 결정 문제(True or False) + 답을 이분하는 경우
- 0408 TIL 에 정리!

예제: 두 용액 (https://www.acmicpc.net/problem/2470)
- 포인트 1: 두 수의 합이 0과 비슷해져야 한다.
- 포인트 2: 음수의 경우 양수로 변환하고, 해당 값과 가장 근처에 있는 두 수를 찾는다.
- 포인트 3: 이 때 이분탐색을 이용한다.
- 포인트 4: 이분 탐색을 "요소" 의 인덱스를 찾는데 사용하기 때문에 요소를 정렬해야 한다.

``` cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int inf = 1000000000;

int N;

int main()
{
    cin >> N;
    vector<int> vt(N);
    for (int i = 0, t; i < N; ++i)
    {
        cin >> t;
        vt[i] = t;
    }

    sort(vt.begin(), vt.end());
    int minValue = inf * 2;
    int left = -1, right = -1;

    for (int i = 0; i < N - 1; ++i)
    {
        int lo = i + 1, hi = N - 1, org = vt[i], to = abs(vt[i]);
        // 항상 lo < mid < hi
        // while 문을 벗어나면 lo + 1 == hi !!!!
        while (lo + 1 < hi)
        {
            int mid = (lo + hi) >> 1;
            // 불변식: 항상 vt[lo] < to
            if (vt[mid] < to)
                lo = mid;
            else
                hi = mid;
        }

        if (abs(org + vt[lo]) < minValue)
        {
            minValue = abs(org + vt[lo]);
            left = i;
            right = lo;
        }

        if (abs(org + vt[hi]) < minValue)
        {
            minValue = abs(org + vt[hi]);
            left = i;
            right = hi;
        }
    }
    printf("%d %d\n", vt[left], vt[right]);

    return 0;
}
```
- 사냥꾼 (https://www.acmicpc.net/problem/8983) 도 동일한 맥락

### lower_bound, upper_bound

- lower_bound: 검색 범위 내에서 주어진 값 이상인 첫 번째 요소를 반환
- upper_bound: 검색 범위 내에서 주어진 값보다 큰 첫 번째 요소를 반환

예제: 가장 긴 증가하는 부분 수열 2 (https://www.acmicpc.net/problem/12015)
- 포인트 1: 기존 dp 방식으로 해결하면 O(n^2) 으로, 시간 초과가 발생한다.
- 포인트 2: 정확하게 어떤 요소가 들어가 있는지 구할 필요가 없다.
- 포인트 3: 즉, 가장 긴 길이만 구하면 된다.
- 포인트 4: 후보 배열의 가장 끝 요소보다 크면 그냥 push한다. 
- 포인트 5: 후보 배열의 가장 끝 요소보다 작다면 현재 요소가 들어갈 수 있는 후보를 찾은 후 이를 대치시킨다.
- 포인트 6: 대치시켜도 되는 이유는 대치된 요소가 실제로 가장 긴 증가하는 부분 수열에 일부라도 그것을 알 필요가 없고, 새롭게 증가하는 부부 수열의 후보가 될 수 있는 새로운 요소가 후보 배열에 들어가야하기 때문이다.
- 포인트 7: 이 때, 후보 배열은 정렬된 상태이므로 이분 탐색으로 위치를 찾을 수 있다.
- 포인트 8: 이를 "lower_bound" 로 찾는다.


``` cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> lis;

    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        auto it = lower_bound(lis.begin(), lis.end(), t);

        if (it == lis.end())
            lis.push_back(t);
        else
            *it = t;
    }

    printf("%lu\n", lis.size());

    return 0;
}
```
- 가장 긴 증가하는 부분 수열 5(https://www.acmicpc.net/problem/14003)의 경우 실제 구성하는 부분 수열을 구해야 한다.
- 나중에 해결해보자!!

## 분할 정복 (Divide and Conquer)
- 큰 문제를 작은 문제로 분할하여 해결하고 이를 합치는 알고리즘이다.
- 합병 정렬(merge sort), 퀵 정렬(quick sort), ... 등에서 사용되는 알고리즘이다.
  
예제: 곱셈 (https://www.acmicpc.net/problem/1629)
- 포인트 1: A 를 B 번 곱해야 하는데 B가 21억이므로 for문으로 계속 곱하게 되면 시간초과가 발생한다.
- 포인트 2: A 를 B/2 번 곱하고 동일한 값을 두 개를 곱함으로써 시간 복잡도 문제를 해결하도록 한다.
  - 시간 복잡도: T(N) = T(N/2) + 1, T(N) = O(Nlog(N))
- 포인트 3: x = a * b 일 때, x % c == (a % c) * (b % c) % c 와 동일하다.

``` c
#include <stdio.h>

typedef long long ll;

ll A, B, C;

ll solve(ll x, ll y)
{
    if (y == 1)
        return x % C;
    ll t1 = solve(x, y / 2);
    return ((t1 * t1) % C * (y % 2 == 0 ? 1 : x)) % C;
}

int main()
{
    scanf("%lld %lld %lld", &A, &B, &C);
    printf("%lld\n", solve(A, B));
    return 0;
}
```

예제: 행렬 제곱 (https://www.acmicpc.net/problem/10830)
- 위 제곱 문제와 거의 동일하다.
- 다만 수를 곱하는 것이 아닌 행렬을 곱하는 것으로만 변경해주면 된다!!
- T[i][j] = M[i][k] * L[k][j]

``` cpp
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int N;
long long B;

vector<vector<ll>> mul(vector<vector<ll>> M, vector<vector<ll>> L)
{
    vector<vector<ll>> ret;

    for (int i = 0; i < N; ++i)
    {
        vector<ll> vt;
        for (int j = 0; j < N; ++j)
        {
            ll temp = 0;
            for (int k = 0; k < N; ++k)
            {
                temp = (temp + M[i][k] * L[k][j]) % 1000;
            }
            vt.push_back(temp);
        }
        ret.push_back(vt);
    }
    return ret;
}

vector<vector<ll>> solve(vector<vector<ll>> A, ll BB)
{
    if (BB == 1)
        return A;

    vector<vector<ll>> t = solve(A, BB / 2);
    vector<vector<ll>> t2 = mul(t, t);

    if (BB % 2 == 1)
        return mul(t2, A);

    return t2;
}

int main()
{
    scanf("%d %lld", &N, &B);

    vector<vector<ll>> M;

    for (int i = 0; i < N; ++i)
    {
        vector<ll> temp;
        for (int j = 0, t; j < N; ++j)
        {
            cin >> t;
            temp.push_back(t % 1000);
        }
        M.push_back(temp);
    }

    vector<vector<ll>> ret = solve(M, B);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printf("%lld ", ret[i][j]);
        printf("\n");
    }
    return 0;
}
```

예제: Z (https://www.acmicpc.net/problem/1074)
- 포인트 1: 큰 문제를 어떻게 작은 문제로 분할할 것인가를 생각하는 것!
- 포인트 2: 중복되는 패턴이 존재한다.
- 포인트 3: 큰 정사각형에서 4개의 작은 정사각형으로 나눌 수 있고 하나의 작은 정사각형에서 선이 다 그어지면 다음 작은 정사각형으로 선이 넘어간다. (이를 이용!)

``` c
#include <math.h>
#include <stdio.h>

int Z(int n, int r, int c)
{
    if (n == 0)
        return 1;

    int ret = 0, powpow = pow(2, n - 1);
    if (r < powpow && c < powpow)
    {
        return Z(n - 1, r, c);
    }
    else
    {
        ret += powpow * powpow;
    }

    if (r < powpow && c >= powpow)
    {
        return ret + Z(n - 1, r, c - powpow);
    }
    else
    {
        ret += powpow * powpow;
    }
    if (r >= powpow && c < powpow)
    {
        return ret + Z(n - 1, r - powpow, c);
    }
    else
    {
        ret += powpow * powpow;
    }

    if (r >= powpow && c >= powpow)
    {
        return ret + Z(n - 1, r - powpow, c - powpow);
    }
    return 0;
}

int main()
{
    int N, r, c;
    scanf("%d %d %d", &N, &r, &c);
    printf("%d\n", Z(N, r, c) - 1);
    return 0;
}
```

예제: Counting Inversions (https://www.acmicpc.net/problem/10090)
- 포인트 1: 자신보다 왼쪽에 있는 작은 값의 개수를 모두 합하는 문제이다.
- 포인트 2: 분할 정복을 활용하여, 배열을 절반(A, B)으로 나눈 후, merge sort를 수행한다.
- 포인트 3: merge 시에 A의 맨 앞 요소를 새로운 배열에 넣으려 할 때, B가 merge 해 놓은 갯수만큼 A의 맨 앞 요소가 크다. (이를 카운트)

``` cpp
#include <iostream>

using namespace std;

typedef long long ll;

int L[1000001];
int R[1000001];
int arr[1000001];

ll merge(int lo, int hi, int m)
{
    int n1 = m - lo + 1;
    int n2 = hi - m;

    for (int i = 0; i < n1; ++i)
        L[i] = arr[lo + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[m + 1 + i];

    int i, j, w, k = lo;
    ll ret;
    i = j = w = ret = 0;

    while (i < n1 && j < n2)
    {
        if (L[i] > R[j])
        {
            arr[k++] = R[j++];
        }
        else
        {
            arr[k++] = L[i++];
            ret += j;
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
        ret += j;
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
    }

    return ret;
}

ll mergeSort(int lo, int hi)
{
    ll ret = 0;
    if (lo >= hi)
        return 0;

    int mid = (lo + hi) >> 1;
    ret += mergeSort(lo, mid);
    ret += mergeSort(mid + 1, hi);
    ret += merge(lo, hi, mid);

    return ret;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    printf("%lld\n", mergeSort(0, n - 1));

    return 0;
}
```

예제: 히스토그램에서 가장 큰 직사각형 (https://www.acmicpc.net/problem/6549)
- 포인트 1: 특정 [lo, hi] 구간 사이의 가장 큰 직사각형의 넓이를 구하는 "구간" 문제이다.
- 포인트 2: 구간 문제의 경우 하나의 인덱스에서의 부분 문제로 나누어 해결하거나, 절반으로 분할하여 해결하거나, 구간 트리(SegTree)를 사용하거나 등등의 방법이 있다.
- 포인트 3: 분할 정복을 활용하여 해결하려 할 때, 절반으로 구간을 나누고 각각의 구간에서 후보로 될 수 있는 최대 직사각형의 넓이를 구한다. (A, B)
- 포인트 4: 구간을 나눴지만 mid 와 mid + 1을 포함한 직사각형의 넓이를 구하지는 않았으니 이를 포함하고 구간을 넓혀가면서 값을 비교해야 한다.
- 포인트 5: left 와 right 를 넓혀가는 과정에서 높이가 높은 쪽으로 넓혀가는 것이 이득이다. (그리디)
  - 증명
  - 3가지 상황을 살펴보면 된다. (left, right의 높이 vs 현재 최대 높이)
    - 1. 둘 다 높이가 높을 때: 아무 방향이나 넓혀도 된다.
    - 2. 둘 다 높이가 낮을 때: 최대한 높이가 덜 낮은 방향으로 넓힌다.
    - 3. 하나는 높이가 높고 하나는 높이가 낮을 때: 이 때도 높이가 높은쪽으로 넓히는 것이 좋다.
  - 즉, 높이가 높은 쪽으로 넓혀 가는 것이 이득이다. 
  - 높이는 높아질 수 없다. 항상 같거나 작아지게 된다.

``` cpp
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

ll height[100001];

ll histo(int lo, int hi)
{
    if (lo > hi)
        return 0;
    if (lo == hi)
        return height[lo];

    int mid = (lo + hi) >> 1;
    int left = mid, right = mid + 1;
    ll h = min(height[left], height[right]);
    ll area = h * 2;
    while (lo < left || right < hi)
    {
        if (right < hi && (left == lo || height[left - 1] < height[right + 1]))
        {
            h = min(h, height[++right]);
        }
        else
        {
            h = min(h, height[--left]);
        }
        area = max(area, h * (right - left + 1));
    }

    return max({ area, histo(lo, mid), histo(mid + 1, hi) });
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (true)
    {
        int n;
        cin >> n;

        if (n == 0)
            break;

        memset(height, 0, sizeof(height));
        for (int i = 0; i < n; ++i)
        {
            cin >> height[i];
        }

        cout << histo(0, n - 1) << '\n';
    }
    return 0;
}
```
- 무서운 아르바이트 (https://www.acmicpc.net/problem/12846) 도 동일한 문제

예제: **가장 가까운 두 점 (https://www.acmicpc.net/problem/2261)**
- 정말 어려웠던 문제.
- 포인트 1: 모든 쌍을 다 고려하면 O(n^2) 이 걸린다. (시간초과)
- 포인트 2: 분할 정복을 활용해서, 절반을 분할하고 각각의 구간에서의 최솟값을 구한다.
- 포인트 3: 분할하여 왼쪽, 오른쪽 구간의 최솟값을 구했지만 중앙을 통과하여 연결되는 두 점의 거리는 구하지 못했다. 
- 포인트 4: 이를 그냥 하게되면 n/2 * n/2 이 걸린다.
  - 시간 복잡도: T(n) = 2*(n/2) + O(n^2)
  - 마스터 정리를 사용하면 T(n) = O(n^2) (2 < 2^2)
- 포인트 5: 검사하는 점들의 수를 어떻게든 줄여야 한는데 이 때 전에 구해놓은 왼쪽, 오른쪽의 최솟값을 사용한다.
- 포인트 6: 즉 해당 최소값보다 mid 와 특정 점의 x 좌표 사이의 거리가 크다면 그 점은 검사할 필요조차 없는 것이다. 왜냐면 지금 나는 mid를 통과하는 점 사이의 거리를 구하려고 하기 때문!
- 포인트 7: 이렇게 최소값보다 mid와 x좌표의 거리가 작은 점들을 구해놓았는데 이번에는 y좌표를 활용해서 y좌표가 최소값보다 큰 값을 걸러내는 방식으로 한 번 더 줄일 수 있다.
- 가장 가까운 두 점의 이론 상 이렇게 걸러낸 점들은 7번을 넘지 않는다고 한다.
- 이론: http://people.csail.mit.edu/indyk/6.838-old/handouts/lec17.pdf
- 시간 복잡도: T(n) = 2*T(n/2) + O(nlog(n)) (y좌표 정렬 시간)
- 마스터 정리를 사용하면 T(n) = O(n(log(n))(log(n)))

``` cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct point
{
    int x, y;
};
bool cmp(point a, point b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
bool cmp2(point a, point b)
{
    return a.y < b.y;
}

vector<point> p;
const int inf = 2000000000;

int dist(int x1, int x2, int y1, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int closeSet(int left, int right)
{
    if (left + 2 >= right)
    {
        int minL = inf;
        for (int i = left; i < right; ++i)
            for (int j = i + 1; j <= right; ++j)
                minL = min(minL, dist(p[i].x, p[j].x, p[i].y, p[j].y));
        return minL;
    }

    int mid = (left + right) >> 1;
    int minL = min(closeSet(left, mid), closeSet(mid + 1, right));

    vector<point> vt;

    for (int i = left; i < right + 1; ++i)
        if (minL > (p[mid].x - p[i].x) * (p[mid].x - p[i].x))
            vt.push_back(p[i]);

    sort(vt.begin(), vt.end(), cmp2);
    int s = vt.size();
    for (int i = 0; i < s; ++i)
        for (int j = i + 1; j < s; ++j)
        {
            if (minL > (vt[i].y - vt[j].y) * (vt[i].y - vt[j].y))
                minL = min(minL, dist(vt[i].x, vt[j].x, vt[i].y, vt[j].y));
            else
                break;
        }

    return minL;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0, r, c; i < n; ++i)
    {
        cin >> r >> c;
        p.push_back({ r, c });
    }

    sort(p.begin(), p.end(), cmp);

    cout << closeSet(0, n - 1) << '\n';

    return 0;
}
```

## 힙(Heap)
- 완전 이진 트리 (2개의 자식 + 왼쪽부터 채움)
  -  높이가 h일 때2^(h-1)-1 <= n <= 2^h-1 이다.
  - (부모 노드의 키값 >= 자식 노드의 키값) : maxHeap
  - (부모 노드의 키값 <= 자식 노드의 키값) : minHeap
  - 루트 노드느느 원하는 값을 보장받는다. (최대값 or 최소값)

용도
- 정렬: heap 에서 값을 하나씩 뽑으면 정렬된 순서대로 나온다.
- 정렬 + 값을 계속해서 삽입, 삭제할 때!!!
- 탐색 용도 X, 정렬 O

힙 트리에서는 탐색 연산을 고려하지 않는다.
원소가 어디에 있는지 모르기 때문에, 즉 전체를 뒤져야 하기 때문이다!

자료구조:
- 삽입
- 삭제
- 탐색

즉 힙 트리에서는 삽입, 삭제만 생각하고 탐색 연산은 고려하지 않는다.

이진 트리 (배열 or 포인터)
- 배열: 완전 이진 ㅌ리하고 거리가 멀 경우 낭비도뇌는 메모리 공간이 많다.
- 하지만 힙은 그 자체가 완전 이진 트리라는 성질을 가지고 있기 때문에 배열로 표현하기에 적합하다.

루트 노드는 1번 노드이다.
- 이렇게 해야 루트노드의 자식이 2번, 3번으로 쉽게 찾을 수 있기 때문
- child = 2 * n or 2 * n + 1

힙에 원소 삽입
1. 원소를 완전 이진 트리가 유지되게 삽입
2. 현재 노드 값과 부모 노드 값을 비교하여 필요할 시에 자리바꿈 하기를 루트까지 가면서 반복 (자리 바꿈이 필요 없어지면 멈춤)

힙에 원소 삭제
1. 루트 노드를 삭제 (heap은 무조건 루트노드를 삭제하는 자료구조)
2. 노드 번호 순으로 마지막 노드를 루트 자리로 옮김
3. 현재 노드 값과 자식 중 더 큰 노드 값을 비교하여 필요할 시에 자리바꿈 하기를 단말 노드까지 가면서 반복 
- 자리바꿈이 필요 없어지면 멈춤
- 위에서 아래로 진행

Heap 트리의 알고리즘 효율
- 하나의 노드 삽입: O(logn)
- 하나의 노드 삽입: O(logn)
- 정렬에 사용: O(n log n)

``` c
#include <stdio.h>
#include <stdlib.h>

void insertHeap(heap *h, int item)
{
    if (h->size >= MAX - 1)
    {
        printf("Full!!\n");
        return;
    }
    // 제일 끝 노드에 추가
    // 부모 노드와 비교하면서 자신의 위치를 찾는 것 (자신의 부모보다 작고, 자식보다 크다! : max heap)
    int index = ++h->size;
    // 멈추는 조건
    // 1. 루트 노드 일 때 (루트: 1)
    // 2. 부모 노드의 값이 클 때 (부모: index/2)
    while ((index != 1) && (h->data[index / 2] < item))
    {
        h->data[index] = h->data[index / 2];
        index /= 2;
    }
    h->data[index] = item;
}

int deleteHeap(heap *h)
{
    if (h->size == 0)
    {
        printf("Empty!!\n");
        return -1;
    }
    int result = h->data[1], tmp;
    tmp = h->data[h->size--];

    int cur, child;

    cur = 1;
    while ((child = cur * 2) <= h->size)
    {
        if (child + 1 <= h->size &&
            (h->data[child] < h->data[child + 1]))
            ++child;
        if (h->data[child] <= tmp)
            break;
        h->data[cur] = h->data[child];
        cur = child;
    }
    h->data[cur] = tmp;
    return result;
}

void printHeap(heap *h)
{
    printf("My heap: ");
    for (int i = 1; i < h->size + 1; ++i)
    {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}
```

예제: 카드 정렬하기 (https://www.acmicpc.net/problem/1715)
- 포인트 1: a < b < c < d 인 배열의 경우 작은 순서대로 합치는 것이 좋다.
- 포인트 2: a + b 를 새로 계산하면 새로운 요소를 추가해야 한다.
- 포인트 3: 새롭게 추가된 요소를 포함해서 가장 작은 값을 뽑아야 한다.

``` cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct cmp
{
    bool operator()(int a, int b)
    {
        return a > b; // 작은 값이 우선순위가 높음
    }
};

int main()
{
    // 기본이 min heap 인가연?
    priority_queue<int, vector<int>, cmp> pq;

    int n;
    cin >> n;

    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        pq.push(t);
    }

    int ret = 0;
    while (!pq.empty())
    {
        int left = pq.top();
        pq.pop();

        if (pq.empty())
            break;

        int right = pq.top();
        pq.pop();

        int sum = left + right;
        ret += sum;
        pq.push(sum);
    }

    cout << ret << '\n';

    return 0;
}
```