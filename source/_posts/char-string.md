---
title: 浅谈C/C++中的char和string
date: 2020-06-19 00:52:03
tags:
- char
- string
- C
- C++
- 指针
---

很想写一篇文章来谈一下C/C++中的char和string，顺带也可以说一下python中的string，因为我学习语言的顺序是先学了C再学python然后学C++，一开始对这两个数据类型并没有很敏感，前几天在用C写代码的时候，发现在使用char *和char ch[]的时候有些模糊，而且在给它们初始化或者赋值的时候也会出错。在传统的C里面，我们可以初始化一个定长的char数组，但不能直接给一个定长的char数组赋值：

```c
char ch[20] = "Hello,world!";	// valid
char sh[20]；
sh = "Hello,world!";	// invalid
```

编译器会提示你：

<!--more-->

`array type 'char [20]' is not assignable`

这个时候我们需要用到**strcpy()**函数，它存在于string.h头文件当中，使用前你需要include这个头文件。

```c
char sh[20]；
sh = "Hello,world!";	// invalid
strcpy(sh, "Hello,world!");	// valid
```

### 一.char类型详解

#### 1.char与字符的关系

在C/C++中，char是定义一个字符，存储一个字符，占一个字节(byte)，在内存中占8位(bit)。

我们需要知道这个知识点，在计算机中，通常8位代表一个字节，即1byte = 8bits。

所以一个signed char的范围为-128-127，unsigned char的范围为0-255。

计算机通常用二进制存储信息，所以我们在计算机上看到的汉字、英文等字符是二进制数转换的结果。那么有时候我们在打开一个网页或文件的时候，显示一堆乱码是什么情况呢？这就需要探讨一下不同的字符集。

#### 2.什么是字符集

**字符集**(charset)是一个系统支持的所有抽象字符的集合。字符是各种文字和符号的总称，包括各国家文字、标点符号、图形符号、数字等。常见的字符集比如ASCII码，它是由美国ANSI制定的，主要包括控制字符（回车键、退格、换行键等）和可显示字符（英文大小写字符、阿拉伯数字和西文符号）。

```c
for (int i=32; i<128; ++i) {
  printf("[%3d -> %c] ", i, i);
  if (i%10==0) printf("\n");
}
```

打印的结果如下：

