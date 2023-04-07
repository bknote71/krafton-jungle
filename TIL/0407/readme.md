# QuickSort Algorithm
- Sort 알고리즘 중 하나
- 평균 O(n*logn), 최악의 경우 O(n^2) 의 시간복잡도를 가진다.

기본적인 원리?
- 피봇(pivot)을 기준으로 파티션 + 분할 정복

## 파티션(Partition) 알고리즘
- 호어 vs 로무토
- 피봇(기준)을 가지고 나누는 방법에 따라 알고리즘이 달라진다.

### Lomuto(로무토) Partition Algrorithm
- 구간의 맨 끝(right)을 피봇으로 잡는다. 
- pivot 보다 작은 것을 왼쪽부터 축적해 나간다.
- 축적한 pivot보다 작은 요소 중에 가장 오른쪽 인덱스를 반환한다.

``` c 

int partitionByLomuto(int arr[], int left, int right)
{
	int pivot = arr[right];
	int storeIdx = left - 1;
	for (int i = left; i < right; ++i)
	{
		if (arr[i] < pivot)
		{
			swap(&arr[++storeIdx], &arr[i]);
		}
	}

	swap(&arr[storeIdx + 1], &arr[right]);
	return storeIdx + 1;
}
```

- 구간의 제일 오른쪽을 피봇으로 하기 싫으면 원하는 피봇을 설정하고 가장 오른쪽 요소와 swap하면 된다.


### Hoare(호어) Partition Algorithm
- 피봇을 자유롭게 설정한다. (middle?)
- 피봇보다 큰 요소가 있는 것을 찾는다. (i)
- 피봇보다 작은 요소가 있는 것을 찾는다. (j)
- 찾은 둘 요소를 swap 한다.
- i 요소가 j 요소보다 크거나 같을 때까지 그만한다.
- 마지막에 i 요소는 j 요소보다 같거나 1 크다.

``` c

int partitionByHoare(int arr[], int left, int right, int pivot)
{
	int i = left - 1;
	int j = right + 1;
	while (i <= j){
		do
			{
		i++;
		} while(arr[i] < pivot)

		do
		{
			j++;
		} while(arr[j] < pivot)

		if (i >= j)
		{
			return j;
		}

		swap(&arr[i], &arr[j]);
	}

}
```


- 로무토 알고리즘보다 swap을 덜 발생시키기 때문에 좀 더 효율적이다.



## QuickSort 알고리즘은 각각의 단점을 보완하기 위해 여러 다양한 알고리즘이 존재한다.

1. Standard quicksort
- 피봇을 기준으로 파티션하고 분할 정복을 이용하여 피봇 양 사이드도 정렬하도록 한다.

``` c
void quickSort(int arr[], int left, int right)
{
	if (left >= right)
		return;

	int pivot = partition(arr, left, right);
	quickSort(left, pivot - 1);
	quickSort(pivot + 1, right);
}

```

- 언제 worst-case ?
  - 인풋 데이터가 이미 정렬되었거나 거의 정렬되었을 때 O(n^2) 시간 복잡도가 소요된다.
  - 이미 정렬된 배열에 피봇을 맨 끝으로 잡았다고 가정하고 정렬을 생각해보면 O(n^2)가 소요된다.


2. Randomized quicksort
- 항상 middle 요소를 피봇으로 설정하는 것 대신에, 피봇 요소를 랜덤하게 선택한다.
- 이를 통해 worst-case 를 피하도록 도와줄 수 있다.

``` c
void quickSortRandomized(int arr[], int left, int right)
{
	if (left >= right) 
		return;

	int pivot = partitionRandomized(arr, left, right);
	quickSortRandomized(arr, left, pivot - 1);
	quickSortRandomized(arr, pivot + 1, right);
}

int partitionRandomized(int arr[]. int left, int right)
{
	int pivotIndex = rand() % (right - left + 1) + left;
	int pivot = arr[pivotIndex];

	// 이제부터 로무토 or 호어 파티션 알고리즘 적용하면 된다.
	swap(&arr[pivotIndex],&arr[right]);
	int storeIndex = left - 1; 
	for(int i = left; i < right; ++i)
	{
		if (arr[i] < pivot)
		{
			swap(&arr[++storeIndex], &arr[i]);
		}
	}

	swap(&arr[storeIdx + 1], &arr[right]);
	return storeIdx + 1;
}
```

3. Three-way quickSort
- Standard Version + 인풋 데이터를 “피봇과 동일한 요소”들의 left, right 사이드로 분할한다.
- 파티션 중간에 모든 동일한 요소를 함께 그룹화하는 것이 더 효율적일 수 있습니다

