# Weekly I Learned (0502 ~ 0508)

## Hash Table
- 탐색/삽입/삭제: O(1)
- (key, value) mapping

1. Table
- capacity: n
- 2의 멱수 (2^k)

2. Hash Function
- 최대한 key에 대한 해쉬값이 고르게 분산되도록 한다.
- 그래야 충돌(collision) 횟수가 작아진다.
- c-universal: 충돌 확률이 "c/m" 인 해쉬함수

참고: 정수형 데이터에 대한 해쉬 함수  
- division 해싱
- multiplication method
- universal hashing
  - 해시 함수: h(k) = ((ak + b) mod p)
  - k 는 입력값, a, b 는 해싱에 사용할 임의의 수, p 는 충분히 큰 소수
- folding method

3. 충돌 회피 방법  
linear probing:    
- 충돌 시 그 아래의 빈 슬롯을 찾은 후 삽입한다.  

### chaining  
- 슬롯이 연결 리스트로 되어 있다.
- entry 에 다음 entry 를 가리킬 수 있눈 next 가 있다.
- 슬롯의 처음을 head(sentinel) 로 두는 방식이 있고 처음보토 요소를 넣는 방식이 있다.
- 처음을 head(sentinel) 로 사용하면 삽입 시에 바로 앞에 놓을 수 있고, 삭제 또한 편하다.
- 처음부터 요소를 넣는 방식의 삽입은 연결 리스트의 끝에 삽입해야 한다.

### load factor (n/m)
- m = capacity
- n = 원소 개수
- load factor 가 커지면 커질수록, 즉 원소 개수가 많아지면 많을수록 충돌 확률이 올라간다.
- 따라서 원소 개수가 일정한 크기 이상이 되면 resize 를 호출해서 배열의 크기를 증가시켜야 한다.

(load factor * capacity) == n >= threshold
- resize

in java HashMap, load factor 의 기본값은 0.75f 이다.
- threshold = load factor * capacity
- if (size >= threshold) resize

### implementation (슬롯 처음 요소를 사용)
- key, value 모두 int 형이라고 가정

### put(key, value) 
1. table is null or table length == 0
- create table or resize

2. table[i = hash & (n - 1)] == null
- 사용 가능
- table[i] = create node(key, value, hash, null);
3. null 이 아니면?
- key 가 같은 요소가 있다면? 교체
- key 가 같은 요소가 없다면? 맨 뒤에 삽입

node *p = table[i];
node *prev;
while(p != null && p.key != key)
{ … }

if (p == null)
- 뒤에 삽입 (prev)
else 
- 교체
- return oldvalue

if (++size > threshold)
	resize();
return null;

### remove(key)
1. table is null or table length == 0
- return null;

2. 첫번째 요소
- 따로 처리해야 한다.
- table[index] = node.next

3. while (e = p.next != null){ … }
- 만약 같다면? node = e;

4. node 처리 << 삭제될 노드
- null 이 아니어야 한다.
- p.next = node.next
- —size;

5. 해제
- free(node);

### find(key)
- hash값 찾아서 p.next == null 일 때까지 loop !!

### resize()



## Binary Search Tree (이진 검색 트리)

## AVL Tree 
- 균형 이진 트리 중 하나이다.
- self balancing tree is a binary search tree that balances the height after insertion and deletion according to some balancing rules.

BST 탐색/삽입/삭제 연산의 최악의 시간 복잡도는 O(h) 이다.
만약 트리가 한쪽으로 쏠린 형태가 된다면, 즉 높이가 n 이면 결국 연산의 최악의 시간복잡도는 O(n) 이다.  
AVL 트리는 높이를 "log n" 으로 유지시키도록 하여 탐색/삽입/삭제 연산의 최악의 시간 복잡도가 O(n) 에서 O(log n)으로 감소하였다.

### balance factor?
- balance 를 유지시키도록 하는 요인
- 이 bf 를 보고 트리가 균형 있게 존재하는지 확인할 수 있고, 만약 균형적이지 않으면 수정한다.

bf = height(right(n)) - height(left(n))   
avl tree 에서는 이 bf 요소가 반드시 -1, 0, 1 을 유지해야 한다.

삽입/삭제 이후, 노드들의 bf 를 확인한다.  
만약 bf 가 1 보다 크거나 -1 보다 작으면, "리밸런싱(rebalance)" 을 수행한다.  

tree를 "리밸런스"하기 위해서는 2개의 연산이 필요하다.
- right rotation
- left rotation
  
### right rotation
- 이진트리 T1가 있는데, Y를 루트로 하고, X 는 Y 의 왼쪽 자식이고, Z 는 X 의 오른쪽 자식이다.
- BST의 특성으로 인해 X < Z < Y.   
- Y 의 right rotation 실행 이후의 트리는 X 를 루트로하고, X 의 오른쪽 자식은 Y 이고, Z 는 Y 의 왼쪽 자식이 되었다.
- 이 트리 역시 BST의 특성을 유지한다. X < Z < Y  

``` c
node *rotateRight(node *y)
{
    node *x = y->left;
    node *z = x->right;
    x->right = y;
    y->left = z;
    x->parent = y->parent;
    y->parent = x;
    if (z != NULL)
        z->parent = y;
    updateHeight(y);
    updateHeight(x);
    return x;
}
```

### left rotation
- right rotation 과 유사하다.
- Y 를 루트로하고, X 는 Y 의 왼쪽 자식, Z 는 X 의 오른쪽 자식이다.
- Y 의 left rotation 실행 이후의 트리는 X 를 루트로 하고, X 의 왼쪽 자식은 Y 이고, Z 는 Y 의 오른쪽 자식이다.

``` c
node *rotateLeft(node *y)
{
    node *x = y->right;
    node *z = x->left;
    x->left = y;
    y->right = z;
    x->parent = y->parent;
    y->parent = x;
    if (z != NULL)
        z->parent = y;
    updateHeight(y);
    updateHeight(x);
    return x;
}
```

### Rebalancing
- 노드들의 어떠한 변화 이후라도 AVL 트리는 "밸런스"를 지키도록 한다.
- 이 때, right rotation, left rotation 연산을 사용할 수 있다.

unbalanced tree
- 적어도 하나의 노드의 balance factor가 2 or -2 이다.

Z 의 bf 가 2 이면, Z 를 루트로하는 서브트리는 2가지 상황이 존재한다  
- considering Y as the right child of Z.

1. Y 의 오른쪽 자식의 높이는 Y 의 왼쪽 자식의 높이보다 클 때
- Z 의 왼쪽 회전을 함으로써 rebalance 할 수 있다.

2. Y 의 오른쪽 자식의 높이는 Y 의 왼쪽 자식의 높이보다 작을 때
- Y 를 오른쪽 회전 시킨다. 그렇게 되면 1 번의 상황과 같게된다.
- Z 를 왼쪽 회전 시킨다.

Z 의 balanace factor 가 -2 이면, 역시 2가지 상황이 존재한다.
- bf 가 2일 때와는 반대로 "리밸런스" 해주면 된다.

``` c
node *rebalance(node *z)
{
    updateHeight(z);
    int bf = getBalance(z);
    if (bf > 1)
    {
        if (height(z->right->right) > height(z->right->left))
            z = rotateLeft(z);
        else
        {
            z->right = rotateRight(z->right);
            z = rotateLeft(z);
        }
    }
    else if (bf < -1)
    {
        if (height(z->left->left) > height(z->left->right))
            z = rotateRight(z);
        else
        {
            z->left = rotateLeft(z->left);
            z = rotateRight(z);
        }
    }
    return z;
}
```

### 삽입(insert) 연산 시 밸런스 유지시키기
- BST 특성에 맞게 키를 삽입할 위치를 찾는다.
- 삽입 이후에, 밸런스가 안맞을 수 있다.
- 그렇기 때문에 삽입 이후에는 balnce factor를 확인하고 그에 맞추어 재조정을 해야할 수도 있는데, 이 때 new_node 부터 root 노드 까지의 경로의 모든 노드를 확인하면서 재조정을 해야한다.