```bash
[ 32 ->  ] [ 33 -> !] [ 34 -> "] [ 35 -> #] [ 36 -> $] [ 37 -> %] [ 38 -> &] [ 39 -> '] [ 40 -> (] 
[ 41 -> )] [ 42 -> *] [ 43 -> +] [ 44 -> ,] [ 45 -> -] [ 46 -> .] [ 47 -> /] [ 48 -> 0] [ 49 -> 1] [ 50 -> 2] 
[ 51 -> 3] [ 52 -> 4] [ 53 -> 5] [ 54 -> 6] [ 55 -> 7] [ 56 -> 8] [ 57 -> 9] [ 58 -> :] [ 59 -> ;] [ 60 -> <] 
[ 61 -> =] [ 62 -> >] [ 63 -> ?] [ 64 -> @] [ 65 -> A] [ 66 -> B] [ 67 -> C] [ 68 -> D] [ 69 -> E] [ 70 -> F] 
[ 71 -> G] [ 72 -> H] [ 73 -> I] [ 74 -> J] [ 75 -> K] [ 76 -> L] [ 77 -> M] [ 78 -> N] [ 79 -> O] [ 80 -> P] 
[ 81 -> Q] [ 82 -> R] [ 83 -> S] [ 84 -> T] [ 85 -> U] [ 86 -> V] [ 87 -> W] [ 88 -> X] [ 89 -> Y] [ 90 -> Z] 
[ 91 -> [] [ 92 -> \] [ 93 -> ]] [ 94 -> ^] [ 95 -> _] [ 96 -> `] [ 97 -> a] [ 98 -> b] [ 99 -> c] [100 -> d] 
[101 -> e] [102 -> f] [103 -> g] [104 -> h] [105 -> i] [106 -> j] [107 -> k] [108 -> l] [109 -> m] [110 -> n] 
[111 -> o] [112 -> p] [113 -> q] [114 -> r] [115 -> s] [116 -> t] [117 -> u] [118 -> v] [119 -> w] [120 -> x] 
[121 -> y] [122 -> z] [123 -> {] [124 -> |] [125 -> }] [126 -> ~] [127 -> ]
```

传统的128个ASCII码有33个是控制字符(0-31, 127)，是不可显示的，剩下的都是可显示字符。

除了ASCII码之外，还有GBxxxx(汉字编码字符集)，Unicode(**统一码**、**万国码**、**单一码**、**标准万国码**)。

#### 3.如何表示字符

通俗的说，按照何种规则将字符存储在计算机中，如'a'用什么表示，称为"**编码**"；反之，将存储在计算机中的二进制数解析显示出来，称为"**解码**"，如同密码学中的加密和解密。

汉字的编码标准，GBK；Unicode的编码标准，UTF。

在解码过程中，如果使用了错误的解码规则，则导致'a'解析成'b'或者乱码。

#### 4.C++中的字符类型

C++提供了几种字符类型，并非只有8bits的char。比如我们熟知的ASCII码，在这种字符集系统上C++的字节确实是8位，然而在国际编程中采用更大的字符集比如Unicode等时，8位组合无法表示所有字符，因此一个字节可能需要16位甚至更多，在这种系统上，C++中的一个字节可能就不是代表8bit了，这是C++对字节的定义，这里我们一定不能搞混淆了。

| 类型     | 含义        | 最小尺寸 |
| -------- | ----------- | -------- |
| char     | 字符        | 8位      |
| wchar_t  | 宽字符      | 16位     |
| char16_t | Unicode字符 | 16位     |
| char32_t | Unicode字符 | 32位     |

其他字符集用于扩展字符集，如wchar_t、char16_t、char32_t。wchar_t类型用于确保可以存放机器最大扩展字符集中的任意一个字符，类型char16_t和char32_t则为Unicode字符集服务。

### 二.char数组和char指针的区别和联系

在C语言中，对字符串的操作主要有两种方式，一是字符数组(char[])，二是使用字符指针(char*)。

#### 1.char数组

```c
char a[] = {'h','e','l','l','o','~'};
char c[] = "hello~";
char ch[10] = "Hello~";

printf("%lu\n", sizeof(a));
for (int i=0; i<sizeof(a); ++i) {
	printf("%c ", a[i]);
}
printf("\n%lu\n", sizeof(c));
for (int i=0; i<sizeof(c); ++i) {
	printf("%c ", c[i]);
}
printf("\n%lu\n", sizeof(ch));
for (int i=0; i<sizeof(ch); ++i) {
	printf("%c ", ch[i]);
}

