---
title: 浅谈C++关键字之volatile
date: 2020-09-25 00:03:10
updated:
tags:
- C++
---

学了C++那么久，发现还是有英语单词不认识。volatile，从英语的角度来看，是什么意思呢？在网上用谷歌翻译，得到的是「易挥发的」，也有的翻译成「易变的」。但仅仅这些对于我们去理解这个单词是不够的，对于翻译来说，很多时候目标语言很难找到一个词能够反映源语言中单词的全部含义和细节。

### 单词volatile的含义

Volatile 的意思，若要详细理解，还是应该查阅权威的英英字典。在柯林斯高阶学习词典中，volatile 是这样解释的：

<!--more-->

> A situation that is volatile is likely to change suddenly and unexpectedly.

这里对 volatile 的解释有三个精髓的形容词和副词，体现了 volatile 的含义。

- likely：可能的。这意味着被 volatile 形容的对象「有可能也有可能不」发生改变，因此我们不能对这样的对象的状态做出任何假设。
- suddenly：突然地。这意味着被 volatile 形容的对象可能发生瞬时改变。
- unexpectedly：不可预期地。这与 likely 相互呼应，意味着被 volatile 形容的对象可能以各种不可预期的方式和时间发生更改。

因此，volatile 其实就是告诉我们，被它修饰的对象出现任何情况都不要奇怪，我们不能对它们做任何假设。

### 程序中volatile的含义

对于程序员来说，程序本身的任何行为都必须是可预期的。那么，在程序当中，什么才叫 volatile 呢？这个问题的答案也很简单：程序可能受到程序之外的因素影响。

考虑以下 C/C++ 代码。

```
volatile int *p = /* ... */;
int a, b;
a = *p;
b = *p;
```

若忽略 `volatile`，那么 `p` 就只是一个「指向 `int` 类型的指针」。这样一来，`a = *p;` 和 `b = *p;` 两句，就只需要从内存中读取一次就够了。因为从内存中读取一次之后，CPU 的寄存器中就已经有了这个值；把这个值直接复用就可以了。这样一来，编译器就会做优化，把两次访存的操作优化成一次。这样做是基于一个假设：我们在代码里没有改变 `p` 指向内存地址的值，那么这个值就一定不会发生改变。

> 此处说的「读取内存」，包括了读取 CPU 缓存和读取计算机主存。

然而，由于 MMIP（Memory mapped I/O）的存在，这个假设不一定是真的。例如说，假设 `p` 指向的内存是一个硬件设备。这样一来，从 `p` 指向的内存读取数据可能伴随着**可观测的副作用**：硬件状态的修改。此时，代码的原意可能是将硬件设备返回的连续两个 `int` 分别保存在 `a` 和 `b` 当中。这种情况下，编译器的优化就会导致程序行为不符合预期了。

总结来说，被 `volatile` 修饰的变量，在对其进行读写操作时，会引发一些**可观测的副作用**。而这些可观测的副作用，是由**程序之外的因素决定的**。



```c
#include <stdio.h>
  
int main(void)
{
  const volatile int local = 10;
  int *ptr = (int*) &local;
  printf("Initial value of local : %d \n", local);
  *ptr = 100;
  printf("Modified value of local: %d \n", local);

  const int a = 10;
  int *pa = (int*)&a;
  printf("a = %d \n" , a);
  *pa = 20;
  printf("a = %d \n" , a);
  return 0;
}

/* output
Initial value of local : 10 
Modified value of local: 100 
a = 10 
a = 10 
*/
```



### 参考文章

- [谈谈 C/C++ 中的 volatile](https://liam.page/2018/01/18/volatile-in-C-and-Cpp/)
- [C++ volatile用法](https://blog.csdn.net/lxiao428/article/details/83830983)
- https://light-city.club/sc/basic_content/volatile/