``` c
void quickSortThreeWay(int arr[], int left, int right)
{
	if (left >= right)
		return;

	int lt, gt;
	partitionThreeWay(arr, left, right, &lt, &gt);
	quickSortThreeWay(arr, left, lt - 1);
	quickSortThreeWay(arr, gt + 1, right);
}

int partitionThreeWay(int arr[], int left, int right, int* lt, int* gt)
{
	// 1개의 피봇 + 2개의 사이드 구분 (lt, gt)
	int pivot = arr[left];
	int i = left + 1; // lt와 gt 중간을 이동하는 인덱스
	*lt = left;
	*gt = right;

	while(i <= *gt)
	{
		if (arr[i] < pivot) {
			swap(&arr[*lt], &arr[i]);
			i++;
			(*lt)++;
		} else if (arr[i] > pivot)
		{
			swap(&arr[i], &arr[*gt])			;
			(*gt)—;
		} else { ++i; } // 같은 요소들을 만나면 i만 증가시키고 양 사이드를 나누는 lt, gt 는 움직이지 않는다.
	}
}
```


4. Dual-pivot quickSort:
- 2개의 피봇을 사용하여 3개의 부분으로 배열을 파티션한다.
- 이 방법은 performance를 향상시킬 수 있으며 매우 반복되는 데이터를 처리하는데 적합하다.
- 자바 버전 7 이후로 Java Standard Library에 적용되었다. (Arrays.sort 함수 내부적으로 dualPivotQuickSort를 사용한다.)

- 두 개의 피봇: p and q
- 3개의 부분으로 나눈다, p보다 작은 요소들, p와 q 사이의 요소들, p보다 큰 요소들
- 3개의 파트를 분할 정복 + 재귀를 이용하여 정렬한다.

- 두 개의 피봇을 사용하는 이점은 배열을 정렬하는데 피룡한 많은양의 swap과 비교를 감소시킨다.
- 특히 많이 중복되는 요소들을 포함하는 배열이 있을 때는 많은 양의 “비교(comparision)”  작업을 감소시킨다.
  


in Java example

``` java
public static void dualPivotQuickSort(int[] arr, int low, int high) {
    if (low < high) {
        if (arr[low] > arr[high]) {
            swap(arr, low, high);
        }

        int pivot1 = arr[low];
        int pivot2 = arr[high];

        int i = low + 1;
        int j = high - 1;
        int k = i;

        while (k <= j) {
            if (arr[k] < pivot1) {
                swap(arr, k, i);
                i++;
            } else if (arr[k] >= pivot2) {
                while (arr[j] > pivot2 && k < j) {
                    j--;
                }

                swap(arr, k, j);
                j--;

                if (arr[k] < pivot1) {
                    swap(arr, k, i);
                    i++;
                }
            }
            k++;
        }

        i--;
        j++;

        swap(arr, low, i);
        swap(arr, high, j);

        dualPivotQuickSort(arr, low, i - 1);
        dualPivotQuickSort(arr, i + 1, j - 1);
        dualPivotQuickSort(arr, j + 1, high);
    }
}

private static void swap(int[] arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
```

- 어려우니까 다시한번 봐야할 듯 하다.

5. Hybrid quickSort
- 퀵 소트와 다른 sorting 알고리즘(insertion, heap, …)을 결합한 알고리즘
- small subarrays 에 대해서 느리지만 “효율”적인 정렬을 하기 위함이다.
- 매우 작은 배열에 대해서 재귀 함수 호출에 대한 오버헤드가 매우 커질 수 있기 때문에 이런 알고리즘이 탄생하였다.
- adaptive behavior (적합한 행동)


with insertion sort
``` c

void quickSort(int arr[], int left, int right) {

	// If subarray is small, switch to Insertion Sort
	if (right - left <= 10) { 
       		insertionSort(arr, left, right);
        		return;
    	}

    	int pivot = partition(arr, left, right); // Select pivot and partition array
    	quickSort(arr, left, pivot - 1); // Recursively sort left subarray
    	quickSort(arr, pivot + 1, right); // Recursively sort right subarray
}

// Insertion Sort function
void insertionSort(int arr[], int left, int right) {
    	int i, j, temp;
    	for (i = left + 1; i <= right; i++) {
       		temp = arr[i];
       	 	j = i - 1;

        		while (j >= left && arr[j] > temp) {
            		arr[j + 1] = arr[j];
            		j--;
        		}
        		arr[j + 1] = temp;
   	 }
}
```


introsort
- Hybrid: QuickSort + HeapSort + InsertionSort
- 재귀의 깊이가 특정 임계치를 초과하거나 서브배열의 크기가 매우 작을 때 다른 정렬 알고리즘으로 전환할 수 있다.
- 좋은 worst-case performance + 작은 오버헤드 !!

