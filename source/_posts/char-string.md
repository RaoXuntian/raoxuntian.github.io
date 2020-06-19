---
title: 浅谈C/C++中的char和string
date: 2020-06-19 00:52:03
tags:
- char
- string
- C
- C++
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

所以一个signed char的范围为-128~127，unsigned char的范围为0~255。

我们在计算机上看到的汉字、英文等字符是每个字符通过二进制转换的结果，为什么是二进制呢，因为计算机中储存的信息都是用二进制数表示的。

#### 2.什么是字符集

字符集是多个字符的集合，比如数字，字母，符号等，