### 삭제(delete) 연산 시 밸런스 유지시키기
- BST 삭제 연산과 동일?하게 삭제연산을 한다.
- 삭제 역시, 연산 이후에 밸런스가 안맞을 수 있기 때문에 "원래 삭제할 위치"인 노드에서 부터 root 노드까지의 경로의 모든 노드를 확인하면서 재조정을 한다.

``` c
void rebalancing(avl_tree *t, node *prev)
{
    for (node *cur = prev; cur != NULL; cur = cur->parent)
    {
        node *cp = cur->parent;
        if (cp != NULL)
        {
            if (cur->key < cp->key)
                cp->left = rebalance(cur);
            else
                cp->right = rebalance(cur);
        }
        if (cur->parent == NULL)
            t->root = cur;
    }
}
```

## CSAPP

### 3 장 프로시저

스택
- 프로시저 호출에 대한 상태 정보를 관리, 프로시저 호출을 위한 자료구조
- 상태 정보? 인자, 리턴 주소, callee-save 레지스터, 지역변수, … 
- “지역” 데이터
- %rsp: 스택 top 주소
- 낮은 주소 방향으로 쌓인다.

push & pop

1. pushq src
- %rsp 8 감소
- %rsp 위치에 src 저장

2. popq dest
- %rsp 위치의 데이터 회수 및 레지스터(dest)에 저장
- %rsp 8 증가

프로시저 매커니즘 

1. 제어 이동
- 스택은 함수의 호출과 리턴 매커니즘을 뒷바침한다.
- 나중에 호출된 함수가 먼저 리턴하는 특성이 스택의 LIFO 구조와 비슷하기 때문!

callq Lable
- 함수 호출
- 먼저 복귀 주소를 현재 스택 프레임에 푸시(push) 후 Label 주소로 점프

ret
- 함수 리턴
- 스택에 저장된 복귀 주소를 팝(pop) 후 복귀 주소로 점프

데이터 전달
- 함수의 1 ~ 6번째 인자는 레지스터에 저장
- 7 ~ n 번째 인자는 “Caller“의 스택 프레임에 “역순서”로 푸쉬된다.
- Caller는 call 명령어를 통해 또 다른 홈수를 호출하기 전에 반드시 인자들을 적절한 레지스터 혹은 스택 공간에 넣어주는 작업이 필요하다.
- 따라서 인자가 6개보다 많으면 복귀 주소보다 인자가 먼저 스택에 쌓이게 될 것이다.
- 참고로 복귀 주소도 Caller의 스택 프레임에 쌓인다.

스택 프레임(stack frame) : 지역 데이터의 관리
- 재진입성: 하나의 프로시저를 동시적으로 여러 개 인스턴스화 하는 게 가능하다.
- 각 인스턴스의 상태 정보(인자, 지역변수, 복귀주소 등)를 저장하기 위한 공간이 필요한데, 그곳이 바로 스택!

프로시저(함수) 하나가 호출될 때마다 스택 프레임(stack frame) 하나가 스택에 푸시되어 그곳에서 그 함수의 지역 데이터들이 관리되며, 함수가 리턴할 때 해당 스택 프레임이 스택에서 팝이 된다.

스택 프레임의 할당 (allocate)
- 함수를 호출할 때 실행하는 call 명령어에 의해 복귀 주소가 “Caller 스택 프레임”에 푸쉬되고, 호출된 함수 내에서 초반부에 실행되는 “Set-up” 코드에 의해 해당 함수 내에서 필요로 하는 지역 데이터들이 할당된다.

스택 프레임의 해제 (release)
- 호출된 함수 내에서 리턴하기 직전에 실행되는 “Finish” 코드에 의해 현재 스택 프레임에 저장되어 있는 지역 데이터들이 팝이 되고, 리턴할 때 실행하는 ret 명령어에 의해 “Caller” 스택 프레임에 존재하는 복귀 주소를 팝을 하고 PC 를 복귀 주소로 이동시킨다.

스택 프레임 구조
- Caller가 프로시저 호출 시

1. Arguments : 필요한 경우(전달할 파라미터/인자가 7 개 이상일 때, 7 개 이상부터)
2. Return address: PC + 4 (call 명령어 이후의 명령어 주소를 가리키게 한다.)
3. Saved register: Callee-save register ?? < 헷갈림
4. Local Variables : 지역 변수들
5. Argument Build : 프로시저를 호출하여 전달할 인자 빌드 ??

레지스터의 백업 및 복원
- Caller-save regiseter 와 Callee-save 레지스터

1. Caller-save 레지스터
- 마음껏 건드려도 괜찮은 레지스터로, 새로 호출할 함수가 그 값열 변경시켜도 된다.
- 따라서 새로 호출할 함수에 의해 값이 손실되면 안되는 경우에는, “caller가 직접 자신의 스택 프레임”에 백업하고, 나중에 해당 함수가 리턴한 직후에 다시 복원을 해야 한다.
- 일반적으로 caller-save 레지스터 -> arguments -> return address 순으로 스택에 쌓인다.
- return address 가 가장 낮은 주소 (스택의 top)
- 스택은 아래로 쌓인다. (주소가 감소하면서 쌓인다.)  

- 근데? 반환 주소를 스택에 저장하는 부분이 없기도 한가?
- 교재에서는 반환 주소를 스택에 저장하는 부분이 없다.

2. Callee-save 레지스터
- Callee-save 레지스터는 함부로 건드리면 안 되는 레지스터로, 새로 함수가 호출되더라도 Caller에게 리턴했을 때 그 값이 변경되어 있으면 안된다.
- 따라서 자신이 Callee-save 레지스터를 건드려야 하는 상황이라면 그 전에 먼저 그 값을 자신(callee)의 스택 프레임에 백업하고, 나중에 리턴하기 직전에 다시 복원을 해야 한다.
- %rbp: 스택 프레임의 Frame pointer(base pointer)로 사용되는 레지스터로, 함부로 건드리면 안 되는 Callee-save 레지스터이다.
- %rsp: Callee-save 레지스터의 특별한 경우로, 함수 리턴 직전 “Finish” 코드에 의해 원래 값으로 복원이 된다.


1. call_incr2 가 callee 입장으로, %rbx 레지스터를 사용하려고 하는데 이 레지스터는 callee-save register 이므로, 스택에 저장해야 한다.
- callee-save 레지스터를 백업(push)했으면, 이후에 반드시 복원(pop)을 해야한다.

2. sub $16, %rsp ? 
- 2 개의 item 을 위한 스택 공간 조정

3. %rdi 레지스터는 Caller-save 레지스터이므로, caller 입장에서 백업해야 하는 레지스터이다.
- 그러므로 %rdi(x 값)을 %rbx 레지스터에 백업 후에 나중에 x + v2 할 때, %rbx (백업된 레지스터)를 사용한다.

재귀 함수
- 재귀 함수를 구현하는 것은 별도의 작업이 필요하지 않다.
- 단순히 또 다른 함수를 호출하는 것과 같은 매커니즘으로 처리하면 된다.

참고: leaq
- load effective address
- 주어진 메모리 주소를 계산하고, 해당 주소를 포함하는 메모리 위치의 주소를 레지스터에 로드하는 역할을 한다.

ex)
leaq (%rax, %rbx, 8), %rdx
- %rax + (%rbx * 8) 를 계산하고, 해당 주소를 포함하는 메모리 위치의 주소를 %rdx 레지스터에 저장한다.

계산 방법:
- leaq disp(base, index, scale), dest

 disp 는 바이트 단위의 상수(offset)입니다. 
base 는 베이스 레지스터(base register)이며, index 는 인덱스 레지스터(index register)입니다. 
scale 은 인덱스 레지스터의 스케일링 인수(scale factor)입니다. 
dest 는 결과를 저장할 대상 레지스터(destination register)입니다.

주소 계산식:
- dest ← disp + base + (index × scale)

ex)
leaq 12(%rip), %rax ; rip = 현재 명령어 주소 + 4
- 12 + %rip? arr[3]의 주소 (arr가 4바이트 일 때,)

### 7 장 링킹

링킹이란?
- 재배치 가능한 오브젝트 파일들을 결합하여 메모리에 로드되어 실행될 수 있는 하나의 실행 파일을 만드는 과정을 의미한다.
- 실행 가능한 목적 파일 생성
- 링킹은 컴파일 타임에 수행될 수도 있고 (정적 링킹), 로드 타입이나 런타임 때 수행될 수도 있다. (동적 링킹)
- 링커는 링킹을 수행하는 프로그램을 의미한다.

