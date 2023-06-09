# Weekly I Learned (0418 ~ 0424)

## 알고리즘 주차
- 개념 정리 및 문제 풀이 정리

## 자료구조 == 컨테이너 !!!
어떤 문제를 풀다가, 기존에 방문했던 점 혹은 남은 점들을 추적/관리할 필요가 있을 때 컨테이너에 담아서 관리할 수 있다.
그래서 이 컨테이너에서 삽입, 삭제, 탐색, 정렬 중에 하려는 연산/동작들을 가지고 어떤 자료구조/컨테이너가 필요한지 선택하면 된다.

예: [막대기](https://www.acmicpc.net/problem/17608), [탑](https://www.acmicpc.net/problem/2493), [히스토그램](https://www.acmicpc.net/problem/1725) 같은 문제
- 다른 인덱스의 요소는 그 요소 방문 이후에 추적/관리될 수 있다.
- 특정 인덱스의 요소는 어느 순간 아예 필요가 없게될 수도 있다.
- ==> 삽입, 삭제
- 정렬 과정이 필요한가? 아니다.
- 이 문제들의 경우 특정 순서대로 넣으면 알아서 정렬된 순서를 유지하기 때문에 정렬이 필요하지 않다.
- 오름차순이나, 내림차순으로 정렬했을 때 그 끝의 값만 확인하면 된다.
- 즉 끝에 값을 넣거나 빼거나 한다.  
- **스택**

예: [뱀](https://www.acmicpc.net/problem/3190)
- 뱀의 머리와 몸체를 추적/관리해야 한다.
- 몸체는 없어지지 않는다.
- 항상 뱀의 머리 --> 몸체 순으로 검사한다.
- ++ '꼬리'라는 새로운 요소가 추가될 수 있는데 이는 마지막에 넣어야 한다.
- 처음 요소(머리)부터 검사하고 꼬리라는 요소를 마지막에 추가해야 한다.
- **큐**

예: [철로](https://www.acmicpc.net/problem/13334)
- 점들을 뒤의 점을 기준으로 오름차순 정렬하고 순회하면서 거리(L) 안에 들어간다면 이 점들을 추적/관리한다.
- 추적하던 점들 중에서 x거리가 L거리보다 멀면 관리하지 않는다.
- x 거리가 가장 먼 좌표부터 검사하는 것이 좋다. 그래야 x 거리가 L보다 가까울 때 남은 관리하는 점들을 볼 필요가 없어지기 때문이다.
- 즉 '점'들을 정렬한 상태로 유지하면서 점의 삽입/삭제가 이루어져야 한다.
- **우선순위 큐**

## 라인 스위핑
라인 스위핑 문제는 정렬된 어떤 자료에서 시간 복잡도를 줄일 수 있도록 선을 한 번만 훑으면서 최종 결과를 찾는 방식으로 되어 있습니다.  
훑는다는 개념이 "도형, 직선, 점, ..." 들을 일정 기준에 맞추어 정렬해놓고 순서대로 훑는 것과 동치가 되는 경우가 다수라고 한다.

지금까지 내가 푼 문제들은 이미 방문한 점을 추적/관리하면서 다시 보는 경우가 많았다.

예: [철로](https://www.acmicpc.net/problem/13334), [선 긋기](https://www.acmicpc.net/problem/2170), [가장 가까운 두 점](https://www.acmicpc.net/problem/2261), [수상 택시](https://www.acmicpc.net/problem/2836), [화성 지도](https://www.acmicpc.net/problem/3392), [북서풍](https://www.acmicpc.net/problem/5419), [보석 도둑](https://www.acmicpc.net/problem/1202), [과제](https://www.acmicpc.net/problem/13904), [소수의 곱](https://www.acmicpc.net/problem/2014)

왼쪽부터 방문하면서 이미 방문한 점들을 추적/관리한다.
왜일까?
- 이미 방문한 점, 선, 도형들은 내가 직접 어떤 처리를 할 수 있기 때문이다. 
- 내가 아직 보지 못한 도형들은 어떠한 처리를 하지 못한다. 만약 어떤 처리를 하려면 "모두" 확인해야 하기 때문에 O(N^2)시간복잡도가 걸리는 경우가 많았다.
- 아직까지는 그렇지만 언제 또 이후의 점, 도형들을 먼저 봐야할지 모른다. 아직 문제를 많이 안 풀어봤기 때문에 좀 더 경험치를 쌓아야 할 듯 싶다.
- 왼쪽부터 방문한다는 것은 그냥 하나의 기준일 뿐이고 정말 중요한 것은 특정한 정렬 기준에 따라서 먼저 방문한 점들을 추적/관리하는 것이다.

2차원 평면? 에서 행하는 스위핑 알고리즘은 세그먼트 트리나 우선순위 큐와 잘 맞는 것 같다.  
항상 도형을 만날 때마다 지금까지 방문한 것들 중 혹은 특정 구간에서 ~~의 개수, 합, 최소값, 최대값, ... 등 같은 것을 매번 체크해야 하기 때문이다.

## 기억에 남았거나, 좀 어려웠던 문제 정리

[후위 표기식](https://www.acmicpc.net/problem/1918)
- 중위 표기식을 후위 표기식으로 고치는 알고리즘
- (A + (B * C)) - (D/E) --> ABC*+DE/-
- +, - 와 *, / 의 우선순위가 다르다.
- *, / 연산을 먼저 해야 한다.
- 그러면 그 전에 나온 +, - 연산들을 어딘가에서는 추적/관리해야 한다.
- *, / 연산 역시 어딘가에서 추적/관리해야 한다.
- 괄호를 제외하고 * 가 + 보다 항상 먼저 나와야 한다.
- 닫는 괄호를 만나면 그 전의 여는 괄호부터의 연산자를 모두 뽑아서 사용해야 한다.
- **스택** 사용
- 즉 '(' 를 만나면 그냥 push하고 *, / 가 쌓였을 때 다음 연산이 +, - 이면 먼저 사용되어야 하기 때문에 기존에 추적/관리하고 있는 *, / 를 계속해서 뽑는다.
- 다 뽑았으면 +, - 를 스택에 푸쉬한다.
- ')'를 만나면 '(' 를 만날 때까지 모두 pop해서 결과에 넣는다.
- 포인트 1: 정확한 식이라면 ')' 를 만났을 때 스택에서 계속 팝하다보면 그에 대응하는 '('를 만나게 되어 있다.

[스카이 라인](https://www.acmicpc.net/problem/1933)
- 건물의 윤곽을 나타내려면 결국에 현재 가장 큰 높이를 추적/관리해줘야 한다.
- x 좌표를 왼쪽에서 오른쪽으로 이동할 때마다 높이를 추가/삭제 해야 한다.
- 건물 특성 상 추적/관리되어야 하는 높이가 있고, 삭제해야 하는 높이가 있다. (push/pop)
- 높이를 추가하는 상황에서 현재 높이보다 높이가 낮다고 관리하지 않으면 안된다.
- 즉 현재 가장 높은 높이를 알아야 하고, 현재 높이를 pop하였을 때 다음으로 가장 높은 높이를 알아야 하는 구조다.
- 바로 **우선순위 큐** 자료구조를 사용하는 문제이다!!!
- 가장 어려웠던 점이 바로 경계에서의 정렬 기준이다.
- 우선순위 큐는 정렬 기준이 가장 중요하다. 
- 우선 첫 번째로는 높이가 가장 높은 높이를 선택해야 하기 때문에 높이를 정렬 기준으로 선택하였다.
- 두번째로 높이가 같을 때 x 좌표가 낮은 순위로 정렬 하였다.
- 왜냐하면 x 좌표를 왼쪽에서 오른쪽으로 보기 때문에 먼저 pop 할 수 있게 하였다.

- 건물을 push/pop 할 기준을 정하는 것도 굉장히 어려웠다.
- 당연히 우선적으로는 x 좌표가 작은 순서대로 정렬하는 것이다.
- 처음에는 x좌표가 같으면 높이가 높은 쪽으로 정렬하게 해서 먼저 우선순위 큐에 놓을 수 있게 함으로써 다음에 들어오는 높이에서는 결과값에 들어가지 않을 수 있게 하였다.
- 그러나 단순히 이렇게 해서는 특정 x좌표에서 pop하고 바로 push하는 경우에 결과값에 두 번 출력되는 대참사를 막을 수가 없었다.
- x좌표가 같은 상황에서 pop을 하고 push하는 경우에 높이가 같다면 2번 출력해서는 안된다.
- 여기서 많이 해맸지만 결국에는 찾아냈다.
- 바로 x좌표가 같을 때에는 방향이 pop하는 쪽보다 push하는 쪽을 먼저 확인하게 하는 것이다.
- 그렇게 되면 pop을 할 때는 이미 push 되었기 때문에 결과값에 두 번 출력될 일이 없어졌다.


``` cpp
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int END = 1000000001;

struct point
{
    int x, h, o, d;
    bool operator<(const point &p) const
    {
        if (x == p.x)
        {
            if (d == p.d)
                return h > p.h;
            return d > p.d;
        }
        return x < p.x;
    }
};

struct pqpoint
{
    int rx, h;
};

struct cmp
{
    bool operator()(const pqpoint &u, const pqpoint &v)
    {
        if (u.h == v.h)
            return u.rx > v.rx;
        return u.h < v.h;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<point> p(2 * n);

    for (int i = 0; i < n; ++i)
    {
        int l, h, r;
        cin >> l >> h >> r;

        p[2 * i] = { l, h, r, 1 };
        p[2 * i + 1] = { r, h, l, -1 };
    }

    sort(p.begin(), p.end());

    priority_queue<pqpoint, vector<pqpoint>, cmp> pq;
    vector<pair<int, int>> ret;
    pq.push({ END, 0 });

    for (int i = 0; i < 2 * n; ++i)
    {
        point now = p[i];
        if (now.d > 0)
        {
            if (pq.top().h < now.h)
                ret.push_back({ now.x, now.h });
            pq.push({ now.o, now.h });
        }
        else // pop
        {
            if (pq.top().h > now.h)
                continue;
            else
            {
                int rx = pq.top().rx;
                if (END == rx)
                    break;
                while (!pq.empty() && pq.top().rx <= rx)
                {
                    pq.pop();
                }
                if (now.h != pq.top().h)
                    ret.push_back({ rx, pq.top().h });
            }
        }
    }

    for (int i = 0; i < ret.size(); ++i)
        cout << ret[i].first << ' ' << ret[i].second << ' ';
    return 0;
}
```


## 메모리 일관성 문제 해결
- 가시성 및 재배치 문제를 해결

가시성 문제?
- 각각의 cpu 코어는 캐시를 가지고 있기 때문에 쓰기 작업을 할 때 캐시에 우선적으로 쓴다. 특정 스레드가 공유 변수에 쓰기작업을 했는데 캐시에는 썼지만 메인 메모리에는 반영되지 않은 상태에서 다른 스레드가 해당 공유 변수를 읽으려 하면 변경된 값을 읽지 못하는 문제가 발생한다.
- visibility

재배치 문제
- 컴파일러 및 CPU 는 최적화를 위해서 명령어의 재배치를 한다.
- 예를 들어, 의존성이 없는 명령어의 경우 파이프라인의 스톨을 막기 위해서 재배치한다.
- out of order

volatile
- 가시성 문제를 해결할 수 있다.
- 컴파일 시의 메모리 재배치 문제를 해결할 수 있다.
- 그러나 런타임 시에 CPU 최적화에 의한 메모리 재배치를 막을 수 없다.

그렇기 때문에 다른 도구들이 필요한데, 그것이 바로 memory fence, memory order 이다.

java에서는 atomic, UnSafe, VarHandle, ...을 사용하여 변수에 대해서 메모리 일관성 문제를 해결할 수 있다.

ex) ForkJoinPool code

``` java
final int queueSize() {
    int n = (int)BASE.getAcquire(this) - top;
    return (n >= 0) ? 0 : -n; // ignore transient negative
}

final boolean isEmpty() {
    ForkJoinTask<?>[] a; int n, cap, b;
    VarHandle.acquireFence(); // needed by external callers
    return ((n = (b = base) - top) >= 0 || // possibly one task
            (n == -1 && ((a = array) == null ||
                         (cap = a.length) == 0 ||
                         a[(cap - 1) & b] == null)));
}

```

### getAcquire, acquireFence

getAcquire
- acquire 기능은 현재 스레드가 어떤 메모리 위치에 대한 엑세스를 수행할 때, 그 엑세스 이전에 다른 스레드에 의해 수행된 엑세스의 메인 메모리에 대한 쓰기 변경 사항을 현재 스레드에서 보이도록 하는 것을 보장한다.
- setRelease 메서드 이후의 읽기 작업이 메서드 호출 이전으로 넘어갈 수 없다.
- 반 메모리 재배치 금지
- 따라서 getAcquire() 메서드는 이전 메모리 엑세스의 변경 사항이 현재 스레드에서 보이도록 보장하면서, BASE 변수의 값을 가져올 수 있다.

따라서 queueSize() 메서드에서 BASE.getAcquire(this) 메서드는 현재 스레드에서 this 참조로 참조되는 인스턴스의 BASE 변수 값을 가져올 때, 메인 메모리에 반영된 최신값을 가져올 수 있다.

acquireFence
- 메서드 호출 "이전에" 이루어진 변수(메인 메모리) 엑세스에 대한 일관성을 보장한다.
- 공유 상태(변수)에 대한 일관성을 제어
- 다른 스레드에서 변수를 읽기 전에 현재 스레드에서 메인 메모리에 변수를 쓴 후에 메모리 일관성을 유지할 수 있게 한다.
- 반대로 말하면 현재 스레드에서 변수를 읽기 전에 다른 스레드에서 작업중이던 메인 메모리에 변수를 쓴 후에 읽을 수 있도록 한다는 말이다.

이전에 실행된 변수 엑세스(메인 메모리에 대한 쓰기 작업)와 이후에 실행될 변수 엑세스 사이(읽기)의 일관성을 유지한다.

getAcquire, acquireFence 모두 어떻게 일관성을 보장할 수 있을까?
이전의 메인 메모리에 대한 변경사항을 특정 스레드의 캐시, 혹은 모든 스레드의 캐시가 메인 메모리와 동기화되고, 메인 메모리에서 가장 최신의 변수 값이 읽힐 때까지 모든 스레드에서 일시 중지된다.

정리
- acquireFence 는 현재 스레드의 메모리 가시성을 보장하기 위해, 이전에 다른 스레드가 메인 메모리에 작성한 값을 모든 스레드의 캐시로 로드하는 것을 보장한다. 따라서 다른 스레드가 작성한 최신 값을 메인 메모리에서 가져와서 현재 스레드에서 볼 수 있게 한다.
- getAcquire 는 다른 스레드가 메인 메모리에 작성한 값을 현재 스레드의 캐시로 로드하여 읽는 것을 보장
- 메모리 가시성 보장!!
- 메인 메모리로부터의 데이터를 캐시에 동기화하는 것이기 때문에 캐시에 있는 값이 메인 메모리에 즉시 반영되는 것은 아니다. (즉, 완전한 메모리 가시성을 보장하지는 않는다.)

### setRelease, releaseFence

setRelease
- 지정된 변수에 값을 저장 + 이전의 캐시된 값을 메인 메모리로 플러시하여 모든 스레드에서 새로운 값을 읽을 수 있도록 할 수 있다.
- 이전 쓰기작업이 setRelease 메서드 이후로 넘어갈 수 없다.
- 반 메모리 재배치 금지
- 즉 값을 저장하는 것과 동시에 해당 변수가 다른 스레드에게 가시적인 것을 보장한다.

releaseFence
- 다른 스레드에서 현재 스레드가 작업하는 변수에 엑세스하기 전에, 이전에 발생한 모든 변수 업데이트(in cache)가 메인 메모에 반영될 수 있도록 보장한다.

setRelease()는 값을 저장하면서 동시에 메모리 가시성을 보장하며, releaseFence()는 캐시된 값을 메인 메모리로 플러시하여 메모리 가시성을 보장합니다.

**중요**  
acquire 는 이후 읽기를 보장해야 한다
release는 즉 이전 쓰기 작업을 보장  
즉, release 는 이후로 갈 수 없고, acquire는 이전으로 갈 수 없는 것을 보장
순서가 이상하게 바뀌면 이후 읽기/ 이전 쓰기를 보장하지 못하기 때문이다!!!
- 가시성 및 재배치 문제 해결

acquireFence()는 읽기 작업에서 사용되며, releaseFence()는 쓰기 작업에서 메모리 가시성 및 일관성을 보장하기 위해 사용

### fullFence
- setRelase + getAcquire, releaseFence + acquireFence
- 메모리 가시성과 일관성을 보장하는 메서드
- 이 메서드는 메인 메모리와의 모든 캐시를 동기화하여, 모든 쓰기 작업이 메모리, 다른 코어 캐시에 반영되었음을 보장한다.
- 즉 fullFence 이후에는 모든 스레드에서 모든 변수에 대한 변경사항이 적용된 후의 최신 값을 가져올 수 있다.
 - releaseFence: 모든 코어의 캐시를 메인 메모리에 플러시
 - acquireFence: 메인 메모리로부터 데이터를 캐시에 동기화 시킨다.

fullFence는 보통 다음과 같은 상황에서 사용된다.
- 데이터 구조의 불변성을 유지하기 위해 동기화가 필요한 경우
- 스레드 간의 통신이 필요한 경우

그러나 이 메서드는 메모리 동기화에 대한 오버헤드가 크기 때문에, 상황에 따라서는 사용을 지양해야 할 수도 있다.  
--> synchronized 와 비슷한 것 같다. synchronized 역시 블럭에 진입 전에 메인 메모리부터 데이터를 가져오고 블럭에 진입 후에 캐시를 메인 메모리에 플러시 한다.

### Volatile vs Opaque
opaque 필드는 자바 메모리 모델에서 volatile 필드 보다 더 강력한 메모리 가시성을 제공하는 특별한 종류의 필드이다. opaque 필드는 다른 스레드에서 변경된 값을 즉시 보장하지는 않지만, 이 필드를 수정한 스레드가 이후에 일어나는 다른 메모리 엑세스의 발생 순서를 제어한다.   
opaque 힌트는 JVM에게 해당 변수나 객체에 대해 메모리 가시성과 순서를 보장하는 것을 요청하는 힌트이다. 즉 JVM은 이 힌트를 받으면 해당 변수나 객체에 대한 메모리 업데이트를 CPU 캐시에서 메인 메모리로 즉시 플러시하고, 다른 스레드가 이변수나 객체를 읽을 때 즉시 메인 메모리에서 읽어오게 된다. 이렇게 함으로써, 다른 스레드가 이 변수나 객체의 값을 보장받을 수 있게된다.  

정리  
volatile은 매번 변수에 접근할 때마다 캐시를 플러시하여 메인 메모리와 동기화하므로 항상 최신값을 읽거나 쓸 수 있다. 이렇게 함으로써 메모리 가시성을 보장할 수 있지만 매번 그렇기 때문에 성능이 안좋아질 가능성이 존재한다. 반면에 opaque는 변수에 대한 일관된 가시성을 보장하지는 않지만, 힌트를 제공하여 컴파일러나 프로세서에게 변수의 가시성을 보장하도록 "유도" 할 수 있다는 말이다. 이러한 힌트를 통해 다른 스레드에서 해당 변수를 접근할 때 캐시를 플러시하고 메인 메모리에서 데이터를 가져오도록 유도할 수 있다.  
opaque는 메모리 재배치 문제제를 막아주지느 않는다. 오히려 opaque를 사용하면, 메모리 재배치가 발생할 가능성이 높아진다.  
왜?  
opaque를 사용하면 컴파일러나 하드웨어가 최적화를 수행할 때 해당 변수를 다른 변수와 함께 묶어서 처리할 가능성이 있는데 이럴 경우, 메모리 재배치가 발생할 가능성이 높아진다. 그렇기 때문에 opaque를 사용할 때는 해당 변수를 다른 변수와 함께 묶이지 않도록 주의해야 한다.  opaque를 사용하면 가시성을 보장하면서도 volatile보다 더 나은 성능을 보일 수 있지만, 그렇다고 해서 항상 opaque가 더 좋은 선택은 아니다. 이유는 opaque는 힌트로 메모리 가시성을 제어하기 때문에 메모리 가시성을 보장해야 할 필드가 많아질수록 코드가 복잡해지기 때문이고, 
또한 opaque는 모든 경우에 대해 volatile보다 더 나은 성능을 보장하지는 않는다. 예를 들어, 동시에 여러 스레드에서 해당 필드에 접근할 가능성이 낮거나, 필드가 자주 업데이트 되지 않는 경우에는 volatile보다 opaque가 더 비효율적일 수 있습니다.
따라서, opaque와 volatile 중 어떤 것을 사용할지는 상황에 따라 다르며, 실제로 필요한 경우에만 사용해야 한다!!

## 그래프
- dfs, bfs, tree, bst, mst, topology sort

그래프 문제?  
- 누가 누구를 선택한다. 누가 누구보다 크다. 누가 누구보다 머머하다.
- 즉 특정한 관계에 놓인 상황에서 그래프를 사용할 수 있다.
- 관계가 명확하지 않아도 A 상태에서 B 상태로 변화할 수 있으면 또 그래프 형태로 나타낼 수 있다.

상태 전이 (예: [동전 2](https://www.acmicpc.net/problem/2294))
- 현재 {cost, usecount} --> {ncost, nusecount}

### 용어
방향 그래프(directed graph): 방향이 있는 그래프  
무(방)향 그래프(undirected graph): 방향이 없는 그래프  
사이클: 시작한 정점으로 돌아오는 경로  
인접 행렬: 행렬로 그래프를 표현 (모든 노드를 확인해야 한다.)  
인접 리스트: 링크드 리스트로 그래프를 표현 (연결되어 있는 노드만 확인하면 된다.)  
연결 요소(connected component): 컴포넌트 하나 안에 속한 정점은 서로 모두 이어져 있으며, 다른 컴포넌트 끼리는 이어져 있지 앟는다. 또한 컴포넌트는 항상 최대의 크기  
연결 그래프(connected graph): 컴포넌트가 하나. 즉, 모든 정점들이 연결되어 있는 그래프

- 모든 정점을 방문하려면 각 컴포넌트에 속한 정점들 중 하나씩은 방문 시도를 해야하고, 이를 가장 쉽게 구현하는 방법중 하나는 반복문을 돌면서 방문하지 않은 정점들로 dfs를 시작하는 것이다.
- 이 때 방문 시도 횟수는 컴포넌트의 개수가 된다.

## BFS (Breadth-first search, 너비 우선 탐색)
- 너비를 중시한다?
- 같은 레벨의 노드들을 먼저 방문한다.

여기서 **같은 레벨**이란??
- 거리, 일수, 비용, ... 굉장히 다양하다.

**큐**라는 자료구조를 사용한다.
- 선입 선출(FIFO)
- 즉 먼저 방문한 노드들부터 먼저 검사한다.

### 알고리즘
1. 큐가 비어있지 않을 때까지 방문을 시도한다.
2. 큐에서 지금 나온 정점의 인접한 노드들 중 아직 방문하지 않은 노드들을 다시 큐에다 넣어준다.
3. 반복 순회

레벨 간의 명확한 구분을 하면서 처리, 순회하는 방식

``` cpp
while(!q.empty()) {
    ... 특정 레벨 전처리
    int qsize = q.size();
    for(int i = 0; i < qsize; ++i)
    {
        int curr_node = q.front();
        q.pop();

        ...

        q.push(next_node);
    }
    ... 특정 레벨 후처리
}
```

## dfs(depth-first-search, 깊이 우선 탐색)
- 재귀 함수 사용
- 한 방향으로 깊게 방문하다가 모두 방문했으면 반환되는 방식

**스택**구조이다.
- 방문하는 순서대로 정점을 스택에 쌓고, 방문이 끝나면 스택에서 pop하는 형태로 구현이 가능
- **재귀 함수** 또한 스택 메모리 공간에 쌓아올려지는 구조이기 때문에 재귀 함수를 사용해서 dfs를 구현할 수 있다.

활용: 사이클 (cycle)

어떤 그래프를 dfs로 탐색했을 때 탐색한 엣지만을 남겨 놓으면 트리 형태가 된다.  
--> dfs 트리!!!

어떤 그래프를 dfs트리로 변환했을 때 그래프의 모든 엣지를 4가지로 분류가 가능하다.

1. tree edge (트리 간선)
- 트리 간선은 dfs 트리에 속하는 간선
- 즉 dfs를 하면서 거쳐간 엣지

2. forward edge (순방향 간선)
- dfs를 통해 어떤 연결된 두 노드 사이의 부모-자식? 조상-자손? 관계인 간선
- dfs 트리 간선은 아닌 간선

3. back edge (역방향 간선)
- dfs 트리에서 자식 --> 부모로 거슬러 올라가는 간선

4. cross edge (교차 간선)
- 위 세종류를 제외한 나머지 간선들, 형제 관계

각 간선들은 dfs의 구현에 따라 지위가 바뀔 수 있다.

위의 분류를 통해 **방향 그래프에서 사이클이 존재하는 경우**를 간단하게 정의할 수 있다.  
바로 역방향 간선의 존재 여부이다.  
역방향 간선의 개수 == 곧 사이클의 개수

dfs의 응용
1. visited
- 해당 노드의 방문을 시작했는지 여부
2. finished
- 해당 노드의 방문이 종료되었는지 여부

dfs 탐색을 하면서 방문하지 않은 노드는 방문하고, 만약 해당 노드가 방문된 상태인데 종료가 되지 않았다면, 즉 (visited[node] == true && fisnished[node] == false) 이면 역방향 간선이 존재한다는 것이다.

참고: visited에 방문 순서 기록하기
- 역방향 간선을 찾게 되면 현재 방문하 노드의 번호에서 사이클을 마주친 노드의 방문 번호를 빼면 사이클에 속한 노드의 개수를 알 수 있기 때문이다.
- 스택을 사용하면 사이클에 존재하는 노드들도 알 수 있다!!

예제: [텀 프로젝트](https://www.acmicpc.net/problem/9466)
```cpp
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int vst[100001];
int fsh[100001];
int cnt, ret;

int g[100001];

void dfs(int node)
{
    vst[node] = ++cnt;
    int next = g[node];
    if (!vst[next])
        dfs(next);
    else if (!fsh[next])
        ret += vst[node] - vst[next] + 1;

    fsh[node] = true;
}

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        memset(vst, 0, sizeof(vst));
        memset(fsh, 0, sizeof(fsh));
        cnt = 0;
        ret = 0;

        int n;
        cin >> n;

        for (int i = 1; i < n + 1; ++i)
        {
            int x;
            cin >> x;
            g[i] = x;
        }

        for (int i = 1; i < n + 1; ++i)
        {
            if (!fsh[i])
            {
                dfs(i);
            }
        }
        cout << n - ret << '\n';
    }
    return 0;
}
```

## 트리 tree

1. 연결 그래프이다. (연결 컴포넌트가 하나이다.)
- 참고: 연결 컴포넌트는 모든 정점이 서로 연결되어 있는 정점의 집합
2. 방향을 무시하였을 때, 사이클이 존재하지 않는다.
- 사이클이 없는 것을 보장하는 것 << 이게 정말 크다
3. 트리의 간선의 개수는 반드시 트리의 정점개수보다 1 작음
4. 부모 - 자식으로 가는 간선의 개수는 1개이다. 
5. 임의의 두 정점에 대해서 경로가 유일하다.

**트리는 사이클이 없는 하나의 연결요소이다.**

인접해 있는 두 정점이 있을 때 깊이가 작은 쪽을 부모 노드(parent), 깊이가 깊은 쪽을 자식 노드(child)라고 한다.
- 깊이, 레벨이 더크다 == 아래에 있다.
- 
루트를 제외하면 모든 노드가 자기 자신의 부모 노드와 이어진 간선을 한 개 갖는다. (E = V - 1)

서브 트리: 트리속에 포함되어 있는 또 다른 트리

트리에서 가장 중요히 다뤄야 할 성질은 **트리가 재귀적인 구조를 띈다는 것** 이다.  
어떤 구조? 트리의 자식은 또 트리를 이룬다. (서브 트리)
- dp나 분할 정복 등과 잘 사용되기도 한다고 한다.

트리 순회 방식
1. 전위 순회 (preorder traversal)
2. 중위 순회 (inorder traversal)
3. 후위 순회 (postorder traversal)
4. 레벨 순회 (level-order traversal)

전위 순회
- 모든 정점에 대해서 "자기 자신"을 먼저 방문한 후에 자식들을 방문
- 자식은 왼쪽부터

후위 순회
- 전위 순회와는 반대로 자식들부터 모두 방문하고 나서야 루트(current node)를 방문할 수 있다.
- 왼쪽 자식 --> 오른쪽 자식 --> 루트

중위 순회
- 자식들 중간에 루트를 방문한다.

레벨 순회
- 같은 레벨에 있는 노드들 먼저 순회한다.
- 깊이가 작은 것부터 순회
- 루트를 먼저 방문한 후 루트의 자식들을 큐에 넣는다.
- 큐에 들어있던 노드를 하나씩 방문할 때마다 그의 자식들을 큐에 넣는다.
- 이렇게 해서 큐가 빌 때까지 순회
- BFS 방식

전위, 중위, 후위 순회 --> 재귀 구조로 구현 가능
방문을 하면서 다양한 동작들을 수행할 수 있다.

레벨 순회만이 아주 다른 구조를 띄고 있고 BFS와 동일하다.

재귀적인 구조
- 서브 트리들의 문제를 풀고, 그것들을 조합해서 더 큰 문제를  푸는 방식

## 이진 검색 트리 (binary search tree, bst)
1. 왼쪽 자식이 있다면, 왼쪽 자식의 key값보다 자신의 key값이 커야 한다.
2. 오른쪽 자식이 있다면, 오른쪽 자식의 key값보다 자신의 key값이 작아야 한다.

key값은 비교를 위한 기준일 뿐이다. 꼭 int 값일 필요는 없다.  
중위 순회를 하면 방문하는 순서에 따라 노드 값이 반드시 증가함을 알 수 있다.

이진 검색 트리는 탐색을 하기에 매우 적합하다.  
그런데, 값들이 정해져도 존재할 수 있는 트래의 형태는 상당히 많다. 왜냐하면 입력되는 순서에 따라서 트리 모양이 달라지기 때문이다.  
트리의 높이가 N이고 노드 개수가 2^N - 1 일 때, 모든 리프 노드의 깊이가 같은 형태를 포화 이진 트리 (perfect binary tree)라고 한다.  
포화까지는 아니더라도 모든 리프 노드의 깊이가 N 또는 N 0 1이고, 깊이 N인 단계의 리프 노드들은 왼쪽으로 쏠려 있는 형태를 완전 이진 트리 (complete binary tree)라고 한다.  
++ N - 1 깊이에서는 꽉 차있어야 한다.

포화 이진 트리 역시 완전 이진 트리에 속한다.  
트리가 이진 트리에 가깝게 균형 잡힌 형태라면? 한번의 이진 탐색에 걸리는 시간은 트리 크기가 N일 때 평균 O(logN)이다.
- 한 레벨에서의 노드 개수 = 2^(level)
- 완전 이진 트리 전체 노드의 개수가 N일 때 최대 높이 = logN

균형 잡힌 이진 트리가 아닌 극단적으로 한 쪽으로만 형태가 쏠릴 수도 있는데 이럴 경우 최악의 시간복잡도 O(N)이 나올 수 있다.

따라서 항상 최적의 시간복잡도인 O(logN)에 근접하도록, 지닌값들을 바꾸지 않으면서 그 형태를 변하게 해 스스로 균형을 맞추는 자가 균형 트리 (balanced tree)들이 있다.
- AVL, rb tree, btree, ...

균형 잡힌 트리 규칙
- 어떤 정점에 대해서도 양쪽 서브트리의 높이 차가 1을 넘지 않는다.
- 계속 탐색 시에 최적의 시간복잡도를 낼 수 있다.
- in Java, TreeMap (rb tree)
- in C++, set, map, ...

예제: [나는야 포켓몬 마스터 이다솜](https://www.acmicpc.net/problem/1620)

``` cpp
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
        cout << ret->second << '\n';
    }

    return 0;
}
```

## 유니온 파인드(Union-Find), Disjoint-Set (분릴된 집합)
- union(merge), find 2개의 연산만을 지원
- 분리된 집합을 표현
- 즉 어떤 두 집합 사이에도 교집합의 원소가 하나도 없고, 모든 집합의 합집합은 전체 집합
- A 교 B = 공, A 합 B = 전체
- 같은 집합에 속해있는 지를 판단하기에도 좋고, 집합끼리 병합할 때도 사용하기에 좋다.

**집합 문제**
- 특정 집합에 속하느냐?
- 집합을 합칠 수 있느냐?


이 자료구조는 항상 여러 개의 트리 형태
- 트리 컴포넌트 각각이 하나의 집합
- 트리에 속해 있는 정점들은 같은 집합
- 가장 위에 있는 노드가 각 트리의 루트, 즉 루트가 같으면 같은 집합

### find 연산 (루트 찾기)
두 원소가 같은 집합/트리에 속해 있는지를 확인하는 방법은 각각의 루트를 찾아서 둘이 같은지 비교


``` cpp
int find(int node)
{
	if(parent[node] < 0)	return node;
	return parent[node]  = find(parent[node]);
}
```

parent: 자신의 부모를 가리키는 배열
- 자신이 루트이면 값이 음수 (초기값 -1)

경로 압축
- 재귀 함수를 호출하면서 만약 특정 노드가 루트를 알았다면, 다시 한번 구하기 위해서 또 함수를 호출할 필요가 없게 한다.
- parent[node] = find(parent[node]): 현재 노드의 부모 노드를 루트 노드로 변경
- 재귀 함수로 경로의 모든 노드의 부모를 루트로 재설정
- 이렇게 변경하면 find 함수가 거의 선형 시간복잡도를 가지게 된다.

### union(merge)
- 두 집합을 하나로 합쳐준다.
- 도로 분할하는 것은 굉장히 힘들다고 한다. 하지만 합치는 것은 굉장히 쉬움

어떻게 구현할까?  
1. 두 집합의 루트를 찾는다.
- 같으면 같은 집합에 속해 있기 때문에 합칠 필요가 없다. (return)
2. 루트가 다르다면 한 쪽으로 합쳐준다.

``` cpp
void merge(int a, int b)
{
	a = find(a);
	b = find(b);
	if(a == b) return;
	p[b] = a; // b의 부모를 a로
}
```

### 집합의 크기: parent 배열의 절대값
- 항상 음수이고 절대값이 0보다 크다.
- 초기값 -1 : 처음 크기가 1이라는 것
- 절대값을 집합의 크기로 한다!!

parent 배열의 절대값을 집합의 크기로 할 때 추가적으로 구현해야 할 연산
- 병합 시에 한 쪽 집합의 크기를 다른쪽에 더해주기만 하면 된다.
``` cpp
void merge(int a, int b)
{
	a = find(a);
	b = find(b);
	if(a == b) return;
	p[a] += p[b]; // 음수 더하기 음수
	p[b] = a; // b의 부모를 a로
}
```

최종
- 원래 집합 크기가 큰 쪽이 루트가 되도록 할 수 있다. 
- 이러면 좀 더 시간적인 측면에서 최적화가 가능
``` cpp
void merge(int a, int b)
{
	a = find(a);
	b = find(b);
	if(a == b) return;
	if(p[a] < p[b]) // 음수니까  실제로는 p[a]의 크기가 큰 경우 >> a가 합집합의 루트가 되도록 한다. b의 부모를 a로
		p[a] += p[b], p[b] = a; 
	else
		p[b] += p[a], p[a] = b;
}
```

## 최소 스패닝 트리 (Minimum Spanning Tree, MST)
- 모든 정점들을 연결하는 부분 그래프 중에서 그 가중치의 합이 최소인 트리

스패닝 트리: 신장 트리
- 무향 연결 그래프가 있을 때 그 그래프에서 간선을 부분적으로 선택하여 만들 수 있는 트리이다.
- 기존 그래프의 정점애 개수와 같다.
- 트리: 연결 그래프 + V - 1 개의 간선 개수

최소 스패닝 트리는 그래프의 간선마다 가중치가 있을 때, 간선의 가중치 합이 최소인 스패닝 트리이다. 하나의 그래프에 대해 스패닝 트리는 여러개일 수 있다. 즉 MST 도 여러개일 수 있다

최소로 모든 노드들을 연결하기만 하면 된다!

### **크루스칼 알고리즘**

과정
1. 간선들을 가중치가 작은 순으로 정렬하고, 정점들을 각각의  컴포넌트(parent[node] = -1)로 초기화 한다,
2. 간선들을 훑으면서 양쪽 정점을 포함한 컴포넌트가 연결되어 있지 않으면 간선을 뽑고 연결한다. (find and merge)
3. 간선 V - 1 개가 뽑히면, 그 간선들과 정점들이 이루는 그래프가 MST 다.

크루스칼 알고리즘에는 유니온 파인드 알고리즘이 필요하다.

시간 복잡도
1. 정렬: O(ElogE)
2. V 번 union and find: O(V * (1))  
= 총 O(ElogE)

예제: [최소 스패닝 트리](https://www.acmicpc.net/source/59703222)
``` cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
int parent[10002];
int find(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = find(parent[x]);
}
bool merge(int a, int b)
{
    a = find(a), b = find(b);
    if (a == b)
        return false;

    // a 가 많이 담고있다. --> b를 a 쪽으로
    if (parent[a] < parent[b])
        parent[a] += parent[b], parent[b] = a;

    else
        parent[b] += parent[a], parent[a] = b;
    return true;
}
struct Edge
{
    int u, v, w;
    bool operator<(const Edge &x) const
    {
        return w < x.w;
    }
} edge[100001];
int main()
{
    int V, E, s, e, w;
    cin >> V >> E;
    for (int i = 0; i < E; ++i)
    {
        cin >> s >> e >> w;

        edge[i] = { s, e, w };
    }

    sort(edge, edge + E);
    memset(parent, -1, sizeof(parent));

    long long ret = 0;

    for (int i = 0; i < E; ++i)
        if (merge(edge[i].u, edge[i].v))
            ret += edge[i].w;
    cout << ret << '\n';
    return 0;
}

```


























































