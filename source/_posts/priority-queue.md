---
title: priority_queue
date: 2020-09-03 19:29:24
updated:
tags:
- 优先队列
- 堆
- datastruct
---

优先队列虽然名字叫队列，但它的内部其实是由一个**堆**来维护其排序的。

既然名字叫做队列，那么使用它就要先包含头文件`#include<queue>`，优先队列和普通队列的不同就在于我们可以自定义优先队列内部数据的优先级，让优先级高的排在前面，优先出队。

优先队列具有队列的所有特性，包括基本操作，只是在这基础上添加了内部的一个排序，它本质是一个堆实现的。

<!--more-->

> 和队列基本操作相同:
>
> - top 访问队头元素
> - empty 队列是否为空
> - size 返回队列内元素个数
> - push 插入元素到队尾 (并排序)
> - emplace 原地构造一个元素并插入队列
> - pop 弹出队头元素
> - swap 交换内容

### 定义

定义：`priority_queue<Type, Container, Functional>`
*Type* 就是数据类型，*Container* 就是容器类型（Container必须是用数组实现的容器，比如vector,deque等等，但不能用 list。STL里面默认用的是vector），*Functional* 就是比较的方式，当需要用自定义的数据类型时才需要传入这三个参数，使用基本数据类型时，只需要传入数据类型，默认是大顶堆
一般是：

```cpp
//升序队列
priority_queue <int,vector<int>,greater<int> > q;
//降序队列
priority_queue <int,vector<int>,less<int> >q;

//greater和less是std实现的两个仿函数（就是使一个类的使用看上去像一个函数。其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了）
```

### 使用

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	//对于基础类型 默认是大顶堆
    priority_queue<int> a; 
    //等同于 priority_queue<int, vector<int>, less<int> > a;
    
    //             这里一定要有空格，不然成了右移运算符↓
    priority_queue<int, vector<int>, greater<int> > c;  //这样就是小顶堆
    priority_queue<string> b;

    std::vector<int> v{1,2,9,8,4,0,-5};

    for (size_t i=0; i<v.size(); ++i) {
    	a.push(v[i]);
    	c.push(v[i]);
    }

    while (!a.empty()) {
        cout << a.top() << ' ';
        a.pop();
    } 
    cout << endl;

    while (!c.empty()) {
        cout << c.top() << ' ';
        c.pop();
    }
    cout << endl;

    b.push("abc");
    b.push("abcd");
    b.push("cbd");
    while (!b.empty()) 
    {
        cout << b.top() << ' ';
        b.pop();
    } 
    cout << endl;
    
	return 0;
}

//9 8 4 2 1 0 -5 
//-5 0 1 2 4 8 9 
//cbd abcd abc
```



### 堆排序

我们需要捋清楚堆排序的过程，这就涉及到堆的插入和删除。

下面我们以大根堆为例讲一下大概过程，太懒了就不画图了 = =

#### 堆的插入

需要插入的节点首先加入到堆的二叉树最后的一个节点，依据最大堆的定义，自底向上，递归调整。

#### 堆的删除

 对于最小堆和最大堆而言，删除是针对于根节点而言。

 对于删除操作，将二叉树的最后一个节点替换到根节点，然后自顶向下，递归调整。

附上[最小堆 构建、插入、删除的过程图解](https://blog.csdn.net/hrn1216/article/details/51465270)

那我们用代码去实现堆排序的步骤也可以简单的分为以下几步：

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

这样大根堆建立起来的优先队列就是数值从小到大的优先顺序。

所以一定要记好，**升序序列是大根堆，降序序列是小根堆。**

今天华为二面的时候，面试官问我如何从一组乱序的数组中得到topK的数集。我自作聪明分了两种情况讨论，大数据和普通数据量用不同的方法。普通数据量的话可以把数据一次性全部放进内存，那么我们就可以用内部排序中的快排思想，但不需要像快排一样把每个子集都迭代快排。因为每次迭代过后会有一个“哨兵”的位置是确定的，那么“哨兵”前面的元素数值都比“哨兵”大，同理，后面的都比“哨兵”小。**我们的目的是取topK，不需要那K个数值有序**，所以只要通过几次快排迭代过后确定了第K大的数字位置，那么就可以得到topK的数集了。

大数据的话数据不能一次性放进内存，那我们就把数据分成若干份，每一份用长度为K的优先队列过滤得到topK，然后把过滤后的每一份topK数据组合起来再分成更少的份数，每一份取topK，直到最后一份所有的数据都可以加载到内存中，直接取topK。

然鹅，面试官问了一句，你的优先队列是什么堆啊，大根堆还是小根堆？

当时有点忘了，凭感觉是大根堆，但感觉是错的……面试官说了句你结束后再去了解一下吧。当时心里咯噔一下，知道自己答错了。

所以啊，数据结构这种东西，一定要多看看多画图好好理解，都是基础……

### 参考文章

- [c++优先队列(priority_queue)用法详解](https://blog.csdn.net/weixin_36888577/article/details/79937886)
- [最小堆 构建、插入、删除的过程图解](https://blog.csdn.net/hrn1216/article/details/51465270)