참고: 로드? 로더?
- 디스크로부터 실행 가능한 목적 파일 내의 코드와 데이터를 메모리로 로드/복사하고 이 프로그램의 첫 번째 명령어, 즉 엔트리 포인트로 점프해서 프로그램을 실행
- 프로그램의 엔트리 포인트? _start 함수의 주소 (main 호출)

링커는 각 모듈의 독립적인 컴파일을 가능하게 한다.
- 모듈? C 소스파일, 재배치 가능한 오브젝트 파일, …
커다란 프로그램을 하나의 소스 파일로 개발하는 것이 아니라, 관리하기 용이한 작은 단위의 모듈들로 나눠 개발할 수 있게 되었다.
특정 모듈을 수정하면, 해당 모듈(소스 파일)만 다시 컴파일하여 이미 컴파일되어 있는 다른 모듈(재배치 가능 오브젝트 파일)들과 링킹을 수행하면 된다.

링커, 링킹을 공부해야 하는 이유
1.  큰 규모의 프로그램을 개발하게 되면 링킹과 관련된 에러들에 많이 부딪힐 수 있다.
- 이 때 링킹의 원리를 모른다면 디버깅에 곤란을 겪을 수 있다.
2. 위험한 프로그래밍 에러를 피하기 위해서이다.
- 프로그래머가 예상치 못한 결과가 나올 수 있는 코드임에도 링커가 “에러나 워닝”을 띄우지 않는 경우가 있다. 
- 예를 들어, 링커가 동일한 이름의 Weak 심볼을 여러 개 선언하는 것을 허용한다는 것을 모른다면 디버깅에 어려움을 겪을 수 있다.
3. 프로그래밍 언어의 스코프 규칙이 어떻게 구현되는지 이해할 수 있다.
- 예를 들어, 링킹의 원리를 알면 전역 변수와 지역 변수의 차이, 그리고 static 선언이 어떠한 의미를 지니는지 이해할 수 있다.
4. 중요한 시스템 관련 개념들을 이해할 수 있다.
- 예를 들어, 링킹은 프로그램의 로딩 및 실행 과정, 가상 메모리 기술, 페이징, 메모리 매핑 등의 개념들과 아주 밀접하게  연관되어 있다.
5. 공유 라이브러리를 활용할 줄 알아야 하기 때문이다.
- 공유 라이브러리의 동적 링킹 <<

핵심 주제
1. 컴파일 타임에 이뤄지는 정적 링킹 (static linking)
2. 로드 타임 시 이뤄지는 공유 라이브러리의 동적 링킹
3. 런타임 시 이뤄지는 공유 라이브러리의 동적 링킹

ELF 파일 포멧 기준으로 설명.
그러나 ISA, 운영체제, 그리고 오브젝트 파일 포멧이 다른 환경에서도 링킹의 핵심적인 원리는 크게 달라지지 않는다.

컴파일 방법? 컴파일 시스템?
- 대부분의 컴파일 시스템은 선행 처리기(cpp), 컴파일러, 어셈블러, 링커(ld)를 호출하는 컴파일러 드라이버 제공

gcc c to o
- 
cpp c to i
cc1 i to s
as s to o (재배치 가능한 오브젝트 파일)
ld o to o (실행 가능한 오브젝트 파일)

실행?
./{이름}.o
- 쉘(shell): 로더라는 os의 함수 호출 
- 로딩: 실행 파일의 코드와 데이터를 메모리에 로드한 뒤 CPU 제어를 해당 프로그램의 시작 주소로 전환

정적 링킹?
- 입력으로 주어진 여러개의 재배치 가능한 오브젝트 파일들을 입력으로 받아서 하나의 실행 가능한 오브젝트 파일을 생성한다.

재배치 가능한 오브젝트 파일??
- 섹션, 세그먼트가 나누어져 있다.
- ex) 코드, 데이터, 스택, 힙, ...

링커는 이러한 세그먼트들을 적절히 합쳐주고, 각 세그먼트에게 런타임에 필요한 “가상 주소”를 알맞게 부여하며, 이에 맞게 코드 블록과 데이터 블록들에 존재하는 메모리 주소들을 적절히 수정한다.
- 재배치 과정 
- 링킹 과정에 필요한 대부분의 정보들은 컴파일러와 어셈블러가 만들어서 재배치 가능 오브젝트 파일안에 담아준다.

링커는 그 정보들을 읽어서 링킹을 수행할 뿐, 타겟 머신에 대해서는 잘 알지 못한다.

정적 링킹 단계
1. 심볼 해석 (symbol resolution)
- 재배치 가능 오브젝트 파일들에서 등장하는 각각의 심볼 참조를 정확히 하나의 심볼 정의에 연결하는 작업
- 각 모듈(재배치 가능 오브젝트 파일)은 특정 심볼을 정의하거나 참조하게 된다.

심볼?
- 함수, 전역 변수, static 변수 등? 을 의미한다.
- non-static 지역 변수는 포함하지 않는다.
- non-static 지역 변수는 런타임 스택에서 관리된다.

2. 재배치 (relocation)
- 링커는 코드 및 데이터 섹션등의 섹션들을 적절히 런타임 가상 주소로 재배치하고, 이에 따라 각 심볼 정의에도 알맞은 가상 주소를 부여한다.
- 각 심볼 참조가 올바른 심볼 정의를 가리킬 수 있도록 수정해준다.
- 이러한 작업은 어셈블러에 의해 만들어져서 재배치 가능 오브젝트 파일 안에 담기는 “재배치 엔트리”들의 정보를 바탕으로 수행된다.

섹션? 블록?
프로그램 코드, 프로그램 데이터, 링커와 로더를 안내하는 데이터 구조를 포함

링커는 이런 섹션/블록들을 함께 연결하고 이 연결된 블록들을 위한 런타임 위치를 결정하며, 코드와 데이터 블록 내에 여러 가지 위치를 수정

오브젝트 파일

3가지 형태
1. 재배치 가능 오브젝트 파일 (relocatable object file)
- 링킹 시에 다른 재배치 가능 오브젝트 파일들과 결합될 수 있는 오브젝트 파일 (바이터리 코드와 데이터를 포함)
2. 실행 가능 오브젝트 파일(executable object file, 실행 파일)
- 코드와 데이터가 바로 메모리에 로드되어 실행될 수 있는 오브젝트 파일
3. 공유 오브젝트 파일 (shared object file)
- 로드 타임이나 런타임에 동적으로 메모리에 로드되어 링킹될 수 있는 재배치 가능 오브젝트 파일을 의미한다.

재배치 가능 오브젝트 파일/공유 오브젝트 파일은 컴파일러와 어셈블러에 의해 만들어지며, 실행 파일은 링커에 의해 만들어진다.

오브젝트 파일 포멧 (형태, 구조)
- ELF(executable and linkable format)라는 오브젝트 파일 포멧을 기준으로 설명
- 그러나 포멧이 달라져도 기본적인 링킹의 원리는 크게 달라지지 않는다.

Relocatable Object Files


각 영역의 역할
1. ELF 헤더
- 시스템의 속성 정보, 환경 변수(시스템의 워드 사이즈, 바이트 오더링, …)
- 링커가 이 파일을 읽어서 분석할 때 알아야 하는 정보들 
- ELF 헤더의 크기, 오브젝트 파일의 유형, 타겟 머신의 유형, 섹션 헤더 테이블의 파일 오프셋, 섹션 헤더 테이블에 존재하는 엔트리의 개수와 각 엔트리의 크기 등
- 링커는 이 헤더를 통해 섹션 헤더 테이블에 가서 각 섹션의 크기와 위치정보를 기반으로 링킹을 수행하는 거겠죠?

