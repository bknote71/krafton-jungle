# 가상 메모리 (Virtual Memory)

## summary

VM mechanisms
- Physical and virtual addressing
- Dyanmic Relocation: partioning, segmentation, paging
- Page table management: Single vs Multi, demand paging
- TLBs: Cache to Page Table, fast translation

VM policies
- Page replacement policy: FIFO, LRU, Approximation
- Page allocation policy: Local vs Global

Vm optimizations
- Demand paging, copy-on-write (space)
- Multi-level page tables (space)
- Efficient translation using TLBs(time)
- Page replacement policy (time)


Virtual Memory: Goal

Transparency
- 각각의 프로세스에게 혹은 프로그래머에게 large, contiguous memory space 를 사용하는듯한 착각/추상화를 제공한다. 
- 메모리에 대한 추상화 제공 (크고 연속적인 메모리, 동일한 메모리 구조)

Efficiency
- fragmentation 을 최소화 한다. 
- “Locality” 를 잘 활용한 캐시의 역할을 한다. (메인 메모리를 디스크의 캐시로 사용)

Protection
- 한 프로세스가 다른 프로세스의 주소 공간에 접근하는 것을 쉽게 막을 수 있다.
- 각 Page Table Entry 에는 가상 주소에 대한 “접근 권한”이 명시된다. 
- 프로세스간에 메모리 공유가 가능해졌다.

CPU 에서의 메모리 접근
- Instruction: fetch 
- Data: lw, sw

모두 “가상 메모리 주소”에 대해서 접근한다.

가상 주소 공간? 
- 프로세스마다 가지고 있는 private, virtual address space
- 메모리에 대한 추상화를 제공함

Virtual Memory

Each process has its own virtual address space.
- large and contiguous: 무한한 공간
- private: 각 주소 공간은 해당 프로세스에게서만 유효하다. (물론 공유도 가능)
- 추상화 제공

Address translation
- Virtual address(VA) —> Physical address(PA)
- 런타임에 실행

Lazy Allocation
- 물리 메모리는 동적으로 할당되거나 해제될 수 있다. (on demand)
- Programs execute without requiring their entire address space to be resident in physical memory
- 기존에는 프로그램 실행 시 필요로하는 코드, 데이터 영역 모두를 메모리에 올려놓고 실행했어야 했다.
- 하지만 가상 메모리의 지원으로 인해 필요로 하는 부분만 (on demand)  그때 그때, 동적으로(dynamically) 메모리에 올려놓을 수 있게 된다.

Allocation(Relocation)

1. Static Relocation
- 정적 배치: 한 번 메모리에 배치되면 움직일 수 없다.
- software-based relocation 
- Os rewrites each program before loading it in memory
- rewrite address of static data and functions

장단점?

장점
- 하드웨어 지원이 없어도 된다. (OS 만 필요)

단점

Protection X
- 하나의 프로세스가 OS나 다른 프로세스의 메모리 영역을 침범할 수 있다.
- No Privacy: 메모리 어느 영역이나 접근할 수 있게 된다.

한 번 배치되면 이동이 불가능하다.
- external fragmentation 
- 필요로 할 때 storage로 내려갔다가, 다시 올라올 때 다른 메모리 주소로 올라오는 Dynamic 할당이 안된다.

External fragmentation
- 전체적으로 살펴보면 여유 공간이 있으나, 특정 메모리 공간을 할당한 공간은 없는 상황

- 전체적으로는 56 K 의 여유 공간이 존재하지만 만약  48 K 메모리 공간을 할당하려 해도 할당하지 못한다.
- 메모리 영역을 동적으로 움직일 수 있어야 한다.

Dynamic Relocation

Hardware-based relocation
- MMU (Memory Management Unit) performs address translation on every memory reference instructions
- if the virtual address is invalid, the MMU raises an exception
- OS passes the information about the valid address space of the current process to the MMU
- Valid Address Space를 Context Switch 이 일어날 때마다 하드웨어에게 알려줘야 한다.

Dynamic Relocation Implementation
1. Fixed or Variable Partitions
2. Segmentations
3. Paging

1. Fixed Partitions
physical memory is broken up into fixed partitions
- size of each partition is the same and fixed

H/W 요구사항: base register
- 파티션의 시작 위치/주소
- 물리 메모리 위치 = Virtual address + Base register
- 컨텍스트 스위치마다 base register 를 save 및 restore 해야한다.

장점
- 구현하기 쉽다.
- 컨텍스트 스위치가 다른 Dynamic Relocation에 비해 상대적으로 빠르다. (base register 만 저장 및 복원하면 된다.)

단점
- Internal fragmentation: unused area in a partition is wated
- Partition size: 모든 메모리 영역의 요구사항에 적합하지 않는다.

external fragmentation
- 전체적인 공간은 있지만 사용할 수 없는 상황

internal fragmentation
- 공간은 있지만 사용하지 않아서 “낭비되는” 상황

Improvement
- “미리 정해진” 다양한 파티션 SIZE/크기

