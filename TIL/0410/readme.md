# 4월 10일 TIL (Today I Learned)


## 에라토스테네스의 체
- 소수를 구하는 알고리즘
- 소수의 배수는 소수가 아니기 때문에 이를 거르는 방법이다.

기본적인 알고리즘
``` c
void prime(int n)
{
    bool is_prime[n + 1];

    for (int i = 2;i < n + 1; ++i)
    {
        is_prime[i] = true;
    }

    for (int i = 2;i < n + 1;++i)
        if (is_prime[i]) 
        {
            {
                for (int j = i * i; j < n + 1; j += i)
                    is_prime[j] = false;
            }
        }
}
```

**키 포인트**
1. j = i * i
- i 보다 작은 수 k의 배수는 이미 처리되었다. 
- i * k 는 이미 처리되어있다.

1. j += i
- j 의 시작은 i 이며, i 를 계속 더하면 j 는 항상 i 의 배수이다!

최적화된 알고리즘
```c
void prime(int n)
{
    bool is_prime[n + 1];

    for (int i = 2; i < n + 1; i++) 
    {
        is_prime[i] = true;
    }

    int sqn = sqrt(n);
    for (int i = 2; i < sqn + 1; i++) 
    {
        if (is_prime[i]) 
        {
            for (int j = i * i; j < n + 1; j += i)  
                is_prime[j] = false;
        }
    }
}
```

왜 sqrt() (제곱근)을 사용하는 것일까??
- 거꾸로 생각해봤을 때 j = n 으로 가장 클 때, i 는 sqrt(n) 보다 작거나 "같은 수" 이다.
- 따라서 i <= sqrt(n) 이 가능해지는 것이다!!

예제: 골드바흐의 추측 (https://www.acmicpc.net/problem/9020)

- 소수 구하기 (에라토스테네스의 체)
- 가장 가까이 있는 두 숫자 구하기 
- n/2 부터 시작하여 내려가면서 숫자와 반대편 숫자(n - i) 가 모두 소수면 출력 후 break

``` c
#include <math.h>
#include <stdio.h>

int main()
{
    int mr = 10000;
    int prime[10001] = { 0 };

    // 에라토스테네스의 체 (소수는 2부터 시작)
    for (int i = 2; i < mr + 1; ++i)
        prime[i] = 1;

    int sqrtmr = sqrt(mr);
    for (int i = 2; i < sqrtmr + 1; ++i)
    {
        if (prime[i])
            for (int j = i * i; j < mr + 1; j += i)
                prime[j] = 0;
    }

    int tc;
    scanf("%d", &tc);

    while (tc--)
    {
        int n;
        scanf("%d", &n);

        for (int i = n / 2; i >= 2; --i)
        {
            int l = prime[i];
            int r = prime[n - i];

            if (l && r)
            {
                printf("%d %d\n", i, n - i);
                break;
            }
        }
    }

    return 0;
}
```

## 하노이 탑
- 원판 옮기기
- 조건: 본인보다 너비가 작은 원판 위에 못 둔다.

재귀함수 사용

``` python
# hanoi(n, s, e, o)
# n개의 원판이 s 기둥에 있을 때 이를 e 기둥에 모두 옮길 때의 최소 방법 수, o는 보조 기둥
def hanoi(n, s, e, o):
    if n == 1:
        return 1
    
    # (n - 1)개의 원판을 s 기둥에서 o 기둥으로 모두 옮긴다.
    # 그러면 마지막 n번째 원판을 e 기둥에 옮길 수 있다.
    x = hanoi(n - 1, s, o, e)

    # (n - 1)개의 원판을 o 기둥에서 e기둥으로 모두 옮긴다.
    # n 너비의 원판이 이미 e에 깔려 있어서 옮길 수 있다.
    y = hanoi(n - 1, o, e, s)
    return x + y + 1
```

hanoi(n, s, e, o) 의 호출은 항상 최솟값을 보장하고 항상 같은 값을 반환한다.
그래서 하노이 탑에 대한 공식이 존재한다.
- (2**N - 1)

예제: 하노이 탑 (https://www.acmicpc.net/problem/1914)

최솟값 구하기 + 출력
``` python
def hanoiprint(n, s, e, o):
    if n == 1:
        print(s + 1, e + 1)
        return

    hanoi2(n - 1, s, o, e)
    hanoiprint(s + 1, e + 1)
    hanoiprint(n - 1, o, e, s)
    return

print(2**N - 1)
if N <= 20:
    hanoiprint(N, 0, 2, 1)
```

## C++ sort cmp 

**std::sort(arr, arr + n, cmp)**
- #include <algorithm\>
- array 를 정렬해주는 함수이다.
- 정렬 조건을 cmp 구조체를 통해서 줄 수 있다.

정렬 조건 (cmp)
```c
struct cmp 
{
    bool operator() (const string& a, const string& b)
    {
        // 원하는 데로 정렬 조건을 지정할 수 있다.
        // a는 왼쪽 인자값, b는 오른쪽에서 전달받는 인자값이다!
        // true 조건을 만족하게 정렬한다.
        // 가장 기본: 오름차순
        return a < b;
    }
}

// 참고: 구조체나 클래스에서 compare operator 지정
// 현재 값과 다른 값(오른쪽) 비교 
bool operator<(const MyType& o) const {
    ...
}
```

## C 문자열 함수

1. strlen(const char *__s): 문자열의 길이 반환
``` c
char str[] = "hi";
int len = strlen(str);
```

2. strcpy(char *__dst, const char *__src): 문자열을 복사
``` c
char src[] = "hi";
char dst[10]
strcpy(dst, src);
```

3. strcat(char *__s1, const char *__s2): 문자열을 이어 붙인다.
```c
char s1[10] = "hi";
char s2[] = "bk!";
// s1 = s1 + s2 (이어붙이는 관점)
strcat(s1, s2);
```

4. strcmp(const char *__s1, const char *__s2): 두 문자열을 비교한다.
- 리턴값 0: 둘이 같다.
- 리턴값 1: s1이 s2보다 뒤에 온다. (크다.)
- 리턴값 -1: s1이 s2보다 앞에 온다. (작.)
``` c
char s1 = "abc";
char s2 = "def";
int result = strcmp(s1, s2);
```

## 문자열 to 정수 in C/C++

1. atoi(const char *)
- 문자열을 정수로 변환

``` c
char s1[] = "12345";
int num = atoi(s1);
```

2. strtol()
- long 형식으로 문자열을 정수로 변환
- 변환할 진법도 지정할 수 있다. (마지막 인자)
```c
char s1[] = "12345";
char *endptr;
    long num = strtol(str, &endptr, 2);  
```

3. stringstream 클래스 (in C++)
``` cpp
string str = "12345";
stringstream ss(str);
ss >> num;
```

## 정수 to 문자열 in C
1. sprintf()
``` c
int num = 12345;
char str[20];
sprintf(str, "%d", num);
// num to str

// 변환할 값의 형식도 지정할 수 있다.
// 예를 들어, 소수점 이하 자릿수를 지정하거나 16진수로 출력할 수도 있다.
double num = 3.141592;
char str[20];

// 소수점 이하 둘째자리까지 출력
sprintf(str, "%.2f", num);  

// to hex
sprintf(str, "%x", num);

// to oct
sprintf(str, "%o", num);
```
2. std::tostring(num)
- 정수나 부동 소수점 값을 문자열로 변환할 수 있습니다.
``` cpp
int num = 12345;
std::string str = std::to_string(num);

double num = 3.141592;
std::string str = std::to_string(num);
```





