2. 섹션
- .text: 기계어 코드
- .rodata: 문자열 등의 상수, switch 점프 테이블과 같은 “읽기 전용 값”들이 저장
- .data: 0이 아닌 값으로 초기화되는 전역 변수 및 정적 변수(static)
- .bss: 0으로 초기화되거나 초기화가 되지 않는 전역 변수 및 정적 변수, 공간 차지 X
- .symtab: 이 모듈에서 정의하거나 참조하는 모든 심볼(함수, 전역 변수, 정적 변수 등)들의 정보가 저장, 기본적인 섹션
- .rel.text: 링킹 시 재배치가 필요한 .text 섹션 내 메모리 로케이션들의 정보
- .rel.data: 링킹 시 재배치가 필요한 .data 섹션 내 메모리 로케이션들의 정보
- .debug: 디버깅을 위한 정보 (정의된 지역변수 및 typedef의 정보들을 저장하는 디버깅 심볼 테이블)
- .line: 원본 C 소스 파일의 라인들과 .text 섹션에 존재하는 기계어 코드들의 매핑 정보
- .strtab: 심볼 이름들에 해당하는 문자열과 섹션 헤더 테이블에 존재하는 섹션 이름들에 해당하는 문자열

참고로: C 지역 변수는 런타임 스택에 저장되며, .data나 .bss 섹션에 나타나지 않는다.

3. 섹션 헤더 테이블
- 각 섹션의 크기와 위치 정보
- 각 섹션에 대해 고정된 크기의 엔트리를 갖는다.

심볼의 종류
- 전역 심볼과 지역 심볼로 구분된다.

전역 심볼 (global symbol)
- 모듈 m에 의해 정의되고 다른 모듈에 의해 참조될 수 있는 심볼
- 모듈 m에 의해 참조되지만 다른 모듈에 정의되어 있는 심볼
- non-static 함수, non-static 전역 변수


지역 심볼 (local symbol)
- 모듈 m에 의해 정의되고 오직 모듈 m에 의해서만 참조될 수 있는 심볼
- static 함수, static 변수 (전역/지역)

참고: static 지역 변수?
런타임 스택 영역에서 저장 및 관리되는 일반적인 지역 변수와 달리, static 지역 변수는 컴파일러에 의해 고유한 이름을 부여받고 심볼 태이블에 지역 심볼로서 저장이 된다.
그리고 초기화 여부에 따라 .data 섹션 또는 .bss 섹션에 들어가게 된다.
고유한 이름을 부여받는 이유는 서로 다른 함수 내에 동일한 이름의 static 지역 변수가 선언될 수 있기 때ㅜㅁㄴ이다.

참고: static == private
static 타입으로 선언된 모든 전역변수나 함수는 모듈에 private하다.
- 다른 모듈에서 접근할 수 없다.
static 타입 없이 선언된 전역변수나 함수는 public이며, 다른 모듈에 의해 접근될 수 있다.
만약 변수나 함수를 보호하고 싶다면 static 타입을 사용해야 한다. (private 으로 감추기)

### 심볼 테이블 엔트리

name: 심볼 이름에 해당하는 문자열의 .strtab 섹션 내 오프셋 (위치)
type: type? function or data
binding : 심볼의 종류, global or local
section: 심볼이 할당된 섹션, 해당 섹션의 섹션 헤더 테이블 내 인덱스,
value: 심볼의 위치, 재배치 가능 오프젝트 파일이면 섹션 내 오프셋 or 실행 파일이면 절대 가상 주소
size: 심볼 데이터의 바이트 단위 크기

심볼 테이블 예시:  
Nds: 섹션 헤더 테이블 내 인덱스, 섹션 인덱스
- 1: .text 섹션
- 3: .data 섹션
- UND: UNDEF 섹션, 즉 다른 모듈에서 정의되어 있는 심볼

### **심볼 해석**
- 링커가 입력으로 들어오는 재배치 가능 오프젝트 파일들의 심볼 테이블 정보를 바탕으로 각각의 심볼 참조를 정확하게 하나의 심볼 정의에 연결시키는 작업을 뜻한다.
- 심볼 테이블 엔트리? 심볼 정의
- 심볼 참조란 코드 상에서 해당 심볼을 참조하는 부분을 의미한다.

지역 심볼의 해석
- static 함수, static 변수
- 지역 심볼은 정의되는 모듈 내에서만 참조가 가능할 뿐만 아니라, 컴파일러는 한 모듈 내에서 각 지역 심볼의 정의가 고유하다는 것을 보장한다.
- static 전역 변수는 동일한 이름으로 여러 번 정의되면 컴파일 에러가 발생한다.
- 또한 static 지역 변수도 하나의 함수 내에서는 동일한 이름으로 여러 번 정의되면 컴파일 에러가 발생하며, 서로 다른 함수에서 동일한 이름으로 정의가 되더라도 컴파일러에 의해 각기 다른 이름을 부여 받아 심볼 테이블에 들어가게 된다.
- 따라서 지역 심볼의 참조는 동일한 모듈의 심볼 테이블 상에 존재하는 심볼 정의를 그대로 연결하기만 하면 된다.

전역 심볼의 해석
- 전역 심볼의 경우 정의되는 모듈 외부에서도 참조가 가능하다.
- 이로 인해 전역 심볼의 참조에 대응되는 심볼 정의를 현재 모듈의 심볼 테이블에서 찾지 못할 수도 있다.
- 이런 경우 컴파일러는 해당 전역 심볼이 다른 모듈에 정의된 것이라고 가정하고, 섹션이 UNDEF 인 심볼 테이블 엔트리를 만들어서 심볼 테이블에 저장한다.
- 그리고 나중에 링커가 섹션이 UNDEF 인 각각의 심볼 테이블 엔트리에 대해 올바른 심볼 정의를 다른 모듈의 심볼 테이블에서 찾아 심볼 해석을 진행한다.
- 이때 만약 링커가 입력으로 들어오는 재배치 가능 오브젝트 파일의 심볼 테이블들을 전부 확인했는데도 해당 심볼 참조에 대한 심볼 정의를 찾지 못하면???
- 에러 발생 and 바로 종료

또한, 전역 심볼의 경우 여러 모듈이 동일한 이름을 ㅗ정의하는 것이 가능하다.
왜? 컴파일 단계에서는 다른 모듈에서 동일한 이름의 전역 심볼을 정의했는지 알 방법이 없기 때문이다.
- 동일한 모듈 내에서 각 심볼의 정의가 고유하다는 것은 보장한다. 다른 모듈 간에는 보장하지 못한다.
만약 여러 모듈이 동일한 이름의 전역 변수를 정의했다면, 링커는 심볼 해석을 위해 전역 심볼의 중복 문제를 먼저 처리해야 한다.
상황에 따라서 에러를 발생시키고 즉시 종료할 수도 있고, 동일한 이름으로 정의된 여러 개의 전역 심볼들 중 하나를 선택하고 나머지를 폐기할 수도 있다.
전역 심볼 중복 문제를 처리하고 나면, 각 전역 심볼은 고유한 이름을 가진다는 것이 보장되므로 해당 이름의 심볼 정의를 심볼 테이블에서 찾아 심볼 해석을 진행하면 된다.

전역 심볼 중복 문제 처리 (COMMON vs .bss)

전역 심볼은 초기화 여부에 따라 다시 Strong 심볼과 Weak 심볼로 구분된다.
- non-static 함수와 초기화되는 non-static 전역변수는 Strong 심볼에 해당 (초기화 O 전역 심볼)
- 초기화되지 않는 non-static 전역 변수는 Weak 심볼 (초기화 X 전역 심볼)

Strong 심볼과 달리 Weak 심볼은 동일한 이름으로 여러번 정의될 수 있다는 특징이 있다.


컴파일러는 컴파일 단계에서 각 심볼들의 정보를 파악한 뒤 이름 .s 파일에 담아서 어셈블러에게 전달한다.
이 때, 자기 자신 모듈에서 정의되는 전역 심볼의 경우에는 Strong 심볼인지, 아니면 Weak 심볼인지를 파악하여 이 정보도 함께 어셈블러에게 전달한다.
그러면 어셈블러는 그렇게 전달받은 심볼들의 정보를 바탕으로 심볼 테이블을 구성하여 재배치 가능 오브젝트 파일을 만들게 된다.
따라서 나중에 링커가 링킹을 수행하는 시점에는 이미 심볼 테이블에 각 전역 심볼의 유형(Strong or Weak) 정보가 담겨있기 때문에, 링커는 이러한 정보를 바탕으로 전역 심볼 중복 문제를 처리한다.