할당 전략 (Allocation strategies)
- 프로세스의 가상 주소가 어느 파티션에 위치/할당할 수 있는지를 결정한다.
- a) A seperate queue for each partition size
- b) A single queue + first fit (처음 크기가 맞는 파티션)
- c) single queue + best fit (남는 idle을 가장 적게하는 파티션)
- 시간 낭비 vs 공간 효율

2. Variable Partition
physical memory is broken up into variable-sized partitions
- 미리 정해지지 않고, 프로세스의 메모리 요구사항에 맞추어 파티션을 구성한다.

H/W 요구사항: base register + limit register
- limit register: protection

장점
- No internal fragmentation
- 왜? 프로세스가 필요로 하는 만큼 메모리 공간을 할당한다.

단점
- 각각의 프로세스는 물리 메모리에 “연속적으로(contiguously)” 할당되어야 한다.
- External fragmentation
- No Partial Sharing: cannot share parts of address space

3. Segmentation
주소 공간을 “logical segements”로 나눈다.
- segment? logical entity in address space (특정 섹션)
- Code, Data, Stack, Heap, etc.

Logical 한 Entity/세그먼트/섹션으로 나눠서 엔티티끼리는 연속적이지 않아도 서로 다른 공간에 할당할 수 있도록 한다.

각각의 Segment 는 독립적이다.
- 물리 메모리에 세그먼트 별로 독립적으로 할당될 수 있다.
- Grow and Shrink (Stack, Heap)
- Be Protected (separate read/write/execution protection bits, using segements table)

- Variable Partitions를 프로세스 당 하나의 세그먼트가 존재한다.
- Segmentation: 프로세스 당 여러개의 세그먼트가 존재한다.

Segment registers or table (per Process)
- 세그먼트 별로 Base Register, Limit Register, Direction bit, Protection bit, Valid bit, … 등의 엔트리 정보들을 가지고 있는 테이블을 필요로 한다.

장점
세그멘트 별로 독립적인 할당이 가능하다.
스택, 힙은 독립적으로 grow, shrink 가 가능하다

protection 하기 쉽다. 
- valid bit
- different protection bits for different segments
- read/write/execution bit

segement 를 공유하기 쉽다.
- 같은 주소로 translation 을 하면 된다.
- Code/Data sharing at segment level

Dynamic relocation of each segment !!!

단점
세그먼트 자체는 연속적으로 할당되어야 한다.
- External fragmentation: 만약 Large Segements 에 대해서 물리 메모리가 충분하지 않다면??

Lage Segment table
- keep in main memory
- use hardware cache for speed

Summary

Virtual Memory
- 메인 메모리에 대한 Abstraction 제공 (large, uniform array of bytes(구조가 동일))
- 물리 메모리의 위치는 “투명하게” 동적으로 움직일 수 있다.

가상 메모리는 실제 메모리보다 훨씬 클 수 있다.
그럼에도 프로세스를 실행할 수 있다. 그것도 여러개
어떻게?
- 메인 메모리에 프로세스 전체의 가상 주소 영역을 올려놓지 않아도 된다.
- Physical memory is allocated on demand
- Views the physical memory as a cache for the disk

Easy to protect and share memory regions among processes

Paging

Segmentation의 단점?
- 세그멘테이션 자체는 “연속적”이어야 한다.
- 만약 큰 세그멘테이션에 대해서 물리 메모리가 충분하지 않다면 해당 세그먼트를 메모리에 로드할 수 없다.
- external fragmentation

Segmentation 방식의 단점인 external fragmentation 문제를 해결하는 좀 더 flexible 한 Dynamic Relocation 방식은 없을까?
- 그게 바로 Paging이다!

Paging
Allows the physical address space of a process to be noncontiguous
- Divide virtual memory into blocks of same size (Pages)
- Divide physical memory into fixed-size blocks (Frames, Physical Pages)
- Page (or frame) size is power of 2 (4KB 가 기본 페이지 단위)

메모리 관리 단순화
- OS 는 전체의 free 한 물리 페이지(Frame)을 추적(track)한다.
- n 개의 페이지를 할당하기 위해서는 n 개의 free 한 물리 페이지를 찾은 후 로드한다.
- “Page Table” to translate virtual to physical address (VA —> PA 변환)

참고: Page Tables
- 프로세스마다 존재한다.
- 물리 메모리에 존재
- OS가 생성/관리/업데이트
- 하나의 엔트리: Page Table Entry

왜 프로세스마다 필요할까?
- 프로세스마다 Private 한 가상 주소 공간이 존재하는데, 개별 프로세스의 주소 공간의 구분이 필요하다.
- “VA —> PA 매핑 정보” + “각각의 프로세스들을 구분”
- 즉 페이지 테이블은 프로세스마다 필요로 한다.


참고: Page Table Base Register (PTBR)
- 페이지 테이블의 시작주소
- Page Table 은 프로세스마다 필요로 한다.
- 그러면 PTBR 역시 프로세스마다 개별적으로 필요로 한다.
- 컨텍스트 스위칭 시에 해당 PTBR 을 save 및 restore 해야한다.