``` c

// Quicksort function with introsort
void introsort(int arr[], int left, int right) {
	// If subarray is small, switch to Insertion Sort
    	if (right - left <= 10) { 
       		insertionSort(arr, left, right);
        		return;
    	}

	// Compute maximum recursion depth
    	int maxdepth = floor(log2(right - left + 1)); 
	
	// Sort using Quicksort with depth limit
   	quickSortWithDepthLimit(arr, left, right, maxdepth); 

	// If array is not fully sorted, switch to Heapsort
    	if (!isSorted(arr, left, right)) { 
        		heapSort(arr, left, right);
    	}
}

// Quicksort function with depth limit
void quickSortWithDepthLimit(int arr[], int left, int right, int depthlimit) {

	// If recursion depth exceeds limit, switch to Heapsort
    	if (depthlimit == 0) { 
        		heapSort(arr, left, right);
        		return;
    	}

    	int pivot = partition(arr, left, right); // Select pivot and partition array
    	quickSortWithDepthLimit(arr, left, pivot - 1, depthlimit - 1); // Recursively sort left subarray
    	quickSortWithDepthLimit(arr, pivot + 1, right, depthlimit - 1); // Recursively sort right subarray
}

// Heapsort function
void heapSort(int arr[], int left, int right) {
    	int n = right - left + 1;
    	for (int i = n / 2; i >= 1; i--) {
        		heapify(arr, left, right, i, n);
   	 }
    	for (int i = n; i >= 2; i--) {
        		swap(arr, left, left + i - 1);
        		heapify(arr, left, right, 1, i - 1);
    	}
}

// Heapify function
void heapify(int arr[], int left, int right, int i, int n) {
    	int largest = i;
   	int l = 2 * i;
    	int r = 2 * i + 1;

    	if (l <= n && arr[left + l - 1] > arr[left + largest - 1]) {
        		largest = l;
   	}
    	if (r <= n && arr[left + r - 1] > arr[left + largest - 1]) {
        		largest = r;
    	}
    	if (largest != i) {
        		swap(arr, left + i - 1, left + largest - 1);
        		heapify(arr, left, right, largest, n);
    	}
}

// Swap function
void swap(int arr[], int i, int j) {
    	int temp = arr[i];
    	arr[i] = arr[j];
    	arr[j] = temp;
}

// Check if array is fully sorted
int isSorted(int arr[], int left, int right) {
    	for (int i = left + 1; i <= right; i++) {
        		if (arr[i] < arr[i - 1]) {
            	return 0; // array is not sorted
        		}
    	}
    	return 1; // array is sorted
}
```

partially sort
``` c
void quickSort(int arr[], int left, int right)
{
	if (left >= right)
		return;

	// check if array is partially sorted
	if (isSorted(arr, left, right))
	{
		return;
	}

	int pivot = partition(arr, left, right);
	quickSort(arr, left, pivot - 1);
	quickSort(arr, pivot + 1, right);
	
}
```

### **here is an optimized QuickSort**
``` c
void quickSortOptimized(int arr[], int left, int right) 
{
	while (left < right)
	{
		// choose pivot using median-of-three method
		int pivot = medianOfThree(arr, left, right);
		
		// partition array and get pivot index
		int pivotIndex = partition(arr, left, right, pivot);
	
		// recursively sort left and right subarrays
		if (pivotIndex - left < right - pivotIndex)
		{	
			quickSortOptimized(arr, left, pivotIndex - 1);
			left = pivotIndex + 1;
		} else {
			quickSortOptimized(arr, pivotIndex + 1, right);
			right = pivotIndex - 1;
		}
	}
}
// left vs mid vs right 중 중간값을 선택한다.
int medianOfThree(int arr[], int left, int right)
{
	int mid = (left + right) / 2;
	if (arr[left] > arr[mid]) 
	{
		swap(&arr[left], &arr[mid]);
	}

	if (arr[left] > arr[right]) 
	{
		swap(&arr[left], &arr[right]);
	}

	if (arr[mid] > arr[right]) 
	{
		swap(&arr[mid], &arr[right]);
	}
	return arr[mid];
}

int partitionByHoare(int arr[], int left, int right, int pivot)
{
	int i = left - 1;
	int j = right + 1;
	while (i <= j){
		do
			{
		i++;
		} while(arr[i] < pivot)

		do
		{
			j++;
		} while(arr[j] < pivot)

		if (i >= j)
		{
			return j;
		}

		swap(&arr[i], &arr[j]);
	}

}
```

