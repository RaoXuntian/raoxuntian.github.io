---
title: 浅谈C++的智能指针
date: 2020-08-22 00:08:24
updated:
tags:
- C++
- 指针
---

智能指针作为C++11里的新特征，有可能在面试里被问到。本文主要介绍C++里的三个智能指针：`shared_ptr`、`unique_ptr`、`weak_ptr`。其实还有一种`auto_ptr`指针，但在C++11里已经被弃用了，故此我们不做讨论了。

<!--more-->

### 为什么要用智能指针

我们知道C++的内存分配主要有三个大区：

一个是**静态（static）存储区**，用来保存局部的static对象、类static数据成员以及定义在任何函数之外的变量。

一个是**栈（stack）内存**，用来保存定义在函数内的非static对象。

分配在静态或栈内存中的对象由编译器自动创建和销毁。对于栈对象，仅在其定义的程序块运行时才存在；static对象在使用之前分配，在程序结束时销毁。

#### 动态内存

除了静态存储区和栈内存，每个程序还有一个内存池。这部分内存被称作**自由空间（free store）**或**堆（heap）**。程序用来存储**动态分配**的对象——即，那些程序在运行时分配的对象。动态分配的对象的生存期有程序来控制，也就是说动态对象不再使用的时候，我们的代码必须显式地销毁它们。

C++中，我们使用一堆运算符来管理动态内存：`new`/`delete`。在C中是`malloc`/`free`，不要搞混了。

每次我们new一个对象，会在动态内存中为对象分配空间然后返回一个指向该对象的指针，当不用这个对象的时候，我们delete这个动态对象的指针，销毁对象，并释放与之关联的内存。

#### 存在的问题

使用new/delete容易出现问题，最常见的就是**内存泄露**。如何理解内存泄露？凡是new出来的对象没有及时合理的delete释放掉，都有可能造成内存泄漏的问题。

随便举个例子：

```cpp
{
  int* p = new int(1037);
}
```

我们在程序块内定义了一个int指针p指向堆空间的一块int内存，并初始化为1037。如果我们在程序块内部没有`delete p`，那么离开程序块之后，栈上的指针p就会被销毁，而堆上的那个1037并不会随之释放，直到程序结束也没有办法释放，因为在程序块里就只有p指向1037，p销毁后，这块地址就“失踪”了，就找不到这块地址了，所以无法释放，导致内存泄露。

还有，

```cpp
string *p = new string(6, '6');
string *q = p;
delete p;
p = nullptr;
```

我们定义了一个字符串指针p指向“666666”，然后让另一个字符串指针q也指向p所指的区域，然后我们delete了p，随之释放了堆上的“666666”，那么q呢？指了个寂寞……此时q不一定是空指针（nullptr），而是无效指针（可能会指向奇怪的值）。在实际系统中，查找指向相同内存的所有指针是异常困难的。

这里需要再解释一下指针p，在我们delete p之后，指针值就无效了。虽然指针值已经无效了，但在很多机器上指针仍然保存着（已经释放了的）动态内存的地址。在delete之后，指针就变成了人们所说的**空悬指针（dangling pointer）**，即，指向一块曾经保存数据对象但现在已经无效的内存的指针。如果我们在delete p之后还需要保留指针p的话，可以在delete之后将nullptr赋值给指针p，这样就清楚地指出指针p不指向任何对象。

总之，如果频繁地使用new/delete，一旦代码业务逻辑复杂起来，我们或多或少会遇到内存泄露相关的问题，为了尽可能的避免此类问题，**智能指针**就出来了。智能指针是一个类，当超出了这个类的作用域时，类会自动调用析构函数，析构函数会自动释放资源。下面我们逐个介绍各种智能指针。

### shared_ptr

从名字share就可以看出了资源可以被多个指针共享，它使用计数机制来表明资源被几个指针共享。可以通过成员函数use_count()来查看资源的所有者个数。出了可以通过new来构造，还可以通过传入auto_ptr, unique_ptr,weak_ptr来构造。当我们调用release()时，当前指针会释放资源所有权，计数减一。当计数等于0时，资源会被释放。

 {% asset_img 1.png  image %}

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct A
{
private:
	int val_;
public:
	A():val_(0){cout << "A()" << endl;};
	A(int val):val_(val){cout << "A(" << val_ << ")" << endl;};
	~A(){cout << "~A(" << val_ << ")" << endl;};
	void print() {cout << "This is a test~ " << val_ << endl;};
};