페이지 테이블 + 테이블 레지스터 들은 “OS”에 의해서 관리된다.

참고: malloc(128 B)
- OS가 빈 페이지 하나를 찾은 후 할당할 수 있도록 한다. (사실 디스크의 페이지 <<)
- 4KB 중에서 128 Bytes 만 사용자에게 사용할 수 있도록 할당/반환한다.
- 또 요구하면, 페이지 내에서 요구한 만큼 사용자에게 할당/반환하도록 한다.

VA의 페이지 할당: 대응하는 물리 페이지 매핑/연결
- in Page Table 에서 매핑 기록

Address Translation
Translating virtual address
- virtual address has two parts: <Virtual Page Number(VPN), Offset>
- VPN is index into the page table
- Page Table Entry 는 Page Frame Number(물리 페이지 번호, PPN)를 결정한다.
- Physial address is <PFN/PPN, Offset>
- Usually, |VPN| >= |PFN/PPN| . 왜? Virtual Address Memory가 실제 물리 메모리보다 훨씬 크다.

**Offset** (중요)
- 페이지내에서의 주소 위치
- 지금 접근하려는 주소가 페이지 내에서 몇 번째 떨어진 바이트에 있는지를 나타낸다.
- VA, PA 페이지 사이즈가 동일하다.
- 페이지 사이즈가 동일하기 때문에 Offset은 변하지 않는다 !!
따라서 VPN to PPN(PFN) 으로의 translation 이 필요하다.

Page Tables
- Managed by OS
- MAP VPN to PPN(PFN)
- “One Page Table Entry per page”

ex) 32비트 주소체계, 4KB Page Size
- 2^20 개의 페이지 엔트리 개수(PTEs)
- 2^20 개의 페이지 “인덱스”
- Offset 은 동일하다. (VA, PA 모두 offset은 동일)

Page-Level Access Control (Protection)
- 페이지 단위로 접근 제어/Protection 기능
- how? PTE 에 “권한 정보”를 저장해서 페이지 단위로 권한을 설정한다.
- 페이지 테이블에서 VA —> PA 변환 과정에서, 권한 정보 역시 체크가 가능하다.

Page Table/Page Table Entry에서의 2가지 Function
1. Address Translation (VPN —> PPN)
2. Access Control (Protection)
- 동시에 가능하다.

Page Table Entry (PTE)
| V | R | M | Prot | Page Frame Number(PFN, PPN) |

V (valid) bit: 해당 페이지를 사용할 수 있는지 여부
- VPN 에 대응하는 PPN 이 실제 물리 메모리에 존재하는지

R (reference) bit: 해당 페이지의 참조 여부
- 해당 페이지에 읽기/쓰기할 때 발생

M (modify) bit: 수정 여부
- dirty bit라고 한다.

Prot (Protection) bit
- control access
- which operations are allowed
- Read, Write, Execute, etc.

PFN(PPN) : Physical Frame Number, Physical Page Number

Demand Paging
- 해당 페이지를 필요로 할 때 디스크로부터 가져와서 물리 메모리에 매핑한다.

Virtual Page 매핑 
- 실제 물리 메모리에 존재
- 아니면 디스크에 존재한다.

만약 가상 페이지에 대응한 페이지가 메모리에 없고, 디스크에 있다면?
- “디스크”로부터 페이지를 가져와 메인 물리 메모리에 매핑시킨다!

Page Table 은 <Virtual Pages Number to Physical Pages Number>  매핑 정보를 저장하는 테이블이다.

프로세스의 “페이지 정보”는 미리 디스크에 스왑 공간이라는 공간에 생성해둔다.

Swap in/out
- 매번 프로그램 전체의 기능을 쓰는것은 아니다.
- 필요한 부분(페이지)만 메모리 영역에 올려놓기
- demand paging
- 필요없는 부분은 storage(disk)에

디스크에는 프로세스의 페이지에 대한 카피본이 존재한다.

궁굼
- 일단, 아직까지는 프로세스의 모든 페이지 영역을 디스크 영역에 생성한 후에 필요할 때 메모리에 할당한다고 생각하자.
- invalid: replacement/ swap in
- 근데 디스크 영역에 제한은 존재한다. 그럴 때는 어떻게하지?
- 즉, 동적 할당을 제외하고, 동적으로 페이지를 생성 및 해제할 수 있을까?

- 스왑 자체에 대해서 다시 공부하자

Physical Memory as a Cache
- 물리 메모리는 디스크에 대한 캐시이다.
- Fully-Associative cache
- - 처음 프로세스 시작 시 가상 주소 공간에서 필요한 페이지는 디스크의 스왑 공간에 생성한다.
- 필요에 따라(on-demand) 물리 메모리에 올려놓기도 하고(Cached), 공간이 꽉차면 디스크에 내려놓기도 한다.(Uncahced)
- 사용하지 않는 주소 공간 영역에 대한 페이지는 “Unallocated” 되어있다.
- 해당 페이지에 대해서 접근할 수는 없다. (Protection fault)