리눅스 시스템의 링커는 다음 3가지 기준으로 전역 심볼 중복 문제를 처리한다.
- 모든 모듈의 심볼 테이블을 검사하겠지?
1. 동일한 이름의 strong 심볼이 여러개 정의되어 있다면 에러를 발생시키고 즉시 종료한다.
2. 동일한 이름의 Strong 심볼 하나와 Weak 심볼 여러개가 정의되어 있다면 Weak 심볼은 전부 폐기하고 Strong 심볼을 선택한다.
3. 동일한 이름의 Weak 심볼이 여러개 정의되어 있다면 그중에 아무거나 선택한 뒤 나머지 Weak 심볼들을 전부 폐기?
- 심볼을 선택한다 함은 그 이름의 심볼 참조들을 해당 심볼 정의에 연결하게 될 것이라는 뜻이다. 즉 해당 심볼 정의를 사용한다는 의미.
- 폐기? 심볼 테이블에서 심볼 정의를 삭제

링커의 이름 규칙 (이름 중복 문제 해결)

어셈블러는 심볼 테이블에 각 전역 심볼의 유형정보를 어떻게 저장할까?
이는 곧 링커가 심볼 테이블을 보고 각 전역 심볼의 유형을 어떻게 파악할 수 있는지와 동일한 물음이다.

어셈블러는 컴파일러로부터 전달받은 심볼들의 정보를 바탕으로 심볼 테이블을 구성할 때, 각 심볼 테이블 엔트리에 해당 심볼이 가상 주소 공간의 어떤 섹션에 할당될 것인지 표기해야 한다. (심볼이 할당된 섹션)
예를 들어, 함수들은 .text 섹션으로 표기, 0 이 아닌 값으로 초기화가 되는 전역변수들은 .data 섹션으로 표기

Weak 심볼?
- 어셈블러는 심볼 테이블을 만드는 시점에 해당 Weak 심볼이 나중에 링커에 의해 선택될지 미리 알 수 없다.
- 링커에 의해 선택된다는 것이 보장된다면 .bss 섹션으로 표기해도 되지만, 선택되지 않을 수도 있기 때문에 함부로 .bss 섹션을 표기할 수 없다.

따라서 어셈블러와 링커는 다음과 같은 약속을 하게 된다.
어셈블러는 Weak 심볼에 해당하는 심볼 테이블 엔트리에 COMMON 섹션으로 표기하고, 나중에 링커는 COMMON 섹션으로 표기되어 있는 동일한 이름의 심볼들을 따로 모아서 전역 심볼 중복 문제를 처리하도록 한다.
결국 어셈블러는 섹션 정보를 빌려서 링커에게 Weak 심볼의 존재를 암묵적으로 알리게 된다.

이는 전부 전역 심볼에만 해당하는 내용이라는 것이다/
지역 심볼에 해당하는 static 함수, static 지역/전역 변수들은 scope 가 해당 모듈 내로 한정되며 각기 고유한 이름을 가지고 있다는 것이 보장되기 때문에 COMMON 섹션으로 표기할 필요가 없이 바로 .data 또는 .bss 섹션으로 표기해도 된다.
COMMON 섹션은 폐기될 수도 있는 심볼(Weak 심볼)들을 처리하기 위한 수단일 뿐이다.
- 지역 심볼들은 폐기될 일이 없다.

위와 같이 COMMON 섹션으로 표기된 전역 심볼들의 중복 문제를 처리하고 나면, 최종적으로 선택된 심볼 정의들의 총 사이즈가 실행 파일의 .bss 섹션에 저장될 값에 더해지고, 실행 파일에는 더 이상 COMMON 섹션이 존재하지 않게 된다.
(단, 동적 라이브러리의 코드/데이터에 대한 심볼 참조가 있는 경우에는 여전히 COMMON 심볼이 남아있을 수도 있다.)
- 선택된 심볼 정의? Strong or Weak

참고:
- 실행 파일의 .bss 섹션에는 데이터들 자체가 아니라 그 데이터들의 총 사이즈가 저장된다.

링크 결과 실행 파일의 .bss 섹션에 저장될 값 = 기존 .bss 심볼 정의들의 총 사이즈 + 선택된 심볼 정의들의 총 사이즈
- 기존 .bss 심볼 정의들의 총 사이즈? 0 으로 초기화 or 초기화되지 않은 static 변수들의 총 사이즈

심볼 해석 전체 과정
1. 커맨드 라인에 입력되는 순서대로 재배치 가능 오브젝트 파일들과 아카이브 파일(라이브러리)들을 하나씩 스캔한다.

링커는 스캔 과정에서 다음과 같은 세 개의 집합을 내부적으로 관리한다.

링커는 하나의 파일을 스캔할 때마다 다음과 같은 동작을 수행한다.
읽은 파일이 재배치 가능 오브젝트 파일인지, 아니면 아카이브 파일인지 판단한다.
그리고 그 판단 결과에 따라 다음 그림과 같은 동작을 수행하는 것을 반복하면서 모든 심볼 참조들을 정확히 하나의 심볼 정의에 연결하는 것을 시도한다.
만약 커맨드 라인 입력 순서대로 모든 파일을 스캔했음에도 해석되지 않은 심볼 참조가 있따면 링커는 에러 메시지와 함께 즉시 종료한다.
그렇지 않고 모든 심볼 참조를 성공적으로 하나의 심볼 정의에 연결했다면 이제 E의 모듈들을 대상으로 재배치 (Relocation)를 진행한다.

 링커의 관점에서 심볼 정의(Symbol Definition)는 .symtab 섹션의 심볼 테이블에 존재하는 심볼 테이블 엔트리를 가리키며, 심볼 참조(Symbol Resolution)는 .rel.data 섹션과 .rel.text 섹션에 존재하는 재배치 엔트리(Relocation Entry)를 가리킨다.

심볼 참조와 재배치 엔트리는 서로 연관된 개념이다.
- 심볼 참조 = 심볼 정의 재배치 과정 = 재배치 엔트리 기반으로 수행
- 재배치 엔트리 = 재배치 되어야 하는 심볼 참조에 대한 정보 저장
재배치 엔트리는 해당 심볼 참조가 어떤 심볼 정의를 가리키는지를 나타내는 symbol 필드를 가지고 있다.

지역 심볼? 해당 심볼 정의에 바로 연결.
전역 심볼? section 필드 확인
- UNDEF X —> goekd tlaqhf wjddmldp qkfh dusruf
- UNDEF O —> 다른 모듈의 심볼 테이블 확인하여 올바른 심볼 테이블 엔트리를 찾아 연결


주의해야 할 점이 바로 커맨드 라인의 입력 순서이다. 
심볼 정의가 포함된 정적 라이브러리가 파일을 심볼 참조가 포함된 재배치 가능 오브젝트 파일보다 앞에 위치시키면 해당 심볼 참조를 해석하는데 실패한다. 
따라서 정적 라이브러리 파일들은 맨 뒤에 두는 것을 원칙으로 한다.

# 재배치 Relocation
심볼 해석이 완료되면, 각 심볼 참조는 정확히 하나의 심볼 정의(심볼 테이블 엔트리)에 연결되어 있다.

재배치는 다음과 같이 두 단계로 진행
1. 섹션들과 그 안의 심볼 정의들을 재배치한다.
- 같은 유형의 섹션들은 한 섹션으로 합쳐서 실행 파일에 담고, 그렇게 ㅅ탄생하는 새로운 섹션들에 런타임 절대 가상 주소를 할당한다.
- 그리고 이에 맞춰 각 섹션 안에 존재하는 심볼 정의들에도 알맞은 가상 주소를 부여한다.
- 이 단계가 끝나면 모든 함수, 전역 변수, 그리고 static 변수들의 고유한 런타임 가상 주소를 알 게된다.

2. 심볼 참조들을 재배치한다.
- 앞서 심볼 정의들을 재배치 했기 때문에 해당 심볼 정의들에게 부여한 가상 주소 정보들을 활용하여, 각 섹션 안에 존재하는 심볼 참조들이 올바른 가상 주소를 가리키도록 수정해준다.
- 심볼 참조 재배치 과정에서 필요한 정보는 재배치 엔트리들에 담겨있다.
- 왜? 재배치 엔트리? 심볼 참조에 대한 정보?

