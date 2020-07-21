---
title: C/C++中的内存对齐
date: 2020-07-03 14:53:49
updated:
tags:
- C++
---

内存对齐这个东西我一开始也是不知道的，后来又一次面试被问到了，然后张总跟我随口普及了一下，其实还是蛮简单的，有一点点C的基础估计五分钟就能学会内存对齐的规则了。但如果你想刨根问底，为什么我们现有的计算机要内存对齐，里面的学问还是蛮深的，涉及到了处理器、寄存器这些很核心的内存硬件。

<!--more-->

### 一.引子

我们知道，任何一个数据结构在计算机内存当中要占据一定的字节(byte)数：

```cpp
cout << "type: \t\t" << "************size**************"<< endl;  
cout << "bool: \t\t" << "所占字节数：" << sizeof(bool) << endl;  
cout << "char: \t\t" << "所占字节数：" << sizeof(char) << endl;  
cout << "signed char: \t" << "所占字节数：" << sizeof(signed char) << endl;  
cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char) << endl;  
cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t) << endl;  
cout << "short: \t\t" << "所占字节数：" << sizeof(short) << endl;  
cout << "int: \t\t" << "所占字节数：" << sizeof(int) << endl;  
cout << "unsigned: \t" << "所占字节数：" << sizeof(unsigned) << endl;  
cout << "long: \t\t" << "所占字节数：" << sizeof(long) << endl;  
cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long) << endl;  
cout << "double: \t" << "所占字节数：" << sizeof(double) << endl;  
cout << "long double: \t" << "所占字节数：" << sizeof(long double) << endl;  
cout << "float: \t\t" << "所占字节数：" << sizeof(float) << endl;  
cout << "size_t: \t" << "所占字节数：" << sizeof(size_t) << endl;  
cout << "string: \t" << "所占字节数：" << sizeof(string) << endl;  
cout << "type: \t\t" << "************size**************"<< endl; 
```

output:

```cpp
type: 		************size**************
bool: 		所占字节数：1
char: 		所占字节数：1
signed char: 	所占字节数：1
unsigned char: 	所占字节数：1
wchar_t: 	所占字节数：4
short: 		所占字节数：2
int: 		所占字节数：4
unsigned: 	所占字节数：4
long: 		所占字节数：8
unsigned long: 	所占字节数：8
double: 	所占字节数：8
long double: 	所占字节数：16
float: 		所占字节数：4
size_t: 	所占字节数：8
string: 	所占字节数：24
type: 		************size**************
[Finished in 0.9s]
```

那我们来写一个class或struct

```cpp
class A
{
	char c;
	short s;
	int i;
	char ch[5];
	float f;
};
```

那一个A的对象的大小是多少呢？

1+2+4+5+4=16？

```cpp
A a;
printf("%lu\n", sizeof(a));
```

打印的结果是20.

多做几个实验，你会不会感到奇怪，sizeof的结果往往都比你声明的变量总长度要大，这是怎么回事呢？

### 二.内存（字节）对齐

网上随手一搜搜到的三个内存对齐的原则：

1. 结构体的总大小，必须要是其内部最大成员的整数倍，不足的要补齐。
2. 结构体或联合的数据成员，第一个数据成员是要放在offset == 0的地方，如果遇上子成员，要根据子成员的类型存放在对应的整数倍的地址上。
3. 如果结构体作为成员，则要找到这个结构体中的最大元素，然后从这个最大成员的整数倍地址开始存储。

对照这三个原则，我们再来看看之前的代码：

```cpp
class A
{
	char c;		// [0]-->[1] 补齐1个字节
	short s;	// [2]...[3]
	int i;		// [4]...[7]
	char ch[5];	// [8]...[12]-->[15] 补齐3个字节 (ch占8个字节 8是4的整数倍)
	float f;	// [16]...[19]
};
```

A的内部最大成员是int和float的4字节，所以内部成员在内存对齐的时候遵循4k原则，尽可能从4的整数倍的地址开始存放数据。我们再来看一个复杂点的：

