# 4월 9일 TIL (Today I Learned)

# HashMap in Java
- <Key: Value> 매핑값을 가지는 자료구조
- 검색 속도가 평균 O(1)
- 동시에 수정하지 못한다. (ConcurrentModificationException)

해쉬값이 같으면 체이닝을 통해 연결한다.
- Linked Node (using next, 포인터 개념)
  

하나의 노드 (Node)
- 주요 필드: 해쉬값(hash), Key, Value + next node
- 최초의 노드는 보초 노드(sentinel node)가 아니다. (사용하는 노드!)

``` java
static class Node<K,V> implements Map.Entry<K,V> {
    final int hash;
    final K key;
    V value;
    Node<K,V> next;

    Node(int hash, K key, V value, Node<K,V> next) {
        this.hash = hash;
        this.key = key;
        this.value = value;
        this.next = next;
    }
}

```

## Threshold 필드 (기준? 임계값?)

``` java
// - The bin count threshold for using a tree rather than list for a bin
// - bin? node !! (link로 연결된 노드)
static final int TREEIFY_THRESHOLD = 8;


// - resize operation 할 때, untree 하도록 하는 threshold
static final int UNTREEIFY_THRESHOLD

// - The smallest table capacity for which bins may be treeified
static final int MIN_TREEIFY_CAPACITY
```

## static 유틸리티 함수

``` java
// - key의 hash값 계산
static final int hash(Object key) {
    int h;
    return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
}

// - Returns a power of two size for the given target capacity.
// - n 보다 큰 근처 2의 제곱수를 반환해줌
// - 즉 table size == pow(2, x)
// - “>>>” : 앞에 0으로 채움
static final int tableSizeFor(int cap) {
    int n = -1 >>> Integer.numberOfLeadingZeros(cap - 1);
    return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
}
```

## 주요 필드

``` java

// - 테이블의 길이는 항상 2의 제곱수
transient Node<K,V>[] table;

// - cache 용도 (entrySet() 호출을 위한?)
transient Set<Map.Entry<K,V>> entrySet;

transient int size;

// - 구조적 변경 횟수
// - 매핑 수를 변경하거나 내부 구조를 수정한다. (Hash)
// - ConcrrentModificationException 을 발생시키기 위한 용도인데 Collection-view에서 iterators를 fail-fast로 만든다.
transient int modCount;

// - size가 이 threshold 를 넘으면 resize를 한다.
// - 즉 제한값!!!
// - threshold = capacity * loadfactor (기본적으로 capacity 보다 조금 작다.)
int threshold;

// - 위의 threshold 를 만드는 데 사용하는 듯하다.
// - 즉 하나의 해쉬 인덱스에서 얼마만큼 링크로 연결할 것인가.
final float loadFactor;
```

## public operation
- **중요**
  - capacity = table.length
  - 즉, capacity 는 2의 제곱수이다.