int main(int argc, char const *argv[])
{
	shared_ptr<int> p1(new int(42));
	//auto p2=std::make_shared<vector<int> > ();
	shared_ptr<vector<int>> p2(new vector<int>{1,2,3});

	auto p4 = new A(13);
	shared_ptr<A> p3(p4);
	shared_ptr<A> p5=make_shared<A>(24);
	auto p6(p3);

	cout << p3.use_count() << endl;
	p5.reset(); // 主动销毁p5
	p3.reset(new A); // reset里参数必须是原始指针 p3指向新的地址 原地址销毁
	// std::shared_ptr::reset() function required a raw pointer as parameter.
	//p5=p4;
	cout << *p1 << endl;
	cout << p2->at(0) << " " << p2->at(1) << " " << p2->at(2) << endl;
	p3->print();
	
	return 0;
}

/*
output:
A(13)
A(24)
2
~A(24)
A()
42
1 2 3
This is a test~ 0
~A(13)
~A(0)
*/
```

 {% asset_img 2.png  image %}

 {% asset_img 3.png  image %}

### unique_ptr

unique_ptr,**是用于取代c++98的auto_ptr的产物**,在c++98的时候还没有移动语义(move semantics)的支持,因此对于auto_ptr的控制权转移的实现没有核心元素的支持,但是还是实现了auto_ptr的移动语义,这样带来的一些问题是拷贝构造函数和复制操作重载函数不够完美,具体体现就是把auto_ptr作为函数参数,传进去的时候控制权转移,转移到函数参数,当函数返回的时候并没有一个控制权移交的过程,所以过了函数调用则原先的auto_ptr已经失效了.在c++11当中有了移动语义,使用move()把unique_ptr传入函数,这样你就知道原先的unique_ptr已经失效了.移动语义本身就说明了这样的问题,比较坑爹的是标准描述是说对于move之后使用原来的内容是未定义行为,并非抛出异常,所以还是要靠人肉遵守游戏规则.再一个,auto_ptr不支持传入deleter,所以只能支持单对象(delete object),而unique_ptr对数组类型有偏特化重载,并且还做了相应的优化,比如用[]访问相应元素等。

unique_ptr 是一个独享所有权的智能指针，它提供了严格意义上的所有权，包括：

1、拥有它指向的对象

2、无法进行复制构造，无法进行复制赋值操作。即无法使两个unique_ptr指向同一个对象。但是可以进行移动构造和移动赋值操作

3、保存指向某个对象的指针，当它本身被删除释放的时候，会使用给定的删除器释放它指向的对象

unique_ptr 可以实现如下功能：

1、为动态申请的内存提供异常安全

2、讲动态申请的内存所有权传递给某函数

3、从某个函数返回动态申请内存的所有权

4、在容器中保存指针

5、auto_ptr 应该具有的功能

 {% asset_img 4.png  image %}

```cpp
unique_ptr<string> p6(new string("hahahaha!!!"));
// unique_ptr<string> p6_error(p6); // ERROR: unique_ptr不支持拷贝
unique_ptr<string> p6_error;
// p6_error=p6; // ERROR: unique_ptr不支持赋值
cout << *p6 << endl;
unique_ptr<string> p7(p6.release());	// release将p6置空
unique_ptr<string> p8(new string("XXXDDD"));
cout << "*p7 == " << *p7
<< "\t*p8 == " << *p8 << endl;
// 将所有权从p8转移给p7
p7.reset(p8.release());	// reset释放了p7原来的指向的内存
cout << "*p7 == " << *p7 << endl;
	
/*
hahahaha!!!
*p7 == hahahaha!!!	*p8 == XXXDDD
*p7 == XXXDDD
*/
```



### weak_ptr

weak_ptr是用来解决shared_ptr相互引用时的死锁问题,如果说两个shared_ptr相互引用,那么这两个指针的引用计数永远不可能下降为0,资源永远不会释放。它是对对象的一种弱引用，不会增加对象的引用计数，和shared_ptr之间可以相互转化，shared_ptr可以直接赋值给它，它可以通过调用lock函数来获得shared_ptr。



### 参考文章

- C++ Primer 5th
- [c++ 智能指针用法详解](https://www.cnblogs.com/TenosDoIt/p/3456704.html)