재배치 엔트리 (Relocation Entry)
- 재배치 되어야 하는 심볼 참조에 대한 정보 저장 + 재배치 타입
어셈블러는 참조가 가리키는 심볼 정의가 무엇인지 모르거나, 가리키는 심볼 정의의 최종적인 가상 주소를 확정할 수 없는 심볼 참조를 마주칠 때마다 재배치 엔트리를 만들어서 재배치 가능 오브젝트 파일에 담는다.
여기에는 나중에 링커가 해당 심볼 참조를 어떻게 수정(재배치)해줘야 하는지에 대한 정보들이 담긴다.


offset: 해당 심볼 참조의 섹션 내 오프셋
type: 해당 심볼 참조를 어떻게 재배치해야 하는지에 대한 정보
symbol: 해당 심볼 참조가 가리켜야 하는 심볼 정의
addend: 특정 재배치 타입에 한하여 심볼 참조를 재배치할 때 사용해야 하는 부호 있는 상수 값

재배치 타입?
1. 32 비트 PC-relative 주소 방식
- [심볼 정의의 가상 주소] + [재배치 엔트리의 addend 필드 값] - [심볼 참조의 가상 주소]

2. 32 비트 절대 주소 방식
- [심볼 정의의 가상 주소] + [재배치 엔트리의 addend 필드 값]


### Executable Object Files
- 메모리에 로드되어 실행되기 위한 정보들을 담은 하나의 바이너리 파일이다.

ELF Header: 해당 오브젝트 파일의 전반적인 포멧 정보 저장, 프로그램 실행 시 실행해야 하는 첫 번째 명령어의 주소인 Entry Point 도 이곳에 저장된다.

.text, .rodata, .data 섹션은 재배치 가능 오브젝트 파일과 거의 유사하다. 다만 이러한 섹션들이 링커에 의해 최종적인 런타임 가상 주소로 재배치가 이뤄졌다는 것만 다르다.

.init 섹션은 _init 이라는 이름의 작은 함수를 정의하는데, 이는 프로그램의 초기화 코드에 의해 호출되는 함수이다.

한편 실행 파일은 Fully Linked, 즉 이미 재배치가 수행된 완전한 실행 파일이기 때문에 .rel.text 섹션과 .rel.data 섹션은 존재하지 않는다.

ELF 실행 파일은 메모리에 로드되기 쉽도록 디자인 된다.
즉, 실행 파일 내의 연속적인 바이트 청크/섹션들이 연속적인 “메모리 세그먼트”에 맵핑이 되도록 하는 것이다.
이런 맵핑 정보는 프로그램 헤더 테이블(세그먼트 헤더 테이블)에 저장된다.


코드 세그먼트
- read only 세그먼트, 읽기 및 실행 권 부여
- elf header, segment header table, init, text. rodata 까지의 섹션이 해당 세그먼트

데이터 세그먼트
- read/write 세그먼트, 읽기 및 쓰기 권한
- data, bss 섹션이 해당 데이터 새그먼트
- 참고: bss ? 런타임 시에 모두 0으로 초기화됨.

로딩
- “로더” 라고 불리는 os 코드 호출

로더
- 로딩: 디스크에 있는 실행 파일로부터 프로그램의 코드와 데이터를 메모리에 복사하고, Entry Point 에 해당하는 첫 번째 명령어의 주소로 점프함으로써 해당 프로그램을 실행한다.
- cpu 제어를 entry point 명령어로 넘긴다.

로더는 실행되면 위 그림과 유사한 메모리 이미지를 만들어 낸다.
그리고 실행 파일의 프로그램 헤더 테이블에 적힌 정보를 바탕으로 실행 파일의 연속적인 바이트 청크들을 코드 세그먼트와 데이터 세그먼트에 복사한다. 
다음으로, 로더는 _start 함수(시스템 오브젝트 파일인 crt1.o에서 정의됨)의 시작 주소에 해당하는 Entry Point로 점프함으로써 해당 프로그램의 실행을 개시한다.
그리고 _start 함수는 system startup function인 __libc_start_main 함수를 호출한다.
 이는 실행 환경을 초기화하고, 유저 프로그램의 main 함수를 호출하며, 그것의 반환 값을 처리하고, 필요한 경우에는 제어를 커널로 옮기는 역할을 수행한다.

————————————————————————————————————————

예외적인 제어 흐름 (Exceptional Control Flow, ECF)
- 실행하는 명령어에 따라 PC의 값이 변해가는 흐름을 제어 흐름(Control Transfer)라고 한다.

제어 흐름의 양상
1. 메모리에 연속적으로 할당되어있는 명령어들을 순차적으로 실행
2. 프로그램 변수로 표현되는 상태의 변화에 반응하여 제어 흐름이 바뀌는 경우
- jump, call, return
3. 예외적인 제어 흐름
- 시스템 상태의 변화에 반응하여 제어흐름이 “갑자기” 바뀌는 경우이다.
- uplanned event

ECF는 컴퓨터 시스템의 모든 수준에서 나타난다.
- 하드웨어, 운영체제, 응용 프로그램 수준에서 나타날 수 있다.
1. 하드웨어
- ex) 외부 입출력
2. 운영 체제
- 커널은 문맥 전환(context switch)을 통해 한 프로세서가 가지고 있던 제어를 또 다른 프로세서에게 넘겨줄 수 있다.
3. 응용 프로그램: 
- 시스템 콜(트랩)을 통해 운영체제에게 특정 서비스를 요청할 수 있으며, 한 프로세스는 다른 프로세스에게 시그널(Signal)을 전송하여 제어가 수신자 측의 시그널 핸들러로 넘어가도록 한다.
- 또한, 개별 프로그램은 일반적인 호출/리턴 스택 규칙을 깨고 다름 함수 내 임의의 주소로 비지역 점프(nonlocal jump)를 수행함으로써 특정 예외 상황에 반응할 수도 있다.

ECF (예외적인 제외 흐름)
- 운영체제가 외부 입출력, 프로세스, 가상 메모리를 구현하기 위한 기본적인 매커니즘이다.
- 응용 프로그램은 ECF의 한 종류인 시스템 콜(트랩)을 이용하여 운영체제에게 특정 서비스를 요청한다. 예를 들어, 시스템 콜을 통해 운영체제에게 디스크에 데이터를 쓰거나, 네트워크로부터 데이터를 읽거나, 새로운 프로세스를 만들거나, 현재 프로세스를 종료시키기 위한 서비스를 요청할 수 있다.

동시성
- 컴퓨터 시스템의 동시성은 ECF 를 기반으로 구현된다.
- 동시성의 대표적인 예시로는 응용 프로개름의 실행을 간섭하는 핸들러나 시그널 핸들러, 그리고 동시에 실행되는 프로세스나 스레드 등이 있다.

소프트웨어 수준의 예외가 동작하는 원리
- C++ 이나 자바와 같은 언어들은 소프트웨어 수준에서 예외를 처리하기 위한 메커니즘 (try, catch, throw 등)을 제공한다.
- 이러한 소프트웨어 수준의 예외는 프로그램으로 하여금 비지역 점프(nonlocal jump)를 수행하도록 함으로써 구현된다.
- 비지역 점프는 응용 프로그램 수준의 ECF 에 해당한다.
- 예외가 발생하면 예외 처리 핸들러가? catch 명령어로 점프하도록 한다.

Exception (예외)
- 예상치 못한 이벤트
- 제어 흐름의 갑작스러운 변화
- 하드웨어 + 운영체제의 협력에 의해 구현되는 낮은 수준의 ECF

프로세스의 상태 변화: 이벤트
- 이벤트는 현재 명령어의 실행과 유관할 수도 있고 무관할 수도 있다.
- 현재 명령어에 의해서 발생하는 이벤트일 수도 있고, 타이머 장치나 혹은 외부 입출력 작업에 의한 이벤트일 수도 있다.