캐싱 이슈
1. Placment: 어느 부분을, 어떻게 메인 메모리에 배치할 것인가
2. Replacement: 어느 페이지를 메모리에서 제거할 것인가
3. Granularity of Management: large, small, uniform pages
4. Write Policy: writes 에 관한 정책? 메모리에 쓰기를 한 것에 대한 처리 정책. Write Back?

Virtual Memory 가 필요로 하는 것
- HW + SW

Page Table in Memory
- Translation Lookaside Buffers(TLBs): 테이블 페이지의 캐시

MMU (Memory Management Unit)
- includes Page Table Base Register, TLBs, page walkers (페이지 테이블 엔트리 탐색기)

MMU를 활용한 OS Jobs  
- page tables 생성, replace 대상 결정
- change the page table register on context switch (to use the running thread’s page table)
- Handle page faults and Ensure correct mapping

OS Job for Virtual Memory
1. free 한(가용한)  물리 페이지를 추적/관리(track)
2. free 한 물리 페이지를 가상 페이지에 할당/매핑
3. Page Replacement Policy (victim selection, evict)
- when no physical memory is free, 무엇을 Swap out 할 것인지?
4. Sharing pages between processes
- copy-on-write optimization

Page Fault: A Miss in Physical Memory
If a page is not in physical memory but disk
- page table entry indicates that the page not in memory (by Valid bit)
- Access to such a page triggers a Page Fault exception 
- OS exception handler is invoked to move data(page) from disk into memory

OS Exception Handler에 의해 페이지를 디스크에서 메모리에 배치하는 것은 “디스크 I/O” 과정이고 이는 매우 느리다.
- Miss Penalty 
- 메모리가 디스크에 대한 “캐시”(DRAM 캐시)라는 측면에서 봤을 때는 Cache Miss 가 발생한 것이다.
- 왜 느릴까? 디스크와 DRAM 의 속도 차이는 거의 10,000 배에 이른다고 한다.

Miss Penalty 처리 방식 (즉, 캐시 미스 처리 방식)
- 캐시 메모리(SRAM)의 경우 DRAM과 SRAM의 속도 차이가 그렇게 크지 않기 때문에(대략 10배) 하드웨어 수준에서만 처리해도 문제가 되지 않는다.
- 그러나 DRAM 캐시의 경우 디스크와 DRAM의 속도 차이가 매우 크기 때문에 하드웨어 수준에서만 처리하기에는 낭비되는 시간이 많다.
- 따라서 OS 의 Support 를 필요로 한다.
- 하드웨어가 DRAM 캐시의 Miss Penalty를 처리(Replace, Swap in/out)하는 동안 컨텍스트 스위칭을 통해 잠시 다른 프로세스에게 제어를 넘겨주는 것
- Page Fault Handler의 처리가 끝나면 인터럽트를 보내서 다시 제어를 가져오도록 한다.
- 이렇게 하면 미스 패널티를 처리하는 긴 시간을 기다리기만 하면서 다른 프로세스에게 잠시 제어를 넘겨준다.

Handling Page Faults
Shared Memory
Allows process to share data using direct memory reference

구현
-  in both tables PTEs 는 같은 “물리 페이지”를 가리킨다
- 해당 물리 페이지가 invalid 하게 된다면 both PTEs 를 업데이트해야 한다.

Copy-on-Write
:페이지를 Write 할 때까지 가능한한 메모리 카피를 미룬다. 

구현
- 바로 페이지를 카피하는 것 대신에, 물리 메모리에 있는 동일한 페이지를 가리키도록 Shared Mapping 을 한다.
- Shared Pages are protected as read-only (Copy 프로세스의 PTE에 권한 설정)
- 이 페이지에 쓰기 작업을 할 때, OS 는 물리 메모리에 새로운 페이지를 할당하고, 그 페이지에 쓰기 작업을 하도록 한다.

사용
- fork()
- Allocating data and heap pages, etc.

fork()
- 부모 프로세스로부터 자식 프로세스를 생성하는 시스템콜

Instead of copying all pages, create shared mapping of parent pages in child address space
Shared pages are protected as read-only in child
Reads happen as usual
Writes generate a protection fault and OS copies the page, changes page mapping, and restarts write instruction

최대한 Lazy 하게, on-write 이라는 demand가 있을 때 Copy 를 한다.

Three Major Issues
1. 페이지 테이블은 얼마나 클까? 그리고 어떤 방식으로 저장하고, 접근할까?
2. 주소 전환(translation)과 access control check를 빠르게 할 방법이 없을까?
3. 주소 전환과 관련되어서 캐시(SRAM) 접근을 언제할까?

Virtual Memory Issue I
얼마나 페이지 테이블이 클까?

우리는 페이지 테이블을 물리 메모리에 저장한다.