```cpp
class B
{
	A a;		// [0]...[19]
	short s;	// [20]...[21]
	char c;		// [22]-->[23]
	int i;		// [24]...[27]-->[31]
	double d;	// [32]...[39]
};
```

B当中有A，也多了一个8字节的double类型，那么根据原则三，B中最大成员是8字节的double（注意不是20字节的A！），所有每个内部成员在内存对齐的时候遵循8k原则，尽可能才能够8的整数倍的地址开始存放数据。

稍微算一下，就可以得到sizeof(B)是40字节。

讲到这里相信很多人已经弄清楚了内存字节对齐是个什么回事了，但我想接着这个`class B`再分享两点

- 假如我把B里的`char c`换个位置，移到最后会发生什么呢？读者可以花上一分钟时间自行计算一下此时的B的大小。

```cpp
class B
{
	A a;		// [0]...[19]
	short s;	// [20]...[21]
	int i;		// [24]...[27]-->[31]
	double d;	// [32]...[39]
	char c;		// [40]...[47]
};
```

没错，你会发现我只是调换了一下位置，`sizeof(B)`就从40-->48了！

虽然我还没有接触过正式的C++工程开发项目，但我能感觉，在正式的项目中一定要考虑内存对齐的原则按顺序定义成员数据类型，稍微有顺序地定义成员数据类型可以提高机器内部的存储效率，积少成多，还是得注意细节问题。

- 假如我把B里的`double d`换成float类型，会发生什么改变呢？再请读者花上一分钟时间自行计算一下此时的B的大小。

```cpp
class B
{
	A a;		// [0]...[19]
	short s;	// [20]...[21]
	char c;		// [22]-->[23]
	int i;		// [24]...[27]
	float d;	// [28]...[31]
};
```

很好，如果你计算出来的结果是32说明这一块你应该已经基本掌握了。当我把double-->float，此时B的最大成员大小只有4字节，所以我们只需要遵循4k原则去对齐，从double-->float少了4个字节，但整个B少了8个字节。从这一点我又想到在定义成员变量的数据类型的时候，考虑到实际内存大小，我们不能盲目地想着用long、double这些类型一劳永逸，应该根据实际情况去选择适合实际情况的数据类型，在时间和空间中找到权衡。

### 三.#pragma pack()

假如我们不希望机器内存对齐，有办法吗？

当然有。`#pragma pack()`

该预处理指令用来改变对齐参数。在缺省情况下，C编译器为每一个变量或数据单元按其自然对界条件分配空间。一般地，可以通过下面的方法来改变缺省的对齐参数：

- 使用伪指令#pragma pack (n)，C编译器将按照n字节对齐。
-  使用伪指令#pragma pack ()，取消自定义字节对齐方式。

也可以写成：

`#pragma pack(push,n)`

`#pragma pack(pop)`

`#pragma pack (n)`表示每个成员的对齐单元**不大于**n（n为2的整数次幂）。这里规定的是上界，只影响对齐单元大于n的成员，对于对齐字节不大于n的成员没有影响。

```cpp
#pragma pack(1)
class A
{
	char c;
	short s;
	int i;
	char ch[5];
	float f;
};
class B
{
	A a;
	short s;
	char c;
	int i;
	float d;
};
class C
{
	double d;
	int i;
	short s;
	char c;
};
#pragma pack()

int main(int argc, char const *argv[])
{
	
	A a;
	B b;
	C c;
	printf("%lu\n", sizeof(a));		// 16
	printf("%lu\n", sizeof(b));		// 27
	printf("%lu\n", sizeof(c));		// 15
	return 0;
}
```



### 四.参考文章

- [内存对齐三个原则](https://www.jianshu.com/p/9441a78062f3)
- [５分钟搞定内存字节对齐](https://blog.csdn.net/hairetz/article/details/4084088)
- [C/C++ 内存对齐原则及作用](https://blog.csdn.net/chy19911123/article/details/48894579)
- [为什么要内存对齐 Data alignment: Straighten up and fly right](https://blog.csdn.net/lgouc/article/details/8235471)
- [关于内存对齐](https://blog.csdn.net/lgouc/article/details/8235616)