프로세서는 특정 예외 이벤트의 발생을 감지하는 순간, 예외 테이블 (Exception Table)이라고 불리는 점프 테이블을 참조하여 해당되는 예외 핸들러 (Exception Handler)로의 간접 프로시저 호출을 수행한다.
- 그냥 예외 핸들러를 호출한다.
이렇게 호출된 예외 핸들러가 해당 루틴 처리를 마치면 다음 세가지 동작 중 하나를 수행한다.
1. I_curr 로 리턴 (즉, 예외가 발생했던 명령어로 리턴)
2. I_next 로 리턴 (예외를 발생시킨 명령어 이후의 명령어로 리턴)
3. abort 루틴: 해당 프로그램 종료

예외 처리 (Exception Handling)
- 한 시스템 내에서 발생할 수 있는 모든 예외는 자신만의 예외 번호(Exception Number? offset?)를 가진다.
- 예외 번호는 음이 아닌 정수로서, 모든 예외는 고유한 예외 번호를 가진다는 것이 보장된다.
- 어떤 예외 번호는 프로세서를 설계하는 사람들에 의해 부여되고, 또 어떤 예외 번호는 커널을 설계하는 사람들에 의해 부여된다.
- 전자에 해당하는 예외로는 divide by zero, page fault 등이 있고, 후자에 해당하는 예외로는 시스템콜, 외부 입출력 장치에 의한 인터럽트 등이 있다.

컴퓨터가 켜지면, OS는 예외 테이블을 메모리에 할당 및 초기화 한다.
- 각 예외에 해당하는 예외 핸들러의 주소가 매핑되어 있다.


프로세서는 런타임 때 특정 예외 이벤트를 감지하면 해당 이벤트의 예외 번호(offset)를 결정하고 해당 번호의 엔트리를 참조하여 해당되는 예외 핸들러를 호출하게 된다.

참고로 예외 테이블의 시작 주소는 예외 테이블 베이스 레지스터라고 불리는 특별한 종류의 CPU 레지스터에 저장이 되어있다.

일반적인 함수의 호출 vs 예외 핸들러 호출의 차이
- 예외 핸들러 기준
1. 스택에 push하는 리턴 주소가 현재 명령어의 주소일 수도 있고, 다음 명령어의 주소일 수도 있다.
- 일반적인 프로시저는 다음 명령어(pc + 4)가 push된다.

2. 복귀 주소뿐만 아니라 다른 추가적인 프로세서 상태 정보도 스택에 push한다.
- 이는 예외 핸들러가 리턴할 때 모든 프로세서 상태 정보를 원래대로 되돌려 놓기 위함이다.
- 프로세서 상태 정보? 컨텍스트, 레지스터? 
- 일반적인 프로시저의 경우 동일한 프로세서내에서 호출된다. 예외 핸들러는 조금더 폭넓은 정보를 저장한다.

3. 커널 모드
- 일반적인 프로시저 호출과 달리 예외 핸들러는 시스템 자원들에 대한 접근 권한을 갖는다.
- 데이터는 유저 스택이 아닌 “커널 스택”에 쌓이게 된다.

처리를 끝낸 예외 핸들러는 예외 종류에 따라 원래 프로그램의 실행 흐름(I_curr, I_next)으로 돌아가거나 abort 루틴으로 리턴하여 해당 프로그램을 종료시킨다.
- 원래 프로그램의 실행 흐름으로 돌아가기: “return from Interrupt” 라는 명령어를 사용한다
- 이 명령어는 스택에 푸쉬되어 있는 복귀 주소와 각종 프로세서 상태 정보를 pop 하여 원래대로 되돌려 놓고, 현재 프로세서의 상태를 유저 모드로 바꿔주는 역할을 한다.

예외 종류 (Exception Class)

1. 동기적 예외 (Exception)
- 명령어에 의한 예외, 명령어를 실행할 때 발생하는 예외

a) Trap, System call
- 특정 명령어를 실행하여 의도적으로 발생시키는 예외. (명령어에 의한 예외이므로 동기적 예외, Exception)
- 트랩에 해당하는 예외 핸들러는 트랩 핸들러라고 부르며, 트랩 핸들러의 처리가 끝나면 인터럽트 핸들러와 마찬가지로 다음 명령어로 리턴한다.
- OS(커널)를 호출하여 커널의 서비스를 요청한다.
- 커널이 제공하는 서비스? 파일 읽기(read), 프로세스 생성(fork), 로드(execve), 프로세스 종료(exit) 등이 있다.
- 프로세서는 유저 프로그램이 시스템 콜을 통해 이러한 서비스들을 요청할 수 있도록 syscall n 명령어를 제공한다.
- 이 명령어를 실행하여 호출되는 예외 핸들러(트랩 핸들러)는 레지스터로 전달되는 인자들의 값을 적절히 해석한 뒤, 요청된 커널 루틴을 호출하게 된다.
- 여기서 인자로 전달되는 시스템 콜의 번호(n)는 요청하려는 시스템 콜의 고유 번호이다.
- 이는 커널에 존재하는 시스템 콜 테이블에서 요청된 커널 루틴들의 주소를 저장하는 엔트리의 인덱스에 해당한다.

- 시스템 콜 테이블과 예외 테이블은 다른 것이므로 혼동하지 말자!

b) fault
- 회복 가능성이 있는 예외
- 에러를 고치는 것에 성공하면 현재 명령어(I_curr, Faulting 명령어)로 리턴하고 에러를 고칠 수 없으면 커널에 존재하는 abort 루틴으로 리턴하여 해당 프로그램을 종료시킨다.
- 대표적인 예: 페이지 폴트(Page Fault)
- 명령어가 메인 메모리에 존재하지 않는 가상 페이지에 접근하려 시도하면 예외가 발생하여 페이지 폴트 핸들러가 호출된다.
- 핸들러는 디스크에 위치해 있는 요청된 가상 페이지를 메인 메모리에 로드하게 되고, 로드 작업이 완료되면 Faulting 명령어로 복귀한다.
- 그러면 접근하고자 하는 가상 페이지가 메인 메모리에 존재하므로 예외가 발생하지 않고, 아무 일도 없었던 것처럼 정상적으로 프로그램 실행이 재개된다.

c) abort
- 회복 가능성이 없는 예외, 회복 불가능한 예외
- abort 루틴: 프로그램 종료
- ex) 치명적인 하드웨어 에러들에 의해 발생하는 예외

2. 비동기적 예외 (Interrupt)
- 명령어 실행에 의한 것이 아닌, 외부 입출력 장치들에 의한 예외
- 프로세서 외부의 입출력 장치들로부터 전달받는 신호에 의해 발생하는 예외로, 명령어의 실행 결과로 발생하는 예외가 아니기 때문에 비동기적 예외이다.
- 인터럽트에 해당하는 예외 핸들러인 인터럽트 핸들러는 처리가 끝나면 다음 명령여(I_next)로 리턴한다.
- 외부 입출력 장치가 인터럽트를 발생시키는 방법은 프로세서의 인터럽트 핀에 신호를 전달하고 시스템 버스에 예외 번호를 실어 보내는 것이다.
- 그러면 프로세서는 현재 명령어의 실행이 끝난 직후 인터럽트 핀을 보고 인터럽트 발생을 감지할 수 있다. 이후 프로세서는 시스템 버스에서 읽어 들이는 예외 번호를 사용하여 적절한 인터럽트 핸들러를 호출하게 된다.

예외 번호
0 ~ 31: 프로세서 설계자가 정의한 예외 번호
32 ~ 255: 리눅스 커널 설계자가 정의. 인터럽트 및 트랩 예외에 해당한다.

시스템 콜의 대표적인 사례
- 참고로 시스템 콜 테이블은 예외 테이블과 다르다
- 트랩이 발생하면 트랩 핸들러가 호출되고 이 트랩 핸들러에서 시스템 콜 테이블을 참조한다.


C 프로그램은 syscall 함수를 직접 실행하여 시스템 콜을 수행할 수 있다.
그러나 보통 C 표준 라이브러리가 제공하는 wrapper 함수들을 사용하여 시스템 콜을 수행하게 된다.
wrapper 함수들은 전달되는 인자들을 적절히 해석하고, 알맞은 시스템 콜 명령어를 실행하도록 하며, 시스템 콜의 수행 상태 정보를 호출부에게 반환 값으로 전달해준다.
참고로, 이와 같은 시스템 콜 및 그것의 Wrapper 함수들을 통틀어서 시스템 수준 함수 (System-level function)라고 부른다.