ex) 32 비트 주소체계, 4KB 크기의 페이지
- 2^20 개의 페이지 개수 (페이지 엔트리 개수)
- 만약 하나의 페이지 엔트리 크기가 4 Bytes 이면
- 하나의 프로세스당 페이지 테이블의 크기는 4MB 이다.
- 왜이렇게 클까? 모든 주소 공간 영역에 대한 PTE를 고려했을 때 이렇게 페이지 테이블의 크기는 커진다.
- 특정한 지점에서 프로세스는 전체 주소공간(VM)을 사용하지 않고, 일부만 사용한다. <<
- Process may not be using the entire VM space

How can we store it efficiently without requiring physical memory that can store all page tables ?
- Idea: Multi-level page tables
- 처음에는 오직 first-level 페이지 테이블만 메모리에 존재한다.

- Page Table(혹은 PTE)에 대한 메모리를 “필요로 하는 만큼”만 사용하도록 한다.
- demand paging 과 같은 demand page table

Page Table Entry를 필요로 하는 만큼 사용하도록 하기 + Linked-List 자료구조로 엔트리 저장 
- 만약 Linked-List를 사용해서 필요로 하는 페이지 테이블 엔트리를 동적으로 추가하는 방식을 사용하게 된다면
- 페이지 테이블 크기에 비례하는 탐색 시간을 가지게 된다.
- 왜?
- 동적으로 추가되는 페이지 테이블 엔트리에 대응하는 페이지들은 noncontiguous 할 수 있다. 
- 즉, Linked-List 의 어느 위치에 페이지 테이블 엔트리가 있는지 모르기 때문에 전부 뒤져봐야 한다.

기존 방식은 VPN 으로 한 번에 페이지 테이블 엔트리에 접근할 수 있었다.

목표
1. 페이지 테이블 사이즈를 줄이자
- 필요로 할 때 페이지 테이블 엔트리를 추가하도록 하자
2. VPN에 대응하는 PTE 를 찾는 시간을 줄이자.

Solution: Mutli-level Page Tables
Allow each page table to be allocated non-contiguously

Outer page table: outer page number —> secondary page table 시작 주소
Secondary page table: secondary page # —> Page Frame # (Physical Page Number, PPN)

앞/바깥의 Page Table이 뒤의 Page Table를 포함하면서 훨씬 큰 영역을 커버한다.

멀티 레벨로 구성한 후에 특정 페이지에 대한 페이지 테이블 혹은 페이지 테이블 엔트리를 필요로 할 때만 생성할 수 있다.
- 필요로 할 때, Outer page table 엔트리가 커버하는 영역을 추가한 후에 Secondary Page Table을 추가하면 된다.
단점: 메모리 참조가 많아진다. (기존에는 한 번의 참조가 가능)

64 bit address space
- In 64 bit x86 architecture, 48-bit address has been used
- 2^48/2^12 = 2^36 개의 페이지 개수 (페이지 테이블 엔트리 개수)


2^36 개의 페이지 개수, 8 바이트의 페이지 테이블 엔트리
- 전부 메모리에 올리기에는 너무 크다
- 36 bit 를 여러 레벨로 쪼갠다.
- 4-level 로 쪼개면 한 레벨당 2^9 = 512 bytes
- 512 * 8 Bytes —> 작은 페이지 테이블 하나당 4KB 크기

정리
1. Single level page table
- 장점: 메모리 참조가 적다. VA —> PA 변환을 빠르게 가능
- 단점: 전체 페이지 테이블을 미리 다 만들어둬야 하기 때문에, 메모리 낭비가 크다.
- 주소 공간의 아주 일부분만을 사용하는 프로세스들이 많으면 “낭비되는” 공간이 많아진다.

그래서 필요한 부분의 PTE만 올려두려고 페이지 테이블/PTE을 Linked-List 로 관리하는 방식
PTE를 찾는데 시간 복잡도가 O(n) 만큼 소요된다.

2. Multi-level Page table
장점: 필요로 할 때마다 Page table entry 를 생성하여 메모리 공간에 유지시킨다.
단점: Single-level page table에 비해 메모리 참조/접근이 많이 발생한다. (level 만큼 참조해야 한다.)

지금까지의 방식은 메모리에 접근할 때마다 페이지 테이블에 접근해야 한다.
- 페이지 테이블은 메모리에 있으므로 총 메모리 접근이 2번 발생한다.
- 굉장히 비효율적이다.
- 페이지 테이블에 대한 캐시가 필요하다. 
—> 페이지 테이블 전용 캐시인 TLB

참고: 메모리 접근?
- fetch, lw/sw

참고: 페이지 테이블도 물리 메모리에 있기 때문에 내가 자주 접근하는 페이지 테이블은 캐시(SRAM)에 있다.
- locality

Hashed Page Tables
- Hash table?? 탐색/삽입/삭제를 O(1) 만의 할 수 있는 자료구조

Virtual Page Number is hashed into a page table
- this page table contains a chain of elements hashing to same location
- 즉, Collision 을 체이닝 방식으로 해결

Each element contains
- virtual page number
- the value of the mapped page fram
- a pointer to the next element

캐시 관점에서 Hashed page tables vs Multi-level page tables?
- Page Table에 대한 캐시

