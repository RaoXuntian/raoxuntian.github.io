---
title: C/C++程序内存的各种变量存储区域和各个区域详解
date: 2020-07-02 14:16:29
updated:
tags:
- C++
---

C/C++程序内存中各种变量的存储区域划分是C++面试时常问的一个问题，别的公司我不太清楚，至少某讯是挺爱问的……甚至面试官在面试的时候跟我说，“好的，你能说出这个三个区域就可以了，后面就不做要求了……”。之前看过[一篇博客](https://blog.csdn.net/jirryzhang/article/details/79518408)写的很详细，每次面试前临时背一背，现在不想背了，自己过一遍，画一画图加强理解吧。

<!--more-->

### 一.预备知识—程序的内存分配 

一个由C/C++编译的程序占用的内存分为以下几个部分

1. 栈区（stack）— 程序运行时由编译器自动分配，存放函数的参数值，局部变量的值等。

   其操作方式类似于数据结构中的栈。

2. 堆区（heap） — 在内存开辟另一块存储区域。

   一般由程序员分配释放，若程序员不释放，程序结束时可能由OS回收。

   注意它与数据结构中的堆是两回事，分配方式倒是类似于链表。

3. 全局区（静态区）（static）—编译器编译时即分配内存。   

   全局变量和静态变量的存储是放在一块的，

   **初始化**的全局变量和静态变量在一块区域，

   **未初始化**的全局变量和未初始化的静态变量在相邻的另一块区域。 

   （在C++中，由于全局变量和静态变量编译器会给这些变量自动初始化赋值，所以没有区分了）

   程序结束后由系统释放。

4. 文字常量区 —常量字符串就是放在这里的。 程序结束后由系统释放。

5. 程序代码区—存放函数体的二进制代码。




注意：静态局部变量和静态全局变量

属于静态存储方式的量不一定就是静态变量。 

例如：全局变量虽属于静态存储方式，但不一定是静态变量，

必须由 static加以定义后才能成为静态外部变量，或称静态全局变量。

把局部变量改变为静态变量后是改变了它的存储方式，即改变了它的生存期。
把全局变量改变为静态变量后是改变了它的作用域，限制了它的使用范围。

### 二.动&静

一个程序被加载到内存中，这块内存首先就存在两种**属性**：静态分配内存和动态分配内存。 
静态分配内存：是在程序编译和链接时就确定好的内存。 
动态分配内存：是在程序加载、调入、执行的时候分配/回收的内存。

**Text & Data & Bss**

- .text： 也称为代码段(Code)，用来存放程序执行代码，同时也可能会包含一些常量(如一些字符串常量等）。该段内存为静态分配，只读(某些架构可能允许修改)。 
  这块内存是共享的,当有多个相同进程(Process)存在时，共用同一个text段。

- .data： 也有的地方叫GVAR(global value)，用来存放程序中已经初始化的非零全局变量。静态分配。

  ​	data又可分为读写（RW）区域和只读（RO）区域。 
  ​	-> RO段保存常量所以也被称为.constdata 
  ​	-> RW段则是普通非常全局变量，静态变量就在其中

- .bss： 存放程序中为初始化的和零值全局变量。静态分配，在程序开始时通常会被清零。


text和data段都在可执行文件中，由系统从可执行文件中加载；而bss段不在可执行文件中，由系统初始化。 
这三段内存就组成了我们编写的程序的本体，但是一个程序运行起来，还需要更多的数据和数据间的交互，否则这个程序就是死的，无用的。所以我们还需要为更多的数据和数据交互提供一块内存——堆栈。

**堆栈（Heap& Stack）**
堆和栈都是动态分配内存，两者空间大小都是可变的。

- Stack： 栈，存放Automatic Variables，按内存地址由高到低方向生长，其最大大小由编译时确定，速度快，但自由性差，最大空间不大。


- Heap： 堆，自由申请的空间，按内存地址由低到高方向生长，其大小由系统内存/虚拟内存上限决定，速度较慢，但自由性大，可用空间大。 
  每个线程都会有自己的栈，但是堆空间是共用的。

### 三.代码

```cpp
#include<iostream>
using namespace std;

int global_i = 0;	// global_i在全局（初始化）区

char* global_p;		// global_p在全局（未初始化）区

int main(int argc, char const *argv[])
{
	printf("&global_i = %p\n", &global_i);
	printf("&global_p = %p\n", &global_p);
	printf("global_p = %p\n", global_p);

	static int static_i = 1;	// 全局静态区
	int i = 2;	// 	栈
	const int const_i = 3;	// 栈
	
	char p1[] = "HUST";		// p1在栈，"HUST"在常量区
	const char *p2 = "Computer Science";	// p2在栈，"Computer Science"在常量区
	global_p = new char(10);	
	// 指针变量global_p依然在全局区，但在堆上开辟了10个char长度的空间，global_p的值是堆上开辟空间的首地址
	char* p3 = new char(20);	
	// 这行代码在Heap中开辟了20个char长度的空间，同时在Stack上压入了p3，
	// 指针变量p3存在于栈上，其值为刚刚在堆上开辟的空间的首地址。
	
	printf("&static_i = %p\n", &static_i);
	printf("&i = %p\n", &i);
	printf("&const_i = %p\n", &const_i);

	printf("&p1 = %p\n", &p1);
	printf("&p2 = %p\n", &p2);
	printf("%lu\n", sizeof(p2));
	printf("p1 = %p\n", p1);
	printf("p2 = %p\n", p2);

	printf("&global_p = %p\n", &global_p);
	printf("global_p = %p\n", global_p);
	printf("&p3 = %p\n", &p3);
	printf("p3 = %p\n", p3);
	return 0;
}
```

output:

```cpp
&global_i = 0x10e6a0020
&global_p = 0x10e6a0028
global_p = 0x0
&static_i = 0x10e6a0018
&i = 0x7ffee15618ac
&const_i = 0x7ffee15618a8
&p1 = 0x7ffee15618a3
&p2 = 0x7ffee1561898
8
p1 = 0x7ffee15618a3
p2 = 0x10e69ef3a
&global_p = 0x10e6a0028
global_p = 0x7fc593c05850
&p3 = 0x7ffee1561890
p3 = 0x7fc593c05860
[Finished in 0.9s]
```

粗略地画了个草图……

{% asset_img 1.jpg  image %}

在全局静态区的有`global_p`，`global_i`，`static_i`，其中`global_i`，`static_i`是int类型，所以1个int数据直接在全局区占4字节存数据，而`global_p`是char类型的指针，一开始没有初始化，C++默认初始化为零指针，指向`0x00`，但指针变量`global_p`是在全局区上，后面new分配了地址，才指向了堆区。

在栈上的有`i`，`const_i`，`p1`，`p2`，`p3`，其中`i`，`const_i`都是int，所以int数据之间存在栈上，但他们也有区别，加了const变量说明这块区域是不能“修改”的，你无法再给`const_i`重新赋值；`p1`是数组名，将常量区的`"HUST\0"`五个字符复制拷贝给p1数组，所以你会发现`p1`和`const_i`之间刚好有5个字节；`p2`是const char*，是指针，占8个字节，但如果仔细的算一下，你会发现，`p2`和`p1`之间有11个字节，好像对不上？其实不光这里对不上，你会发现在全局区里的int只占4个字节，但相邻int之间隔了8个字节，以及后面堆区上的`global_p`明明只分配10个字节，却和相邻区域隔了整整16个字节，其实这是C++里的**内存对齐**规则，遵循4k/8k原则，这里不多说了。

堆上的就是`global_p`和`p3`分配的空间，注意一下栈和堆的地址高低，等会要讲……

常量区上的就是`p2`指向的常量，通过地址可以看得出来，常量区的地址和全局区很近，和堆栈区隔得比较远，那么这些区域在计算机内存中到底是如何分布的呢？

### 四.图解

在 sw-at 的博客上扒了一张图，这张图中所示内存空间，地址由下往上增长，分别标示了 .text、.data、.bss、stack和heap的内存分部情况。 
我们可以看到：

- text、data(gvar)、bss 在内存中地址较低低的位置（low level address），而堆栈则在相对较搞的位置。
- 堆(Heap)往高地址方向生长，栈(Stack)往低地址方向生长。

{% asset_img 2.jpg  image %}

在C\C++中，通常可以把内存理解为4个分区：栈、堆、全局/静态存储区和常量存储区。下面我们分别简单地介绍一下各自的特点。

**1 栈**
        通常是用于那些在编译期间就能确定存储大小的变量的存储区，用于在函数作用域内创建，在离开作用域后自动销毁的变量的存储区。通常是局部变量，函数参数等的存储区。他的存储空间是连续的，两个紧密挨着定义的局部变量，他们的存储空间也是紧挨着的。栈的大小是有限的，通常Visual C++编译器的默认栈的大小为1MB，所以不要定义int a[1000000]这样的超大数组。

**2 堆**
        通常是用于那些在编译期间不能确定存储大小的变量的存储区，它的存储空间是不连续的，一般由malloc（或new）函数来分配内存块，并且需要用free（delete）函数释放内存。如果程序员没有释放掉，那么就会出现常说的内存泄漏问题。需要注意的是，两个紧挨着定义的指针变量，所指向的malloc出来的两块内存并不一定的是紧挨着的，所以会产生内存碎片。另外需要注意的一点是，堆的大小几乎不受限制，理论上每个程序最大可达4GB。

**3 全局/静态存储区**
        和“栈”一样，通常是用于那些在编译期间就能确定存储大小的变量的存储区，但它用于的是在整个程序运行期间都可见的全局变量和静态变量。

**4 常量存储区**
        和“全局/静态存储区”一样，通常是用于那些在编译期间就能确定存储大小的常量的存储区，并且在程序运行期间，存储区内的常量是全局可见的。这是一块比较特殊的存储去，他们里面存放的是常量，不允许被修改。

### 五.总结

 根据上面的内容，分别将栈和堆、全局/静态存储区和常量存储区进行对比，结果如下。

**表1 栈和堆的对比**

|                      | 栈                       | 堆                       |
| -------------------- | ------------------------ | ------------------------ |
| 存储内容             | 局部变量                 | 变量                     |
| 作用域               | 函数作用域、语句块作用域 | 函数作用域、语句块作用域 |
| 编译期间大小是否确定 | 是                       | 否                       |
| 大小                 | 1MB                      | 4GB                      |
| 内存分配方式         | 地址由高向低减少         | 地址由低向高增加         |
| 内容是否可以修改     | 是                       | 是                       |

**表2 全局/静态存储区和常量存储区的对比**

|                      | 全局/静态存储区    | 常量存储区 |
| -------------------- | ------------------ | ---------- |
| 存储内容             | 全局变量、静态变量 | 常量       |
| 编译期间大小是否确定 | 是                 | 是         |
| 内容是否可以修改     | 是                 | 否         |

l          栈区：主要用来存放局部变量, 传递参数, 存放函数的返回地址。.esp 始终指向栈顶, 栈中的数据越多, esp的值越小。

l          堆区：用于存放动态分配的对象, 当你使用 malloc和new 等进行分配时,所得到的空间就在堆中。动态分配得到的内存区域附带有分配信息, 所以你能够 free和delete它们。

l          数据区：全局，静态和常量是分配在数据区中的，数据区包括bss（未初始化数据区）和初始化数据区。

注意：

1）     堆向高内存地址生长；

2）     栈向低内存地址生长；

3）     堆和栈相向而生，堆和栈之间有个临界点，称为stkbrk。



全局区可以在编译期间确定大小，那么我们可以应该想到，**static const**关键词不光可以作为类的静态常量属性，还可以作为预编译声明。

当作为**预编译声明**时，static const 属性必须在声明时即指定值，而且类型仅限基本数据类型。

```cpp
class A
{  
	static const int a =1;   
}
```

此时相当于C语言中的 `#define a 1` 宏定义了一个宏变量a，但是C++的这种方式比C的#define的优势在于，**可以对类型进行检查和限制，减少了编译期间因为类型隐式转换而造成的潜在风险**。

此时的static const常量既不存在于动态区也不存在于静态区（应该是存在于常量区或代码区），而是由编译器在编译期间就直接进行了值替换。也因为这个原因不可以对其进行取地址操作，因为它根本没有地址。


关于这些区域存取的效率，我们可以分析这样两行代码：

```cpp
char s1[] = "aaaaaaaaaaaaaaa"; 
char *s2 = "bbbbbbbbbbbbbbbbb"; 
```

aaaaaaaaaaa是在运行时刻赋值给s1的，存在栈上； 
而bbbbbbbbbbb是在编译时就确定的，存在常量区； 

但是，在以后的存取中，在栈上的数组比指针所指向的字符串(例如堆)快。 

栈是机器系统提供的数据结构，计算机在底层提供支持，分配有专门的堆栈段寄存器，入栈出栈有专门的机器指令，这些都决定了栈的高效率执行。

堆是由C/C++函数库提供的，机制比较复杂，有不同的分配算法，易产生内存碎片，需要对内存进行各种管理，效率比栈要低很多。

堆和栈的区别可以用如下的比喻来看出： 
使用栈就象我们去饭馆里吃饭，只管点菜（发出申请）、付钱、和吃（使用），吃饱了就走，不必理会切菜、洗菜等准备工作和洗碗、刷锅等扫尾工作，他的好处是快捷，但是自由度小。 
使用堆就象是自己动手做喜欢吃的菜肴，比较麻烦，但是比较符合自己的口味，而且自由度大。

### 六.参考文章

- [C/C++程序内存的各种变量存储区域和各个区域详解](https://blog.csdn.net/jirryzhang/article/details/79518408)
- [c/c++内存机制（一）（转）](https://www.cnblogs.com/zhoug2020/p/10520341.html)
- [c/c++内存机制（一）（原）](https://www.cnblogs.com/ComputerG/archive/2012/02/01/2334898.html)
- [C/C++ 全局变量和局部变量在内存里的区别？堆和栈](https://blog.csdn.net/qq_33266987/article/details/51965221)
- [C++ 常量区 静态区 堆区 栈区](https://blog.csdn.net/LYKXHTP/article/details/88877930)