``` java
// - evict: 생성자에서 호출한 것일 때 false, 아니면 true
// --> LinkedHashMap에서 활용한다.
final void putMapEntries(Map<? extends K, ? extends V> m, boolean evict) {
    int s = m.size();
    if (s > 0) {
        if (table == null) {
            float ft = ((float)s / loadFactor) + 1.0F;
            int t = ((ft < (float)MAXIMUM_CAPACITY) ?
                        (int)ft : MAXIMUM_CAPACITY);
            if (t > threshold)
                threshold = tableSizeFor(t);
        } else {
            // Because of linked-list bucket constraints, we cannot
            // expand all at once, but can reduce total resize
            // effort by repeated doubling now vs later
            while (s > threshold && table.length < MAXIMUM_CAPACITY)
                resize();
        }

        for (Map.Entry<? extends K, ? extends V> e : m.entrySet()) {
            K key = e.getKey();
            V value = e.getValue();
            putVal(hash(key), key, value, onlyIfAbsent: false, evict);
        }
    }
}


final Node<K,V> getNode(Object key) {
    Node<K,V>[] tab; Node<K,V> first, e; int n, hash; K k;
    if ((tab = table) != null && (n = tab.length) > 0 &&
            // (n - 1) & hash: n - 1 인덱스를 넘지 않게 해쉬값을 적용하도록 한다.
            // n == pow(2, x), 즉 2의 제곱수
            // n bit: 0x0010000000000000
            // n - 1 bit: 0x0001111111111111
            (first = tab[(n - 1) & (hash = hash(key))]) != null) {

        // always check first node 
        // 해쉬값이 같더라도 key 가 다를 수 있기 때문에 노드를 확인한다.
        if (first.hash == hash && 
            ((k = first.key) == key || (key != null && key.equals(k))))
            return first;

        if ((e = first.next) != null) {
            if (first instanceof TreeNode)
                return ((TreeNode<K,V>)first).getTreeNode(hash, key);
            do {
                if (e.hash == hash &&
                    ((k = e.key) == key || (key != null && key.equals(k))))
                    return e;
            } while ((e = e.next) != null);
        }
    }
    return null;
}
// - 여기서 TreeNode? 
// - 노드는 기본적으로 연결 List 형태 (next)
// - 근데 일정 사이즈를 넘으면 Tree로 변환한다고 되어있다. (TREEIFY_THRESHOLD)
// - 노드가 트리 형태일 때는 table[hash값] 이 트리의 루트 노드

// - onlyIfAbsent: 덮어쓰기 X
// - evict: 생성모드(false), 나머지(true)

final V putVal(int hash, K key, V value, boolean onlyIfAbsent,
                   boolean evict) {
    Node<K,V>[] tab; Node<K,V> p; int n, i;

    if ((tab = table) == null || (n = tab.length) == 0)
        n = (tab = resize()).length;

    // 배열을 할당한다 하더라도 인자는 null 이다.
    if ((p = tab[i = (n - 1) & hash]) == null)
        tab[i] = newNode(hash, key, value, null);

    else {
        Node<K,V> e; K k;
        if (p.hash == hash &&
            ((k = p.key) == key || (key != null && key.equals(k))))
            e = p;
        else if (p instanceof TreeNode)
            e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value);
        else {
            for (int binCount = 0; ; ++binCount) {
                // 기존에 키에 해당하는 노드가 없으면 새로 노드를 생성한다.
                if ((e = p.next) == null) {
                    p.next = newNode(hash, key, value, null);

                    // 만약 bin개수, 즉 노드 개수가 일정 임계값을 넘으면 해쉬에 해당하는 노드 연결 리스트를 트리로 변환한다.
                    if (binCount >= TREEIFY_THRESHOLD - 1) // -1 for 1st (첫번째 것도 포함시키기 때문에)
                        treeifyBin(tab, hash);
                    break;
                }
        
                // 기존 키에 해당하는 노드를 보유하고 있는지 확인(key로) 및 있으면 해당 노드를 반환할 준비 (to p) (무조건 대치하는 것이 아님, onlyIfAbsent를 판단해야 한다.)
                if (e.hash == hash &&
                    ((k = e.key) == key || (key != null && key.equals(k))))
                    break;
                p = e;
            }
        }

        // existing mapping for key
        // 즉 기존에 키에 대해서 노드가 존재한다면 onlyIfAbsent에 따라서 넣을지 말지를 결정한다.
        if (e != null) { 
            V oldValue = e.value;
            if (!onlyIfAbsent || oldValue == null)
                e.value = value;

            // 후처리?
            afterNodeAccess(e);

            // 기존값(oldValue) 반환!!
            return oldValue;
        }
    }

    // 기존에 키에 해당하는 노드가 없을 때 진행

    // 수정횟수 증가 
    ++modCount;

    // 사이즈를 하나 증가시키는데 사이즈 임계값(제한)을 넘는다면 resize를 진행한다.
    if (++size > threshold)
        resize();

    afterNodeInsertion(evict);
    return null;
}

// afterNodeAccess, afterNodeInsertion
// --> LinkedHashMap 에서 처리 (HashMap은 X)

// resize 한 “테이블” 을 반환
// 무엇에 관해서 resize? capacity or threshold !!!
final Node<K,V>[] resize() {
    Node<K,V>[] oldTab = table;

    // capacity == table.length
    // capacity ==> pow(2, x)
    // bit: 0x0010000000000000
    int oldCap = (oldTab == null) ? 0 : oldTab.length;
    int oldThr = threshold;
    int newCap, newThr = 0;
    if (oldCap > 0) {
        if (oldCap >= MAXIMUM_CAPACITY) {
            threshold = Integer.MAX_VALUE;
            return oldTab;
        }
        // double capacity
        // capacity 는 2의 제곱수였다. 
        // 즉, 2를 곱하면 역시 2의 제곱수이다.
        // bit: 0x0010000000000000
        else if ((newCap = oldCap << 1) < MAXIMUM_CAPACITY &&
                    oldCap >= DEFAULT_INITIAL_CAPACITY)
            // double threshold        
            newThr = oldThr << 1; 
    }
    // initial capacity was placed in threshold
    else if (oldThr > 0) 
        newCap = oldThr;
    else {
        // 기본 생성자를 사용했을 때!
        newCap = DEFAULT_INITIAL_CAPACITY;
        newThr = (int)(DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
    }
    // 위의 initail capacity(newCap) 가 threshold로 대치되었을 때, newThr(threshold) 도 변경
    if (newThr == 0) {
        float ft = (float)newCap * loadFactor;
        newThr = (newCap < MAXIMUM_CAPACITY && ft < (float)MAXIMUM_CAPACITY ?
                    (int)ft : Integer.MAX_VALUE);
    }
    threshold = newThr;
    
    // 완전히 기존 테이블을 대치할 새로운 테이블!
    Node<K,V>[] newTab = (Node<K,V>[])new Node[newCap];
    table = newTab;

    // 기존 테이블 값들을 새로운 테이블에 넣어줘야 한다.
    if (oldTab != null) {

        // 테이블을 순회하면서 ~
        for (int j = 0; j < oldCap; ++j) {
            Node<K,V> e;
            if ((e = oldTab[j]) != null) {
                // << 미리 null 처리, 리소스 해제 
                oldTab[j] = null;
                if (e.next == null)
                    newTab[e.hash & (newCap - 1)] = e;
                else if (e instanceof TreeNode)
                    ((TreeNode<K,V>)e).split(this, newTab, j, oldCap);

                // preserve order
                // 중요!!!, 사실상 resize의 핵심
                else { 
                    Node<K,V> loHead = null, loTail = null;
                    Node<K,V> hiHead = null, hiTail = null;
                    Node<K,V> next;
                    do {
                        next = e.next;
                        /**
                         * rehash
                         * 기존 인덱스: e.hash & (oldCap - 1)
                         * 변경된 인덱스: e.hash & (newCap - 1) —> 기존 oldCap 제일 오른쪽 비트에서 1 비트가 하나 더 추가됨. 
                         * 0x00111 (oldCap - 1)
                         * 0x01111 (newCap - 1)
                         * --> (newCap - 1) == (oldCap - 1) + oldCap
                         * 0x01000 (oldCap)
                         * 즉, e.hash & oldCap 을 했을 때 0 or 1 만 나오는 데 0 이면 인덱스를 유지시키고 1이면 기존 인덱스에 oldCap을 더하면 된다. 
                         * 
                         * 이게 바로 capacity(table length) 를 2의 제곱수로 한 이유이다!!!
                         * */
                        if ((e.hash & oldCap) == 0) {
                            if (loTail == null)
                                loHead = e;
                            else
                                loTail.next = e;
                            loTail = e;
                        }
                        else {
                            if (hiTail == null)
                                hiHead = e;
                            else
                                hiTail.next = e;
                            hiTail = e;
                        }
                    } while ((e = next) != null);
                    if (loTail != null) {
                        loTail.next = null;
                        newTab[j] = loHead;
                    }
                    if (hiTail != null) {
                        hiTail.next = null;
                        newTab[j + oldCap] = hiHead;
                    }
                }
            }
        }
    }
    return newTab;
}

// - all linked node ==> 트리 구조로 변경
final void treeifyBin(Node<K,V>[] tab, int hash) {
    int n, index; Node<K,V> e;
    if (tab == null || (n = tab.length) < MIN_TREEIFY_CAPACITY)
        resize();
    else if ((e = tab[index = (n - 1) & hash]) != null) {
        TreeNode<K,V> hd = null, tl = null;
        do {
            TreeNode<K,V> p = replacementTreeNode(e, null);
            if (tl == null)
                hd = p;
            else {
                p.prev = tl;
                tl.next = p;
            }
            tl = p;
        } while ((e = e.next) != null);
        if ((tab[index] = hd) != null)
            hd.treeify(tab);
    }
}

/**
 * 짧게 TreeNode 구조
 * - extends LinkedHashNap.Entry<K, Value> <<  extends HashMap.Node<K, V>
 * - Key, Value, Hash, Next 가지고 있음
 * ++ parent, left, right, prev (needed to unlink next upon deletion?)
 **/


final Node<K,V> removeNode(int hash, Object key, Object value,
                               boolean matchValue, boolean movable) {
    Node<K,V>[] tab; Node<K,V> p; int n, index;
    if ((tab = table) != null && (n = tab.length) > 0 &&
        (p = tab[index = (n - 1) & hash]) != null) {
        Node<K,V> node = null, e; K k; V v;
        if (p.hash == hash &&
            ((k = p.key) == key || (key != null && key.equals(k))))
            node = p;
        else if ((e = p.next) != null) {
            if (p instanceof TreeNode)
                node = ((TreeNode<K,V>)p).getTreeNode(hash, key);
            else {
                do {
                    if (e.hash == hash &&
                        ((k = e.key) == key ||
                            (key != null && key.equals(k)))) {
                        node = e;
                        break;
                    }
                    p = e;
                } while ((e = e.next) != null);
            }
        }
        if (node != null && (!matchValue || (v = node.value) == value ||
                                (value != null && value.equals(v)))) {
            if (node instanceof TreeNode)
                ((TreeNode<K,V>)node).removeTreeNode(this, tab, movable);
            else if (node == p)
                tab[index] = node.next;
            else
                p.next = node.next;
            ++modCount;
            --size;
            afterNodeRemoval(node);
            return node;
        }
    }
    return null;
}
// - remove 시에는 resize() 를 안하는 듯?
// - resize() 는 뭔가 삽입하거나 compute 할 때


public V compute(K key,
                     BiFunction<? super K, ? super V, ? extends V> remappingFunction)

// - 키와 연관된 값을 계산하거나 업데이트하는 기능
// - oldValue = null or old.value;
V v = remappingFunction.apply(key, oldValue);

// - value는 null일 수도 있으니까 BiFunction을 전달할 때는 null 처리도 해줘야 한다!
// - 이를 통해 존재하지 않는 키를 통해 값을 참조하려 할 때의 NullPointerException을 방지할 수 도 있고, 코드의 간결성, 가독성을 높인다.
// ex) map.compute(k, (k,v) -> ㅍ == null ? V1 : V2)

// merge() 도 같은 맥락이다.
// - 하지만 key, old.value 를 BiFunction 의 입력으로 전달하는 것이 아니라 old.value와 new value를 BiFunction에 전달한다.
// - 기존 값과 새로운 값을 병합

if (old.value != null)
	V v = remappingFunction.apply(old.value, value);


// clone !!
@Override
public Object clone() {
    HashMap<K,V> result;
    try {
        result = (HashMap<K,V>)super.clone();
    } catch (CloneNotSupportedException e) {
        // this shouldn't happen, since we are Cloneable
        throw new InternalError(e);
    }
    result.reinitialize();

    // 기존값을 전부 새로 넣는다.
    // Deep Copy <<
    result.putMapEntries(this, false);
    return result;
}

```

TreeNode 짧게 살펴보기

``` java

final TreeNode<K,V> find(int h, Object k, Class<?> kc) {
    TreeNode<K,V> p = this;
    do {
        int ph, dir; K pk;
        TreeNode<K,V> pl = p.left, pr = p.right, q;
        if ((ph = p.hash) > h)
            p = pl;
        else if (ph < h)
            p = pr;
        else if ((pk = p.key) == k || (k != null && k.equals(pk)))
            return p;
        else if (pl == null)
            p = pr;
        else if (pr == null)
            p = pl;
        else if ((kc != null ||
                    (kc = comparableClassFor(k)) != null) &&
                    (dir = compareComparables(kc, k, pk)) != 0)
            p = (dir < 0) ? pl : pr;
        else if ((q = pr.find(h, k, kc)) != null)
            return q;
        else
            p = pl;
    } while (p != null);
    return null;
}
```