캐시는 locality 를 활용한 것이다.
- temporal, spatial
Multi-level page table 은 hash 방식에 비해 캐시 활용도가 높다. 즉 locality 를 잘 활용한다.
- 지역적으로 근처의 Virtual pages 의 경우 페이지 테이블에서도 해당 페이지 테이블 엔트리들이 붙어있을 확률이 매우 높다. 
- 즉 지역성을 매우 잘 활용했다.
Hashed page table의 경우, Virtual page가 붙어 있어도, 즉 지역적으로 근처여도 해쉬 함수에 의해 페이지 테이블에서 완전 멀리 떨어져서 존재할 수 있게 된다.
- 즉 locality 를 활용하지 못하는 것

Virtual Memory Issue II
- address translation 
- How can we make it fast?

Cache for PTE
- Translation lookaside buffer

고려 사항
1. TLB miss 시
- 어느 TLB entry를 대체할 것인지
- HW vs SW 어디에서 처리할 것인지
2. page fault
- 어떤 가상 페이지를 대체할 것인지
- HW vs SW 어디에서 처리할 것인지


TLB: cache for page table entries

누가 TLB 를 채우지?
1. SW
- invoke handler, will traverse the page table and fill tlb entry
- invoking the handler costs permormance (성능 안좋음)

2. HW
- OS에 투명하게 PTE 를 찾고 TLB 를 채운다.


mutliple Page Size
Page Size가 커지면 TLB가 커버하는 영역이 커진다.
- 왜?
- 페이지 사이즈가 올라가면 하나의 page table entry가 커버하는 영역/공간이 커지기 때문
단점
- 메모리의 internal fragmentation이 심해진다. (낭비)

몇몇 TLB는 address-space identifiers(ASIDs, == PID)를 저장한다.
ASIDs: 각각의 프로세스마다 고유하게 구분할 수 있는 ID (== Process ID)
- 기존 ASIDs가 지원되지 않은 TLB 에서는 프로세스를 구분하지 못하였기 때문에 컨텍스트스위칭이 발생할 때마다 TLB flush를 해줘야 했다.
- 왜? 어느 프로세스의 가상 주소 공간에 대한 페이지 테이블 엔트리인지 구분하지 못하니까!
- 하지만 ASIDs 의 지원으로 인해 컨텍스트 스위칭 시에도 TLB flush를 하지 않아도 된다.
- support multiple processes

Virtual Memory Issue III
- 언제 address translation 을 하지?
- 기존 방식은 캐시에 진입하는데 너무 많은 시간이 소요된다.

Address translation

1. Address translation before L1 cache
- L1 sees only physical addresses 
- Physically-indexed, physically-tagged (PIPT)
- too Slow L1 access

VA —> TLB —> PA
TLB Miss?
- 페이지 테이블 탐색
- 이것도 캐시에서 먼저 탐색
- 캐시에 없으면 메인 메모리에서 탐색
- TLB 미스 해결하고나서야 다시 캐시에 진입
—> 캐시에 접근하기 위해서 거쳐야 할 과정이 많다.


참고: 캐시 탐색 과정
a) indexing
b) tag matching

2. Address translation after L1 cache
- Virtually-Indexed, Virtually-Tagged Cache

- Fast L1 access, but Aliasing problem

Aliasing problem
- multiple VAs mapped to the same PA
- multiple blocks for the same physical address in the cache
- Consistency for duplicate blocks is complex


Need to flush the cache for context switch
- 캐시는 프로세스를 구분하지 못하기 때문에 플러시 작업이 필요하다.

Parallel TLB and Caches
Page offset is equal in PA and VA
- 왜? Page Size가 동일하기 때문이다.
- 즉 변하지 않는 Page Offset을 활용하여 캐시 index를 찾을 수 있고, 이후 TLB에서 변환된 PA 로 태그 매칭을 시도한다.
- 즉 캐시 인덱스 찾기 + VA —> PA 변환을 동시에

Set의 개수는 Page size에 의해 제한되어 있다.
- 캐시 사이즈를 증가시키기 위해서는 associativity 를 증가시켜야 하는데, 이는 캐시를 느리게 만든다.

ex)
4KB Page Size, 32B Cache Block Size
- 5 bits: Cache block offset
- 7 bits: Cache Index 
- 7 bits for index —> 128 sets

Maximum cache size
Direct-mapped: 128 X 32B = 4KB
2-way: 128 X 2 X 32B = 8KB
4-way: 128 X 4 X 32B = 16KB
8-way: 128 X 8 X 32B = 32 KB
만약 64KB ?? 16-way ?? too slow
- 너무 많은 태그 매칭 시간
- 그러면 associativity 를 증가시키는 대신에 sets 를 2배 증가시키는 것은 어떨까?


ex) 512 sets
- 2 비트를 추가로 필요로 한다.
- 추가로 필요한 비트를 Virtual Page Number 비트에서 사용한다.


Aliasing problem
- Mutliple sets for a PA 
- in this example, 2 extra bits are used —> 4 possible locations for a PA
- Aliasing problem 의 해결책인 4개의 겹칠 수 있는 공간을 탐색한다.
- Virtually-index, virtually-tagged cache 보다는 쉽게 synonym 을 찾을 수 있다.

