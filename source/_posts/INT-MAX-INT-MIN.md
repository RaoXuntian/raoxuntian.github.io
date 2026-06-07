---
title: 浅谈C/C++整型上下限INT_MAX和INT_MIN及其运算
date: 2020-06-28 23:31:59
updated: 2020-06-28
tags:
- C++
- C
---

今天在刷题的时候，遇到几道关于处理32位有符号整数的题目：[7.整数反转](https://leetcode-cn.com/problems/reverse-integer/)和 [8.字符串转换整数 (atoi)](https://leetcode-cn.com/problems/string-to-integer-atoi/)。题目看起来不算很难，但如果在面试时遇到这样的题目，想想面试官是要考察你什么？考察你用long抖机灵吗？考察你会捕获异常吗？我想应该是要考察你对C/C++中整型的上下限的理解以及这方面的细节处理。

<!--more-->

### 一.整型数据类型和数据大小

说到整型数据类型，很多人第一反应就是int。

int占4个字节，1个字节通常是占8位，所以一个int占32位，根据二进制编码规则，int最大是2^32-1(2147483647)，最小是-2^32(-2147483648)。

除了int还有吗？

在C当中：

| C声明         |                | 字节数 |      |
| ------------- | -------------- | ------ | ---- |
| 有符号        | 无符号         | 32位   | 64位 |
| [signed] char | unsigned char  | 1      | 1    |
| short         | unsigned short | 2      | 2    |
| int           | unsigned       | 4      | 4    |
| long          | unsigned long  | 4      | 8    |
| int32_t       | uint32_t       | 4      | 4    |
| int64_t       | uint64_t       | 8      | 8    |
| char*         |                | 4      | 8    |
| float         |                | 4      | 4    |
| double        |                | 8      | 8    |

我们只讨论整数类型，整数我们可以分为两种类型，一种是**有符号**的，这种可以表示负数、零和正数；另一种是**无符号**的，这种只能表示非负数。

在32位程序上，C语言整型数据类型的典型取值范围如下：

| C数据类型      | 最小值               | 最大值               |
| -------------- | -------------------- | -------------------- |
| [signed] char  | -128                 | 127                  |
| unsigned char  | 0                    | 255                  |
| short          | -32768               | 32767                |
| unsigned short | 0                    | 65535                |
| int            | -2147483648          | 2147483647           |
| unsigned       | 0                    | 4294967295           |
| long           | -2147483648          | 2147483647           |
| unsigned long  | 0                    | 4294967295           |
| int32_t        | -2147483648          | 2147483647           |
| uint32_t       | 0                    | 4294967295           |
| int64_t        | -9223372036854775808 | 9223372036854775807  |
| uint64_t       | 0                    | 18446744073709551615 |

在64位程序上，C语言整型数据类型的典型取值范围如下：

| C数据类型      | 最小值               | 最大值               |
| -------------- | -------------------- | -------------------- |
| [signed] char  | -128                 | 127                  |
| unsigned char  | 0                    | 255                  |
| short          | -32768               | 32767                |
| unsigned short | 0                    | 65535                |
| int            | -2147483648          | 2147483647           |
| unsigned       | 0                    | 4294967295           |
| long           | -9223372036854775808 | 9223372036854775807  |
| unsigned long  | 0                    | 18446744073709551615 |
| int32_t        | -2147483648          | 2147483647           |
| uint32_t       | 0                    | 4294967295           |
| int64_t        | -9223372036854775808 | 9223372036854775807  |
| uint64_t       | 0                    | 18446744073709551615 |

通过上面两张表我们可以注意到，有符号的整型的取值范围是不对称的——负数的范围比整数的范围大1。这个原因是计算机在用二进制表示负数的时候用到了**补码编码**，最前面一位是符号位，就不在这里啰嗦了……

C语言标准定义了每种数据类型必须能够表示的最小取值范围：

| C数据类型      | 最小值               | 最大值               |
| -------------- | -------------------- | -------------------- |
| [signed] char  | -127                 | 127                  |
| unsigned char  | 0                    | 255                  |
| short          | -32767               | 32767                |
| unsigned short | 0                    | 65535                |
| int            | -32767               | 32767                |
| unsigned       | 0                    | 65535                |
| long           | -2147483647          | 2147483647           |
| unsigned long  | 0                    | 4294967295           |
| int32_t        | -2147483648          | 2147483647           |
| uint32_t       | 0                    | 4294967295           |
| int64_t        | -9223372036854775808 | 9223372036854775807  |
| uint64_t       | 0                    | 18446744073709551615 |

C++中的整型类型和范围如下：

| 类型               | 位            | 范围                                                         |
| ------------------ | ------------- | ------------------------------------------------------------ |
| char               | 1 个字节      | -128 到 127 或者 0 到 255                                    |
| unsigned char      | 1 个字节      | 0 到 255                                                     |
| signed char        | 1 个字节      | -128 到 127                                                  |
| int                | 4 个字节      | -2147483648 到 2147483647                                    |
| unsigned int       | 4 个字节      | 0 到 4294967295                                              |
| signed int         | 4 个字节      | -2147483648 到 2147483647                                    |
| short int          | 2 个字节      | -32768 到 32767                                              |
| unsigned short int | 2 个字节      | 0 到 65,535                                                  |
| signed short int   | 2 个字节      | -32768 到 32767                                              |
| long int           | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| signed long int    | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| unsigned long int  | 8 个字节      | 0 到 18,446,744,073,709,551,615                              |
| float              | 4 个字节      | 精度型占4个字节（32位）内存空间，+/- 3.4e +/- 38 (~7 个数字) |
| double             | 8 个字节      | 双精度型占8 个字节（64位）内存空间，+/- 1.7e +/- 308 (~15 个数字) |
| long double        | 16 个字节     | 长双精度型 16 个字节（128位）内存空间，可提供18-19位有效数字。 |
| wchar_t            | 2 或 4 个字节 | 1 个宽字符                                                   |

其实 wchar_t 是这样来的：

```cpp
typedef short int wchar_t;
```

所以 wchar_t 实际上的空间是和 short int 一样。

**注意：**不同系统会有所差异，一字节为 8 位。

**注意：**long int 与 int 都是 4 个字节，因为早期的 C 编译器定义了 long int 占用 4 个字节，int 占用 2 个字节，新版的C/C++ 标准兼容了早期的这一设定。

> C和C++都支持有符号（默认）和无符号数，Java只支持有符号数

### 二.INT_MAX和INT_MIN

我们已经知道了C/C++中一个int占32位，于是为了方便表示int类型的范围，于是在头文件limits.h中，用常量INT_MAX和INT_MIN分别表示最大、最小整数。

```cpp
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)
//這裏沒有簡單地將INT_MIN賦值成-2147483647，是因為-2147483648對於編譯器而言是個表達式，
//而2147483648對於32-bit整數是無法表示的，所以經過這個表達式的結果是未定義的。
//在GCC上直接寫-2147483648後，編譯器給出了警告，說結果是unsigned。
```

在C/C++語言中，不能夠直接使用-2147483648來代替最小負數，因為這不是一個數字，而是一個表達式。表達式的意思是對整數21473648取負，但是2147483648已經溢出了int的上限，所以定義為（-INT_MAX -1）。

记住INT_MAX和INT_MIN的定义，在后面的运算中很重要。

我们用二进制来表示INT_MAX和INT_MIN：

```cpp
INT_MAX == 0b01111111111111111111111111111111;	// 31个1
INT_MIN == 0b10000000000000000000000000000000;	// 31个0
```

### 三.运算

当我们弄清楚了INT_MAX和INT_MIN的本质之后再来谈谈他们的运算。

整数的运算离不开二进制编码的原码、补码和反码这些规则，所以当在刷算法题涉及到INT_MAX和INT_MIN时我们应该对边界情况考虑周到，考虑溢出的情况，当发生溢出的时候，就不会遵循数学规则了。

**INT_MAX + 1 = INT_MIN**

**INT_MIN - 1 = INT_MAX**

**abs(INT_MIN) = INT_MIN**

前两条对比二进制做加减法就能一目了然，那么第三条abs()这个怎么解释呢？别忘了`#define INT_MIN (-INT_MAX - 1)` 所以`abs(INT_MIN)`也就是`abs(-INT_MAX - 1)`，结果就是`INT_MAX+1`，还是`INT_MIN`。

同理，`-INT_MIN == INT_MIN`。

那么我们可以达到另外一种下溢：

**INT_MIN + INT_MIN = 0**

将上式中的`INT_MIN`用`INT_MAX+1`进行替换，我们就得到了另一种上溢：

**INT_MAX + INT_MAX = -2**

总结一下：

1. 最轻微的上溢是INT_MAX + 1 :结果是 INT_MIN; 
2. 最严重的上溢是INT_MAX + INT_MAX :结果是-2; 
3. 最轻微的下溢是INT_MIN - 1:结果是是INT_MAX; 
4. 最严重的下溢是INT_MIN + INT_MIN:结果是0 。

### 四.代码

```cpp
#include <iostream>

using namespace std;

int main() {
	int i = 0b10000000000000000000000000000000;
	int j = 0b01111111111111111111111111111111;
	cout << (i == INT_MIN) << endl;
	cout << (j == INT_MAX) << endl;
	cout << "-INT_MIN = " << -INT_MIN << endl; 
	cout << "INT_MIN = " << INT_MIN << endl;
	cout << "INT_MIN/10 = " << INT_MIN/10 << endl;
	cout << "INT_MIN%10 = " << INT_MIN%10 << endl;
	cout << "-INT_MIN%10 = " << -INT_MIN%10 << endl;
	cout << "-(INT_MIN%10) = " << -(INT_MIN%10) << endl;
	cout << "INT_MAX + INT_MAX = " << INT_MAX + INT_MAX << endl;
	cout << "INT_MIN + INT_MIN = " << INT_MIN + INT_MIN << endl;
	return 0;
}

```

Output:

```cpp
/Users/saladdays/Projects/Learn_CPP/INT/int.cpp:16:44: warning: overflow in expression; result is -2 with type 'int' [-Winteger-overflow]
        cout << "INT_MAX + INT_MAX = " << INT_MAX + INT_MAX << endl;
                                                  ^
/Users/saladdays/Projects/Learn_CPP/INT/int.cpp:17:44: warning: overflow in expression; result is 0 with type 'int' [-Winteger-overflow]
        cout << "INT_MIN + INT_MIN = " << INT_MIN + INT_MIN << endl;
                                                  ^
2 warnings generated.
1
1
-INT_MIN = -2147483648
INT_MIN = -2147483648
INT_MIN/10 = -214748364
INT_MIN%10 = -8
-INT_MIN%10 = -8
-(INT_MIN%10) = 8
INT_MAX + INT_MAX = -2
INT_MIN + INT_MIN = 0
```



### 五.参考文章

- 深入理解计算机系统
- [C++数据类型](https://www.runoob.com/cplusplus/cpp-data-types.html)
- [INT_MIN和INT_MAX註意事項 //C++](https://www.itread01.com/content/1534661783.html)
- [Why -INT_MIN is NOT 2147483648 for uint64_t type](https://stackoverflow.com/questions/54292185/why-int-min-is-not-2147483648-for-uint64-t-type)
- [C/C++中int型上下限INT_MAX INT_MIN以及溢出](https://blog.csdn.net/weixin_42372777/article/details/83092086)

