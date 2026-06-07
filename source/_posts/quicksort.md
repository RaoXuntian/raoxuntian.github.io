---
title: 快速排序
date: 2020-08-31 23:22:51
updated:
tags:
- 排序
---

快排这个东西真的不想说什么，刷面经常常看到会有面试官考察快排的代码，我一直觉得这种事情不会发生在我身上，没想到上周滴滴面试还是发生了。而且，我之前写过好几次快排的代码，然而面试时脑子一篇空白，没有按时写出来……并且像面试官问了一个巨他妈愚蠢的问题：现在的语言都有sort这种已经非常完善的排序算法，为什么还要造轮子手撕快排。面试官说：**其实让你们写快排的代码并不是要你们造轮子取代那些排序算法，而是通过快排这个我们都知道原理的过程来看看你的code基本功，能不能把这个我们都知道的思路复现出来。**

简单点说，写不出来就是菜鸡了。看完这篇文章，拒绝做菜鸡！

<!--more-->

先看一道leetcode上的medium级别的题目：

[215. 数组中的第K个最大元素](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)

> 在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
>
> 示例 1:
>
> 输入: [3,2,1,5,6,4] 和 k = 2
> 输出: 5
> 示例 2:
>
> 输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
> 输出: 4
> 说明:
>
> 你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。
>

这个题有很多思路，用python刷题的同学不要sort一下直接返回nums[k-1]，这样学不到东西的。

清楚快排原理的同学应该不难想到这道题可以用快排的思想，但我们又不需要将每一段都排序，只需要确定好第k-1个位置的数就行，那个数就是第k大的数。

考虑到局部有序的情况，我们在选择参照数的时候，可以用一下随机数选取参照数。

代码如下：

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSort(nums, 0, nums.size()-1, k-1);
    }

    int quickSort(vector<int>& nums, int l, int r, int k) {
        int p=randomPartition(nums, l, r);
        if (p==k) return nums[p];
        else return p<k?quickSort(nums, p+1, r, k):quickSort(nums, l, p-1, k);
    };

    int randomPartition(vector<int>& nums, int l, int r) {
        int p=rand()%(r-l+1)+l;
        swap(nums[p], nums[r]);
        return partition(nums, l, r);
    }

    int partition(vector<int>& nums, int l, int r) {
        int x=nums[r], i=l-1;
        for (int j=l; j<=r; ++j) {
            if (nums[j]>x) {
                swap(nums[++i], nums[j]);
            }
        }
        swap(nums[++i], nums[r]);
        return i;
    }
};
```



由这个算法我们应该可以把快排的代码完整写出来了：

```cpp
#include <iostream>
#include <vector>

int partition(std::vector<int>& arr, int l, int r) {
	int x=arr[r], i=l-1;
	for (int j=l; j<=r; ++j) {
		if (arr[j]<x) {
			std::swap(arr[++i], arr[j]);
		}
	}
	std::swap(arr[++i], arr[r]);
	return i;
}

void quickSort(std::vector<int>& arr, int l, int r) {
	if (l>r) return ;
	int p=partition(arr, l, r);
	quickSort(arr, l, p-1);
	quickSort(arr, p+1, r);
}

int main(int argc, char const *argv[])
{
	std::vector<int> arr={8,7,6,3,5,4,1,2,9,0};
	quickSort(arr, 0, arr.size()-1);
	for (int i:arr) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}
```

基本功也好，八股文也罢，快排写不出来确实尴尬。

奇技淫巧，唯手熟尔。