No flushing needed for context switch

Swapping
- user program should be independent of the amount of physical memory
- demand paging

Consider physical memory as a ache for disks
- leverage locality of reference within processes
- process only uses small amount of address space at a moment
- only small amount of address space must be resident in physical memory
- store the rest of them to disk
- 참고로 전체 주소공간의 페이지가 아니라, 주소 공간에서 사용될 수 있는 페이지 영역을 디스크에 저장하는 것


How to Swap

1. process level swapping
- 매우 비효율적

2. page-level swapping
- swap out: mem to disk
- swap in: disk to mem

Where to Swap
Swap Space
- Disk Space.
- 페이지가 왔다 갔다 이동할 수 있도록 예약된 공간이다.
- swap space 공간은 maximum number of memory pages, 즉 메모리가 2배 있는 것과 같은 효과를 나타낸다.
- Block size is the same as the page size (Block: 디스크 기반 storage 장치의 단위)


When to Swap
- Threshold(임계점, 기준점) 에 기반하여 미리 스왑한다.
- Free pages 를 일정하게 유지하도록 한다.
- 2개의 Threshold: high(HW) and low(LW) watermark
- swap daemon(or page daemon) is responsible for freeing memory

if (# free pages < LW), the swap daemon starts to evict pages from physical memory
if (# free pages > HW), the swap daemon goes to slepp

만약 페이지에 대한 할당 요구 속도가 스왑하는 속도보다 빠르다면?
- e.g. malloc
- page fault 자주 발생
- 매우 느려진다 == Thrashing
- out of memory error 가 발생할 수 있다.
- 이럴 때는 특정 프로세스를 kill 하는 방법이 있다.

What to Swap
**중요**: 
- 만약 메모리에 있는 페이지로 작업을 했음에도 스왑 공간에 존재하는 원본에 영향이 없다면 반영하지 않고 버려도 된다. (Dropped)
- 만약 메모리에 있는 페이지에 변경사항이 있다면 스왑 공간에 존재하는 원본에도 반영을 해줘야 한다. (Swapped)

Kernel code 						—> Not Swapped
Kernel data 						—> Not Swapped
Page tables for user processes 		—> Not Swapped
Page tables for kernel processes 	—> Not Swapped
User code pages 					—> Dropped (코드는 동일, 즉 원본에서 변경되지 않는다. 반영할 필요 없음)
User data pages 					—> Dropped or swapped (전역, 정적 데이터에 변경사항이 있으면 반영해야한다. 변경사항이 없으면 버리면 된다.)
User heap/stack pages			—> swapped (변경사항이 존재할 것이라고 보고 반영 한다)

참고: 
- 스왑 공간에는 프로세스의 모든 페이지가 저장되어 있는 것이 아니라, 필요한 페이지만 스왑 아웃/인되며, 필요에 따라 새 페이지가 스왑 공간에 생성
- 일반적으로 코드나 데이터 영역의 페이지는 프로세스 실행 중에 필요하기 때문에, 프로세스가 시작될  스왑 공간에 원본이 생성되고, 원본이 계속 유지된다.
- 필요에 따라 새 페이지가 스왑 공간에 생성될 수 있는데, 이는 힙이나 스택같은 동적으로 할당되거나 해제되는 영역들에 의해서 새로운 페이지가 스왑 공간에 생성되거나, 해제될 수 있는 것이다.

스왑 공간 정리
1. 코드나 데이터 페이지 영역: 프로그램이 실행되기 전에 디스크의 스왑 공간에 해당 페이지 영역의 원본이 생성됩니다. 그리고 프로그램이 실행될 때, 물리 메모리에 필요한 페이지만 스왑 인되면서 복사된 카피 페이지가 생성됩니다. 이때 원본 페이지는 여전히 스왑 공간에 존재합니다.
2. 동적 할당을 위한 힙이나 스택 영역: 이러한 페이지는 처음에는 원본 페이지가 없습니다. 대신에, 프로세스가 동적으로 메모리를 할당할 때, 필요한 페이지들이 스왑 공간에 생성됩니다. 이때 원본 페이지가 없는 이유는 해당 페이지들이 처음 생성되는 것이기 때문입니다. 또한, 동적 할당된 페이지들은 사용이 끝나면 다시 스왑 아웃되면서 메인 메모리에서 삭제되고, 그에 해당 페이지의 원본 페이지에 반영되어야 한다. 

즉, 스왑 공간의 페이지는 메인 메모리의 카피 페이지에 대한 원본이 되는 것이 맞다


Page Replacement


물리 메모리에 있는 어느 페이지를 victim 으로 선정할 것인가?
- Write out the victim page to disk if modified (dirty bit set)
- If the victim pages is clean, just discard 
- —> the original version is either in the file system or in the swap space

why? “Page” is “fully associative”
- page가 어느 위치에 있는지 page table에 존재하기 때문에 (링크가 존재하기 때문에 전부 탐색할 필요가 없다.)
- 하지만 캐시에는 그런 링크가 없어서 fully-associative 의 경우 전부 탐색해야 하는 단점이 있다.

Minimize the page fault rate (miss rate)
- the miss penalty (cost of disk access) is so high

일반적으로 물리 메모리의 페이지의 개수를 늘리면, 즉 물리 메모리 자체를 늘리면 페이지 폴트가 줄어든다.

Page Replacement 구현

FIFO
- Maybe, the one brought in the longest ago is not beign used
- 그럴 가능성이 있다.

Optimal
- 이상적인 상황
replace page that will not be used for longest period of time
- 오랜 기간동안 사용되지 않을 페이지들을 replace 한다.
하지만 미래는 읽지 못한다.
즉 어느 페이지가 오랜 기간동안 사용되지 않을지는 알 방법이 전혀 없다!
그래서 Optimal 방식은 나의 알고리즘 수행 능력을 측정하거나 비교하기 위해서 사용된다.

LRU (least recently used)
- 최근에 가장 적게 쓴 것
- 가장 오랫동안 사용하지 않은 것

Optimal 방식은 미래를 알지 못한다는 단점이 있다.
그러나 우리는 과거의 지식, 즉 History 는 알 수 있다.

Replace page that has not been used in the most amount of time
각각의 페이지마다 마지막 사용 시간 (time of last use) 를 기록해야 한다.
일반적으로 좋은 알고리즘이고 자주 사용된다.

LRU 구현 방식
1. Counter
- 모든 페이지 엔트리는 카운터를 가지고 있고, 이 카운터는 최근에 사용된 Clock, 시간을 기록한다.
- 페이지를 replace 할 때, 카운터가 가장 작은 것을 선택한다.
- 하지만 모든 프로세스의 테이블의 모든 엔트리를 검사해야 하는 단점이 존재한다. (시간이 오래 걸림)

2. Stack implementation
- Recently used frame is moved up the stack (stack의 top으로 옮긴다.)
- Keep a stack of page numbers in a double link form (prev, next)
- Page referenced, 페이지 참조 시
- - move it to the top by changing head/tail pointers
- - approximate 기법이다.
- 각각의 업데이트는 비용이 들지만, 대체하기 위해서 탐색할 필요는 없다.

LRU Approximation
- reference bit in each PTE
- 페이지가 참조될 때, reference bit 를 세팅해준다.
- initially, the reference bit for each page is cleared by the OS

Clock
clock hand is used to select a victim
- when a page fault occurs, the page (the hand is pointing to)  is inspected
- if (R == 1), turn it off and go to next page (second chance)
- if (R == 0), evict the page
- Arm moves quickly when pages are needed

Physical Memory Allocation Polices 

1. Fixed-space allocation policy
- 각각의 프로세스는 그 프로세스가 사용할 수 있는 물리 페이지 수가 제한되어 있다.
- 제한에 다다르면, 자신의 물리 페이지를 replace(스왑)한다.
- Local replacement: 자기 자신만 한정해서 보기 때문에 local 이다.
- Virtual Machine (ex. ec2)에서 용량을 제한할 때 사용되는 방식

2. Variable-space allocation policy
- processes’ set of pages grows and shrinks dynamically
- Global replacement: 하나의 프로세스가 전체의 메모리 공간을 차지할 수도 있다.
- 실제 프로세스는 해당 Policy 사용

Thrashing
- page fault, swap 이 매우 자주 발생하는 상황

happens when physical memory is not enough to hold all the “working sets” of processes
- Working Set: 하나의 프로세스에서 active 하게 사용되는 페이지 집합
- Thrashing 이 발생하면 많은 CPU 이용 시간을 페이지를 스왑하는 데에 소비한다.

Sum of all processes’ (Working Set) > physical memory
- not enough physical memory
- Thrashing happens

참고:
- 애플리케이션마다 Working Set에 차이가 있을 수 있다.

possible solutions
- kill processes
- buy more memory


프로그램/프로세스는 Locality 가 존재한다.
Locality in a Memory-reference pattern
- temporal: 한 번 방문한 영역을 계속해서 방문한다.
- spatial: 한 번 방문한 영역 근처를 방문한다.


Locality
- 시간, 공간적으로 자주 접근하는 영역이고
- 캐시는 이 locality 특성을 활용해서 “특정 영역” 더 빠른 메모리에 올려놔서 빠르게 접근할 수 있도록 한다.

Demand Paging and Thrashing

Locality Model
- process migrates from one locality to another
- when a program/process runs, it will take up some space on the memory and access this portion(locality) of the memory many times until leaving the locality
- Working Set 역시 Locality 특성 가진다

demand가 있을 때 필요로 하는 해당 메모리 영역을 디스크로부터 더 빠른 접근속도를 가지는 메모리에 올려놓는다.
- ”cache”
- 이 메모리 영역은 Locality 가 존재하므로 더 빠르게 해당 영역을 접근할 수 있다.

why does thrashing occur?
•  (sum of size of processes Working set) > total memory size
- size of locality