```

{% asset_img 1.png  image %}

这张图可以很明显看出来不同方式声明并初始化char数组的效果是不同的。

第一种 `char a[] = {'h','e','l','l','o','~'};` 声明了一个char数组，不知道分配多大空间，根据右边的字符数组初始化char数组来确定最终的分配空间，给了6个字符，分配了6个sizeof(char)；

第二种 `char c[] = "hello~";` 也是声明了一个不知道分配多少空间的char数组，但使用字符串字面值(string literal)初始化char数组之后，实际分配的空间比我们看到的字符串面值的要多一个<0x00>，也表示为'\0'；

第三种 `char ch[10] = "Hello~";`  声明了长度为10的char数组，**编译器为该数组分配了10个单位的内存**，然后初始化，多余没有用到的内存就用'\0'填充，如果初始化的字符串字面值长度比分配的内存长，则会报错。

但C语言不允许我们直接声明一个不知道会分配多少内存空间的char数组，

```c
char a[];	// invalid
```

char[]经过初始化后就会变成有固定长度的char数组。

但这个时候我们如果想给char数组重新赋值，

```c
char ch[10];
ch = "World!";	// invalid
// error: array type 'char [6]' is not assignable
strcpy(ch, "World!");	// valid
```

我们要怎么去理解上面这个操作呢？

我记得我在大一学C语言的时候，老师讲过说，**数组名可以理解为指向这个数组的指针**。那既然是指针为什么不能给这个指针重新赋值呢？

很简单，数组名是数组名，指针是指针，他们是不能划等号的，老师说的是让你理解成指针，并不是说数组名就是指针！！！

有个很简单的方法可以证明，你就看`sizeof(a)`。

指针是指向一个内存地址的对象，无论是void *，char *还是int * ，C语言中指向各种数据的指针大小是一致的，在64位的机器上，**占8个字节**，32位的机器上是4个字节。

```c
char* p;
char ch[10] = "hello~";
int a[4] = {1,0,3,7};
int* pa = &a[0];
printf("sizeof(p)==%lu\n", sizeof(p));
printf("sizeof(ch)==%lu\n", sizeof(ch));
printf("sizeof(pa)==%lu\n", sizeof(pa));
printf("sizeof(a)==%lu\n", sizeof(a));

// sizeof(p)==8
// sizeof(ch)==10
// sizeof(pa)==8
// sizeof(a)==16
```

通过看sizeof()的大小，我们可以发现数组名并不是指针，那数组名到底是什么呢？它和指针又有什么关系呢？

那我们不如来看一下他们的“庐山真面目”：

```c
p = ch;
printf(" p ==%p\n", p);
printf("ch ==%p\n", ch);
printf("&p ==%p\n", &p);
printf("&ch==%p\n", &ch);

printf(" a ==%p\n", a);
printf("pa ==%p\n", pa);
printf("&a ==%p\n", &a);
printf("&pa==%p\n", &pa);

//  p ==0x7ffeec66e8f4
// ch ==0x7ffeec66e8f4
// &p ==0x7ffeec66e8a8
// &ch==0x7ffeec66e8f4
//  a ==0x7ffeec66e8e0
// pa ==0x7ffeec66e8e0
// &a ==0x7ffeec66e8e0
// &pa==0x7ffeec66e8a0
```

通过上面的打印结果我们可以看到，指针指向的地址和存放这个指针的地址是不一样的，而数组名指向的地址和数组名所在的地址是一样的……听着有点绕，其实已经很清楚了：

ch数组名代表的就是char数组第一个元素地址的值，但**它不是指针**，只是对应着（而不是指向）一块内存，是个常量(const)，常量是不可以修改的，所以我们是不能给这个常量去赋值。

简言之，**数组名是一个地址，而非指针，虽然两者数值相同，但是不是同一个东西。**

**所以我们要记住，数组名只是代表数组第一个元素的地址的值，比如数组 `int a[10]`，`a`实际上就是 `&a[0]`，它只是一个值，就像 `5` 这类东西一样，是不能作为左值的，不能给它赋值。**

我想把数组名的真相继续深究下去，就拿`char ch[10];`来说，ch不是「指向char的指针」类型，ch是「长度为10的char数组」类型；&ch也不是「指向指针的指针」类型，而是「指向长度为10的char数组的指针」类型，虽然ch和&ch的值是一样的，但他们是完全不同的类型，不可混淆。

```c
char* p1 = &ch;	// invalid
// error: cannot initialize a variable of type 'char *' with an rvalue of type 'char (*)[10]'
char* p1 = &ch[0];	// valid
char (*p2)[10] = &ch;	// valid:p2是指向长度为10的char数组的指针
printf("%c\n", p2[0][1]);
printf("%c\n", (*p2)[1]);
```

虽然p2看起来像个二维数组，但我们还是要弄清楚他们的本质是不一样的，因为二维数组是数组的数组，而p2是数组的指针。

以上，除了**sizeof(ch)**和**&ch**以外，其余的情况下，ch可以看成指向首地址的指针，可以看成char* 类型。

```c
ch[1] = 'E';
printf("%s\n", ch);