# 프로세스(Process)
- 프로세스란 실행 중인 프로그램의 한 인스턴스를 의미하며, 각각의 프로세스는 특정 문맥에서 실행된다.

문맥(Context)이란?
- 프로그램이 실행되기 위해 필요한 “상태 정보”들의 집합
- “상태 정보”
- 메모리의 스택 및 프로그램 코드/데이터, 범용 레지스터, 프로그램 카운터, 환경 변수, 파일 descriptor 등이 이에 해당한다.
- ++ ex) JobExecutionContext ? 잡 실행에 필요한 상태 정보

프로세스라는 개념에 의해 각 응용프로그램에게 제공되는 핵심적인 두 가지 추상화
- 추상화?  어떤 인터페이스를 통해 추상화? 어떤 추상화를 제공? 어떤 착각을 제공?
1. 프로그램이 프로세서를 독차지하고 있는 듯한 착각을 제공하는 하나의 “독립적인 논리적 제어 흐름(independent logical control flow)”
2. 프로그램이 메모리를 독차지하고 있는 듯한 착각을 제공하는 하나의 “사적인 주소 공간(private address space)”

논리적 제어 흐름
- 프로세스는 각 프로그램에게 자신이 프로세서를 독차지 하고 있다는 착각을 제공한다.
- 프로세서의 time sharing

각 프로세스가 프로세서를 돌아가면서 사용하고 있다.
다른 프로세스가 프로세서를 사용하고 있을 때 자신은 가만히 기다리는 것인데 이를 preemted/suspended 되었다고 표현
그러나 각 프로세스의 문맥에서 실행되는 프로그램의 입장에서는 자신이 프로세서를 독차지하고 있다는 착각을 하게 된다.
왜?
자신의 메모리 정보나 레지스터의 값들이 전혀 변하지 않은 채로 실행이 재기되기 때문

동시적 흐름 (Concurrent Flow)
- 또다른 논리적 흐름과 실행이 시간적으로 겹치는 논리적 흐름을 말한다.
- concurrently 하게 실행된다.
- 실제로는 동시에 실행되지 않아도 논리적 흐름이 시간적으로 겹치면 그것은 동시적 흐름이다.

여러 개의 논리적 흐름이 동시적으로 실행되는 현상을 동시성이라고 부르며, 각 프로세스가 프로세서를 돌아가면서 사용하는 현상을 멀티태스킹(multitask)이라고 부른다.
한편 각 프로세스가 자신의 논리적 흐름 내에서 실제로 프로세스가 사용하고 있는 각각의 시간을 타임 슬라이스라고 부르기 때문에, 멀티태스킹은 타임 슬라이싱이라고 부르기도 한다.

참고로 동시적 흐름의 개념은 CPU 코어 개수와 무관하다.
코어가 한 개인 CPU에서도 두 개 이상의 “논리적 흐름이 겹치기”만 하면 동시적 흐름이 나타날 수 있는 것
만약 코어가 여러 개인 CPU에서 서로 다른 코어의 논리적 흐름이 겹친다면, 이는 병렬적 흐름(parallel flow)라고 한다.
- 병렬적 흐름은 동시적 흐름의 부분 집합이며, “실제로 동시에 실행”되는 흐름이다.

사적 주소 공간 (Private Address Space)
- 프로세스는 각 프로그램에게 사적 주소 공간(private address space)를 제공함으로써 그 프로그램이 메모리를 독차지 하고 있는 듯한 착각을 만들어 낸다.

private
- 해당 공간의 특정 주소에 해당하는 메모리 바이트를 다른 프로세서가 읽거나 쓸 수 없다.

각각의 private address space는 내용이 다르지만, 구조는 모두 동일하다.


유저/커널 모드
- cpu 특정 컨트롤러 레지스터의 모드 비트(mode bit)는 현재 프로세스의 권한/특권(privilege) 유무를 나타낸다.
- 모드 비트가 세팅되어 있으면 커널 모드 또는 슈퍼바이저 모드이며, 모드 비트가 세팅되어있지 않으면 유저 모드이다. 이러한 모드는 실행 가능한 명령어의 범위와 접근 가능한 메모리의 범위를 결정

커널 모드의 프로세스는 권한을 가지고 있기 때문에 어떤 명령어든 실행할 수 있고, 시스템 내 모든 메모리 주소 공간에 접근할 수 있다.
반면 유저 모드의 프로세스는 권한이 없기 때문에 제약이 있다.
1. 유저 모드의 프로세스는 권한이 필요한 몇몇 명령어들을 실행할 수 없다.
- 실행하려고 하면 Fatal Protection Fault 예외가 밠생
2. 유저 모드의 프로세스는 주소 공간 중 커널 영역의 데이터/코드 영역에 직접 접근할 수 없다.
- 대신에 시스템 콜 인터페이스를 통해 간접적으로만 커널 영역의 데이터/코드에 접근할 수 있게된다.

최초 응용 프로그램이 실행될 때 생성되는 프로세스는 유저 모드이다.
프로셋가 유저 모드에서 커널 모드로 바뀌는 경우는 인터럽트 ,폴트, 시스템 콜 등의 “예외”가 발생할 때이다.
예외가 발생하면 제어가 예외 핸들러로 넘어가면서 프로세서에 의해 모드가 커널 모드로 바뀌고, 응용 프로글매의 코드로 돌아갈 때 프로세서에 의해 모드가 다시 유저모드로 바뀌게 된다

문맥 전환 (Context Switch)
- 문맥 전환은 멀티태스킹(프로세스가 프로세서를 번갈아가며 사용) 을 구현하는 기본적인 매커니즘으로, 운영체제 커널에 의해 수행이 되는 높은 수준의 ECF(얘외적인 제어 흐름)에 해당한다.
- 문맥 전환 매커니즘은 앞에서의 낮은 수준의 ECF에 해당하는 예외 매커니즘을 기반으로 구현이 되었다.

문맥 (Context)
- 프로세스를 실행하는데에 있어서 필요한 상태 정보
- 범용 레지스터, 유저 스택, 커널 스택, 프로그램 카운터, 상태 레지스터, 기타 커널 자료 구조 (ex. 페이지 테이블, 프로세스 테이블, 파일 테이블, 시스템 콜 테이블)등의 정보들이 해당한다.

문맥 전환
- 스케쥴러 루틴 호출
- 스케쥴링: ready queue에 있는 프로세스들 중에서 다음에 실행할 프로세스 선택
- 스케쥴링/선택을 했으면 현재 프로세스에서 새로운 프로세스로의 문맥 전환을 수행한다.
- 문맥 전환은 현재 프로세스의 문맥을 저장하고, 새로 실행할 프로세스의 문맥을 복원(restore)하며, 제어를 해당 프로세스로 넘겨준다.

문맥 전환은 언제?
1. 커널이 시스템 콜을 수행하고 있을 때
- 어떤 시스템 콜이 특정 이벤트의 발생을 기다린다면? 이는 스케쥴러를 호출하여 다른 프로세스에게 제어를 넘겨주도록 한다.
2. 인터럽트의 결과
- 타이머 인터럽트에 의해 현재 프로세스가 너무 오래 실행되었다고 판단하고 새로운 프로세스로의 문맥 전환을 수행

다음 그림은 프로세스 A와 프로세스 B 사이의 문맥 전환 예시를 보여준다. 유저 모드로 실행되고 있던 프로세스 A는 read 시스템 콜을 통해 커널의 트랩 핸들러를 호출한다. 그러면 해당 트랩 핸들러는 디스크 컨트롤러에게 DMA Transfer를 요청하고, 디스크 컨트롤러의 메모리 로드 작업이 끝나면 프로세서에게 인터럽트를 걸 수 있도록 준비시킨다. 그런데 디스크 읽기 작업은 상당히 많은 시간을 소요하기 때문에, 트랩 핸들러는 가만히 기다리지 않고 스케쥴러를 호출하여 프로세스 B로의 문맥 전환을 수행한다. 그렇게 프로세스 B가 실행되다가 디스크 읽기 작업이 완료되어 인터럽트가 발생하면 다시 스케쥴러를 호출하여 프로세스 A로의 문맥 전환을 수행한다.