최적화 방식
1. 재귀 대신 반복(Iterative): 함수 호출 + 스택 사용등의 오버헤드를 피하기 위해서 recursion을 2번 사용하는 것이 아니라 recursion 1번 + while loop를 결합했다.
2. Median-of-Three pivot selection: pivot이 left, right, middle 요소의 3 개의 값 중 중간값(median)이다. 이 피봇 선정을 통해 bad pivot 선택 가능성을 줄이고, 부분 정렬의 성능을 향상 시킨다.
3. 호어: 로무토보다 성능이 좀 더 좋다. (swap 콜이 더 적다.)
4. Tail Recursion elimination: use tail recursion —> 함수 호출 (스택 사용) 오버헤드를 줄인다!
5. Inlined swap function? 인라인 함수는 함수 호출의 오버헤드를 줄이는 것 같다. (사실 인라인 부분은 잘 모르긴 한다.)

전체적으로 좋은 성능 향상을 제공한다.
하지만 최적의 구현은 특정 사용 사례와 입력 데이터에 따라 달라질 수 있습니다.

## QuickSort의 장점과 단점

장점
1. 평균 시간 복잡도: O(n log n), faster then Merge Sort and Heap Sort
2. in-place 정렬 알고리즘: input array 이외의 추가의 메모리를 필요로 하지 않는다. (like Merge Sort)
3. 분할 정복 알고리즘: 멀티코어 시스템에서 병렬적으로 실행하기에 적합하다 (parallel <<)
4. 캐쉬 친화적 알고리즘: 왜? Input array 에서만 접근하기 때문이다.

단점
1. 최악의 시간 복잡도: O(n^2), Poor pivot selection이나 이미 정렬되어있거나 거의 정렬되어 있는 배열일 때 발생할 수 있다.
2. not stable sorting algorithm: “키가 동일한 요소”의 상대적인 순서가 정렬 후에 유지되지 않을 수 있다.
3. 크기가 작은 배열에 대해서 성능이 상당히 떨어진다.
- 크기가 작아도 계속 쪼개지면서 재귀함수를 호출해야하기 때문에 재귀 호출을 사용하지 않는 정렬보다 오버헤드가 더 발생할 수도 있다.
- 크기가 작은 배열일 경우에는 Insertion Sort or Selection Sort 알고리즘이 좀 더 효율적일 수 있다.
4. 많은 양의 중복되는 데이터를 정렬하는데 적합하지 않다, 왜냐하면 많은 불균형한 파티션을 생성할 수 있고 이는 성능을 떨어뜨린다.

Recursion 없는 퀵소트 
- Stack 을 사용하여 구현할 수는 있다.
- 하지만 오히려 이것 때문에 더 많은 메모리를 사용하게 된다고 한다.

## QuickSort vs MergeSort
- 둘 다 O(n log n) 의 시간복잡도를 가지는 매우 효율적인 알고리즘이다
- 근데도 왜 대부분 퀵소트를 사용할까? 심지어 최악의 경우 O(n^2) 일텐데?
- 4가지 이유 <<

1. Cache locality
- QuickSort의 장점 중 하나인 in-place 정렬 알고리즘은 추가적인 매모리를 요구하지 않고 원래의 배열만을 가지고 정렬할 수 있는데 이는 Merge Sort 보다는 좀 더 캐쉬 친화적이다.
- MergeSort는 정렬을 하기 위해서 추가적인 서브 배열(메모리)를 필요로 한다.
- 이 서브 배열이 캐쉬 사이즈를 초과하게 된다면 더더욱 성능에 영향을 끼칠 수밖에 없다.

2. Pivot Selection
- QuickSort의 성능은 피봇 선정에 의존적이다. ㅇㅈ? ㅇㅇㅈ
- 피봇 선정이 잘 될 시 대략 균등한 사이즈로 2개의 서브 배열로 분할한다. 이는 빠른 실행시간을 갖게한다.
- 대조적으로 MergeSort는 항상 반으로 나누기 때문에 최적화 요소가 부족하다.

3. Tail Recursion
- QuickSort is tail-recursive
- recursive call is the last operation performed in the function
- 이 때문에 컴파일러측에서 최적화를 진행해서 코드를 재귀 호출 대신 loop로 대치할 수 있다 —> 재귀 대신 루프? 오버헤드 감소!

4. Adaptive Behavior 
- Adaptive Algorithm
- 상황(ex. input data)에 따른 적합한 행동을 가능하게 한다.
- 예: input array가 부분적으로 정렬되어있는 상황이면 이에 따라 대응하게 할 수 있다. (위에 적어놈)
- ++ hybrid, introsort, partially sort

정리하지면, 위와 같은 이유 때문에 퀵소트는 머지소트보다 성능이 좋다.





















































































