// hEllo~
```



#### 2.char指针

当我们使用char指针来定义一个字符串的时候，

```c
char* p0 = "C++!!!";

// warning: conversion from string literal to 'char *' is deprecated [-Wc++11-compat-deprecated-writable-strings]
```

把这个warning转换成中文的意思是：“警告：不建议将字符串文字转换为'char *'[-Wc ++ 11-compat-deprecated-writable-strings]”。

虽说是个warning，说明执行是没有问题的，但后面提示说这个语法不推荐使用(deprecated)，这是为什么呢？

在继续讲之前我们需要说一下C/C++的内存分配，内存分配是面试时候面试官问的高频问题。当我们定义一个字符串数组char a[]，这是属于静态分配，建立的静态数组，它是在**栈空间分配内存**；而动态方式使用new或malloc，是在**堆上分配内存**。string literal(字符串字面值)是常量(const)，常量存储在**常量区**，常量的字符串一般存在常量区，程序结束后由系统释放。

我们再回过头来看上面的定义和初始化语句：`char* p0 = "C++!!!";` p0在栈上，而字符串常量”C++!!!\0“在常量区。我们可以这么理解，我们在栈上定义了一个指针p0，这个时候并没有为其分配内存，同时在常量区分配了一块内存放字符串常量"C++!!!\0"，然后让p0指向常量区这块内存的首地址。听起来没有问题，但为什么会有warning？

主要问题还是在于等号右边的这个string literal，它是个const啊，[const是不能修改的](https://raoxuntian.github.io/2020/06/03/learnCpp-const/) (可以回顾一下这篇文章)。我们不能用一个简单的pointer去指向一个const，得用pointer to const，这样指针所指向的对象才是常量，不可变的。

所以正确的写法应该是

```c
const char* p0 = "C++!!!";	// valid
p0 = "JAVA~";	// valid: 这里并没有修改*p0的值，而是把p0重新指向了"JAVA~"
*p0 = "Python...";	// invalid: read-only variable is not assignable
p0[1] = 'a';	// invalid: read-only variable is not assignable
```

这种情况下我们并不好去修改p0所指向的字符串的值，这个时候我们可以想起数组……

```c
char ch[] = "Gooooo";
//char* p1 = &ch;	// invalid
//char* p1 = ch;	// valid: 当数组名作为右值的时候，我们可以简单理解为数组的指针
char* p1 = &ch[0];	// valid
p1[3] = 'O';
printf("%s\n", ch);
strcpy(p1, "Golang");
printf("%s %s\n", p1, ch);

