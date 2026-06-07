---
title: 排序算法小结
date: 2020-08-01 17:22:04
updated:
tags:
- 排序
- 算法
---

排序算法，面试中最经常被问到的问题，我们需要熟悉并了解各种算法的时间和空间复杂度、时间复杂度平均、最坏、最好的情况和是否为稳定排序。

 {% asset_img 0.png  image %}

<!--more-->

### 1.插入排序（Insertion Sort）

#### 算法描述

插入排序的原理有点像我们平时打扑克牌，假设手中的扑克牌要从左到右依次从大到小，你每次抽牌的时候，从右边最小的牌与所抽到的牌比较，从右到左比较，直到找到第一张不小于所抽牌数值大小的牌，插入在其后面，这样就完成了一次插入排序的操作。显然，这样的操作最坏的情况就是每次都要遍历一遍数组，而且如果不是链表这种结构的话，数据插入数组，后面的所有数据都要往后一个位置，造成的开销会很大，时间复杂度O(n^2)。如果数组一开始就是有序的话，那就是最好的时间复杂度，每次插入到最后的位置，且只需要和数组的最后一个元素比较大小，时间复杂度O(n)。

#### 图示

 {% asset_img 1.gif  image %}

#### 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

void show(vector<int>& arr) {
	int size = arr.size();
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void insertionSort(vector<int>& arr) {
	int len = arr.size();
	int cur = -1, count = 0;
	cout << "Round " << count << ": ";
	show(arr);
	while (++cur < len) {
		for (int i = cur; ~i; i--) {
			if (arr[i] >= arr[i-1]) break;
			else swap(arr[i], arr[i-1]);
		}
		cout << "Round " << ++count << ": ";
		show(arr);
	}
}

int main() {
	cout << "Please input the number of elements: ";
	int size;
	cin >> size;
	std::vector<int> arr;
	for (int i = 0; i < size; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}
	cout << "Insertion sorting ..." << endl;
	insertionSort(arr);
	show(arr);
}
```



### 2.希尔排序（Shell Sort）

#### 算法描述

**希尔排序**（Shellsort），也称**递减增量排序算法**，是[插入排序](https://zh.wikipedia.org/wiki/插入排序)的一种更高效的改进版本。希尔排序是非稳定排序算法。

希尔排序是基于插入排序的以下两点性质而提出改进方法的：

- 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到[线性排序](https://zh.wikipedia.org/w/index.php?title=線性排序&action=edit&redlink=1)的效率
- 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位



原始的算法实现在最坏的情况下需要进行[O](https://zh.wikipedia.org/wiki/大O符号)(*n*2)的比较和交换。 V. Pratt的书[[1\]](https://zh.wikipedia.org/wiki/希尔排序#cite_note-1)对算法进行了少量修改，可以使得性能提升至O(*n* log2 *n*)。这比最好的[比较算法](https://zh.wikipedia.org/w/index.php?title=比較算法&action=edit&redlink=1)的O(*n* log *n*)要差一些。

希尔排序通过将比较的全部元素分为几个区域来提升[插入排序](https://zh.wikipedia.org/wiki/插入排序)的性能。这样可以让一个元素可以一次性地朝最终位置前进一大步。然后算法再取越来越小的步长进行排序，算法的最后一步就是普通的[插入排序](https://zh.wikipedia.org/wiki/插入排序)，但是到了这步，需排序的数据几乎是已排好的了（此时[插入排序](https://zh.wikipedia.org/wiki/插入排序)较快）。

假设有一个很小的数据在一个已按升序排好序的[数组](https://zh.wikipedia.org/wiki/數組)的末端。如果用复杂度为O(*n*2)的排序（[冒泡排序](https://zh.wikipedia.org/wiki/冒泡排序)或[插入排序](https://zh.wikipedia.org/wiki/插入排序)），可能会进行*n*次的比较和交换才能将该数据移至正确位置。而希尔排序会用较大的步长移动数据，所以小数据只需进行少数比较和交换即可到正确位置。

一个更好理解的希尔排序实现：将数组列在一个表中并对列排序（用[插入排序](https://zh.wikipedia.org/wiki/插入排序)）。重复这过程，不过每次用更长的列来进行。最后整个表就只有一列了。将数组转换至表是为了更好地理解这算法，算法本身仅仅对原数组进行排序（通过增加索引的步长，例如是用`i += step_size`而不是`i++ `）。

例如，假设有这样一组数[ 13 14 94 33 82 25 59 94 65 23 45 27 73 25 39 10 ]，如果我们以步长为5开始进行排序，我们可以通过将这列表放在有5列的表中来更好地描述算法，这样他们就应该看起来是这样：

```
13 14 94 33 82
25 59 94 65 23
45 27 73 25 39
10
```

然后我们对每列进行排序：

```
10 14 73 25 23
13 27 94 33 39
25 59 94 65 82
45
```

将上述四行数字，依序接在一起时我们得到：[ 10 14 73 25 23 13 27 94 33 39 25 59 94 65 82 45 ].这时10已经移至正确位置了，然后再以3为步长进行排序：

```
10 14 73
25 23 13
27 94 33
39 25 59
94 65 82
45
```

排序之后变为：

```
10 14 13
25 23 33
27 25 59
39 65 73
45 94 82
94
```

最后以1步长进行排序（此时就是简单的插入排序了）。

#### 图示

 {% asset_img 2.gif  image %}



### 3.选择排序（Selection Sort）

选择排序(Selection-sort)是一种简单直观的排序算法。它的工作原理：首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。

#### 算法描述

n个记录的直接选择排序可经过n-1趟直接选择排序得到有序结果。具体算法描述如下：

- 初始状态：无序区为R[1..n]，有序区为空；
- 第i趟排序(i=1,2,3…n-1)开始时，当前有序区和无序区分别为R[1..i-1]和R(i..n）。该趟排序从当前无序区中-选出关键字最小的记录 R[k]，将它与无序区的第1个记录R交换，使R[1..i]和R[i+1..n)分别变为记录个数增加1个的新有序区和记录个数减少1个的新无序区；
- n-1趟结束，数组有序化了。

#### 图示

 {% asset_img 3.gif  image %}

#### 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

void show(vector<int>& arr) {
	int size = arr.size();
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void selectionSort(vector<int>& arr) {
	int len = arr.size();
	int cur = -1, count = -1;
	cout << "Round " << ++count << ": ";
	show(arr);
	while(++cur < len-1) {
		int minIndex = cur;
		for (int i = cur+1; i < len; i++) {
			if (arr[i] < arr[minIndex]) {
				minIndex = i;
			}
		}
		swap(arr[cur], arr[minIndex]);
		cout << "Round " << ++count << ": ";
		show(arr);
	}

}

int main() {
	cout << "Please input the number of elements: ";
	int size;
	cin >> size;
	std::vector<int> arr;
	for (int i = 0; i < size; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}
	cout << "Selection sorting ..." << endl;
	selectionSort(arr);
	show(arr);
}
```



### 4.堆排序（Heap Sort）

堆排序（Heapsort）是指利用堆这种数据结构所设计的一种排序算法。堆积是一个近似完全二叉树的结构，并同时满足堆积的性质：即子结点的键值或索引总是小于（或者大于）它的父节点。

#### 算法描述

- 将初始待排序关键字序列(R1,R2….Rn)构建成大顶堆，此堆为初始的无序区；
- 将堆顶元素R[1]与最后一个元素R[n]交换，此时得到新的无序区(R1,R2,……Rn-1)和新的有序区(Rn),且满足R[1,2…n-1]<=R[n]；
- 由于交换后新的堆顶R[1]可能违反堆的性质，因此需要对当前无序区(R1,R2,……Rn-1)调整为新堆，然后再次将R[1]与无序区最后一个元素交换，得到新的无序区(R1,R2….Rn-2)和新的有序区(Rn-1,Rn)。不断重复此过程直到有序区的元素个数为n-1，则整个排序过程完成。

#### 图示

 {% asset_img 4.gif  image %}

#### 代码

```cpp
/*堆排序
1.建（大根）堆
2.堆首（最大值）和堆尾互换
3.堆的尺寸缩小1，调整大根堆
4.重复2-3
*/
#include <iostream>
#include <vector>
using namespace std;

void show(vector<int>& arr) {
	//cout << "Round " << ++count << ": ";
	int size = arr.size();
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void heapify(vector<int>& arr, int i, int n) {
	int bigIndex = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[bigIndex]) bigIndex = l;
	if (r < n && arr[r] > arr[bigIndex]) bigIndex = r;
	if (bigIndex != i) {
		swap(arr[i], arr[bigIndex]);
		heapify(arr, bigIndex, n);
	}
}

void heapSort(vector<int>& arr, int n) {
	int round = 0;
	for (int i = n-1; ~i; --i) {
		swap(arr[0], arr[i]);
		heapify(arr, 0, i);
		cout << "Round " << ++round << ": ";
		show(arr);
	}
}

void builtMaxHeap(vector<int>& arr, int n) {
	for (int i = n/2-1; ~i; i--) {
		heapify(arr, i, n);
	}
}

int main() {
	cout << "Please input the number of elements: ";
	int size;
	cin >> size;
	std::vector<int> arr;
	for (int i = 0; i < size; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}
	cout << "Built max heap..." << endl;
	builtMaxHeap(arr, size);
	cout << "Max Heap: ";
	show(arr);
	cout << "Heap sorting ..." << endl;
	heapSort(arr, size);
	show(arr);
}
```



### 5.冒泡排序（Bubble Sort）

冒泡排序是一种简单的排序算法。它重复地走访过要排序的数列，一次比较两个元素，如果它们的顺序错误就把它们交换过来。走访数列的工作是重复地进行直到没有再需要交换，也就是说该数列已经排序完成。这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端。 

#### 算法描述

- 比较相邻的元素。如果第一个比第二个大，就交换它们两个；
- 对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对，这样在最后的元素应该会是最大的数；
- 针对所有的元素重复以上的步骤，除了最后一个；
- 重复步骤1~3，直到排序完成。

#### 图示

 {% asset_img 5.gif  image %}

#### 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

void show(vector<int>& arr) {
	int size = arr.size();
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void bubbleSort(vector<int>& arr) {
	int len = arr.size();
	int right = len;
	int count = 0;
	while (right-- > 1) {
		for (int i = 1; i <= right; i++) {
			if (arr[i-1] > arr[i]) swap(arr[i-1], arr[i]);
		}
		cout << "Round " << ++count << ": ";
		show(arr);
	}
}

int main() {
	cout << "Please input the number of elements: ";
	int size;
	cin >> size;
	std::vector<int> arr;
	for (int i = 0; i < size; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}
	cout << "Bubble sorting ..." << endl;
	bubbleSort(arr);
	show(arr);
}
```



### 6.快速排序（Quick Sort）

（！！！这个需要重点掌握）

快速排序的基本思想：通过一趟排序将待排记录分隔成独立的两部分，其中一部分记录的关键字均比另一部分的关键字小，则可分别对这两部分记录继续进行排序，以达到整个序列有序。

####  算法描述

快速排序使用分治法来把一个串（list）分为两个子串（sub-lists）。具体算法描述如下：

- 从数列中挑出一个元素，称为 “基准”（pivot）；
- 重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作；
- 递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序。

#### 图示

 {% asset_img 6.gif  image %}

#### 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

void show(vector<int>& arr) {
	int size = arr.size();
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int partition(vector<int>& arr, int low, int high) {
	int target = arr[low];
	while (low < high) {
		while (low < high && arr[high] >= target) high--;
		if (arr[high] < target) arr[low++] = arr[high];
		while (low < high && arr[low] <= target) low++;
		if (arr[low] > target) arr[high--] = arr[low];
	}
	arr[low] = target;
	cout << "Round x: " ;
	show(arr);
	return low;
}

void quickSort(vector<int>& arr, int low, int high) {
	if (low < high) {
		int p = partition(arr, low, high);

		quickSort(arr, low, p-1);
		quickSort(arr, p+1, high);
	}
}

int main() {
	cout << "Please input the number of elements: ";
	int size;
	cin >> size;
	std::vector<int> arr;
	for (int i = 0; i < size; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}
	//quick sort
	cout << "Quick sorting ..." << endl;
	quickSort(arr, 0, size-1);
	show(arr);
}
```



### 7.归并排序（Merge Sort）

归并排序是建立在归并操作上的一种有效的排序算法。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为2-路归并。 

#### 算法描述

- 把长度为n的输入序列分成两个长度为n/2的子序列；
- 对这两个子序列分别采用归并排序；
- 将两个排序好的子序列合并成一个最终的排序序列。

#### 图示

 {% asset_img 7.gif  image %}

#### 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
int p = 0;
void show(vector<int>& arr, int& count) {
	cout << "Round " << ++count << ": ";
	int size = arr.size();
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void merge(vector<int>& arr, int startIndex, int midIndex, int endIndex) {
	int cur = endIndex;
	vector<int> tmp;
	for (int i = midIndex + 1; i <= endIndex; i++) tmp.push_back(arr[i]);
	int p1 = midIndex, p2 = endIndex-midIndex-1;
	
	while (~(p1-startIndex) && ~p2) {
		if (tmp[p2] < arr[p1]) arr[cur--] = arr[p1--];
		else arr[cur--] = tmp[p2--];
	}

	while (~p2) {
		arr[cur--] = tmp[p2--];
	}

	while (~(p1-startIndex)) {
		arr[cur--] = arr[p1--];
	}
	
}

void mergeSort(vector<int>& arr, int startIndex, int endIndex) {
	if (startIndex < endIndex) {
		int midIndex = startIndex + ((endIndex - startIndex) >> 1);

		mergeSort(arr, startIndex, midIndex);
		mergeSort(arr, midIndex+1, endIndex);
		
		show(arr, p);
		merge(arr, startIndex, midIndex, endIndex);
	}
}

int main() {
	cout << "Please input the number of elements: ";
	int size;
	cin >> size;
	std::vector<int> arr;
	for (int i = 0; i < size; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}
	cout << "Merge sorting ..." << endl;
	mergeSort(arr, 0, size-1);
	show(arr, p);
}
```



### 8.计数排序（Counting Sort）

计数排序不是基于比较的排序算法，其核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。 作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。

#### 算法描述

- 找出待排序的数组中最大和最小的元素；
- 统计数组中每个值为i的元素出现的次数，存入数组C的第i项；
- 对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）；
- 反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1。

#### 图示

 {% asset_img 8.gif  image %}

#### 算法分析

计数排序是一个稳定的排序算法。当输入的元素是 n 个 0到 k 之间的整数时，时间复杂度是O(n+k)，空间复杂度也是O(n+k)，其排序速度快于任何比较排序算法。当k不是很大并且序列比较集中时，计数排序是一个很有效的排序算法。



### 9.桶排序（Bucket Sort）

桶排序是计数排序的升级版。它利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定。桶排序 (Bucket sort)的工作的原理：假设输入数据服从均匀分布，将数据分到有限数量的桶里，每个桶再分别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排）。

#### 算法描述

- 设置一个定量的数组当作空桶；
- 遍历输入数据，并且把数据一个一个放到对应的桶里去；
- 对每个不是空的桶进行排序；
- 从不是空的桶里把排好序的数据拼接起来。 

#### 图示

 {% asset_img 9.png  image %}

#### 算法分析

桶排序最好情况下使用线性时间O(n)，桶排序的时间复杂度，取决与对各个桶之间数据进行排序的时间复杂度，因为其它部分的时间复杂度都为O(n)。很显然，桶划分的越小，各个桶之间的数据越少，排序所用的时间也会越少。但相应的空间消耗就会增大



### 10.基数排序（Radix Sort）

基数排序是按照低位先排序，然后收集；再按照高位排序，然后再收集；依次类推，直到最高位。有时候有些属性是有优先级顺序的，先按低优先级排序，再按高优先级排序。最后的次序就是高优先级高的在前，高优先级相同的低优先级高的在前。

#### 算法描述

- 取得数组中的最大数，并取得位数；
- arr为原始数组，从最低位开始取每个位组成radix数组；
- 对radix进行计数排序（利用计数排序适用于小范围数的特点）；

#### 图示

 {% asset_img 10.gif  image %}

#### 算法分析

基数排序基于分别排序，分别收集，所以是稳定的。但基数排序的性能比桶排序要略差，每一次关键字的桶分配都需要O(n)的时间复杂度，而且分配之后得到新的关键字序列又需要O(n)的时间复杂度。假如待排数据可以分为d个关键字，则基数排序的时间复杂度将是O(d*2n) ，当然d要远远小于n，因此基本上还是线性级别的。

基数排序的空间复杂度为O(n+k)，其中k为桶的数量。一般来说n>>k，因此额外空间需要大概n个左右。



### 参考文章

- [十大经典排序算法（动图演示）](https://www.cnblogs.com/onepixel/p/7674659.html)
- [希尔排序](https://zh.wikipedia.org/wiki/%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F)