// GooOoo
// Golang Golang
```

### 三.string和char的区别

刚刚我们谈了关于char的很多东西，那么string和char又有什么关系呢？

在C++ primer一书中有介绍说，char字符属于C++的基本内置类型，包括前面说的wchar_t、char16_t和char32_t，都是primitive type（原始类型）。而在C++里。string是作为标准库类型，成为了一个类(class)，封装在string头文件里，当我们使用string类时，需要先include< string >，string表示的是可变长的字符序列。

关于string的语法我后面会再写一篇文章来记录，就不在此多说了，发表一下个人看法，有了string类之后，可以弥补之前char指针和char数组在字符串相关操作的不足，然而，熟悉C++语法的人也知道，string类也不只是封装了个char数组这么简单。虽说string中重载了各种操作符，还有各种find函数，给我们带来便利，但我们也不能忽视在复杂环境或多线程下频繁处理string类时的安全性，string不是万能的，不管是在C++还是Python当中，你使用时没有发生错误只是因为你只走到了这一步，并不意味它真的是完美(perfect)的。

顺带说一笔Python中的string吧，Python中有五个标准的数据类型：

- Numbers（数字）

- String（字符串）

- List（列表）

- Tuple（元组）

- Dictionary（字典）

  

  没错。Python没有char类型，所以在Python中，`str = "Hello~"`和`str = 'Hello~'`是没有区别的，str都是字符串，而在C/C++中，字符串或者char数组对应的需要用双引号来表示，而字符对应的需要用单引号来表示，如果你`char c = "C"`，那这就是错的。

### 四.相关文章

- [C++中char类型详解](https://blog.csdn.net/Sylvernass/article/details/44604459)
- [字符集和字符编码（Charset & Encoding）](https://www.cnblogs.com/skynet/archive/2011/05/03/2035105.html)
- [C 语言里为什么这样初始化字符串是错误的？](https://segmentfault.com/q/1010000003793687)
- [char数组与char指针的区别与联系](https://blog.csdn.net/self_mind/article/details/49705227)
- [知乎：c中，数组名跟指针有区别吗？](https://www.zhihu.com/question/41805285)
- [Conversion from string literal to 'char *' is deprecated 问题原因](https://blog.csdn.net/wangtie_123/article/details/9629111)
- [C++ 数组在内存中的分配](https://blog.csdn.net/u011555996/article/details/79496156)
- [c/c++中string与char的区别](https://blog.csdn.net/yejinxiong001/article/details/78436310)

## 五.文章中的源码

```c
#include <cstdio>
#include <cstring>
int main(int argc, char const *argv[])
{
	
	{	// ASCII码
		for (int i=32; i<128; ++i) {
			printf("[%3d -> %c] ", i, i);
			if (i%10==0) printf("\n");
		}
	}
	
	{
		char a[] = {'h','e','l','l','o','~'};
		char c[] = "hello~";
		char ch[10] = "Hello~";

		printf("%lu\n", sizeof(a));
		for (int i=0; i<sizeof(a); ++i) {
			printf("%c ", a[i]);
		}
		printf("\n%lu\n", sizeof(c));
		for (int i=0; i<sizeof(c); ++i) {
			printf("%c ", c[i]);
		}
		printf("\n%lu\n", sizeof(ch));
		for (int i=0; i<sizeof(ch); ++i) {
			printf("%c ", ch[i]);
		}
		
		strcpy(a, "world");
		strcpy(ch, "world");
		printf("\n%s %s\n", a, ch);
		printf("%p %p %p\n", a, c, ch);
	}
	
	{
		char* p;
		char ch[10] = "hello~";
		int a[4] = {1,0,3,7};
		int* pa = &a[0];
		printf("sizeof(p)==%lu\n", sizeof(p));
		printf("sizeof(ch)==%lu\n", sizeof(ch));
		printf("sizeof(pa)==%lu\n", sizeof(pa));
		printf("sizeof(a)==%lu\n", sizeof(a));
		
		p = ch;
		printf(" p ==%p\n", p);
		printf("ch ==%p\n", ch);
		printf("&p ==%p\n", &p);
		printf("&ch==%p\n", &ch);

		printf(" a ==%p\n", a);
		printf("pa ==%p\n", pa);
		printf("&a ==%p\n", &a);
		printf("&pa==%p\n", &pa);

		//char* p1 = &ch;
		char* p1 = &ch[0];
		char (*p2)[10] = &ch;
		printf("%c\n", p2[0][1]);
		printf("%c\n", (*p2)[1]);

		ch[1] = 'E';
		printf("%s\n", ch);
	}

	{
		//char* p0 = "C++!!!";
		const char* p0 = "C++!!!";
		p0 = "JAVA~";
		//*p0 = "Python...";
		//p0[1] = 'a';
		char ch[] = "Gooooo";
		//char* p1 = &ch[0];
		char* p1 = ch;
		p1[3] = 'O';
		printf("%s\n", ch);
		strcpy(p1, "Golang");
		printf("%s %s\n", p1, ch);
	}
	return 0;
}
```

