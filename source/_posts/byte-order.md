---
title: 浅谈字节序
date: 2020-06-29 15:38:31
updated: 2020-06-29
tags:
- 字节序
---

我记得那场面了3个小时的腾讯面试，面试官出了一道颠倒字节序的题目，当时完全不懂……昨晚看书，看到书上讲到了寻址和字节顺序，方才恍然大悟，发现还是自己书读的不够多。

<!--more-->

### 一.大小端

计算机硬件有两种储存数据的方式：大端字节序（big endian）和小端字节序（little endian）。

举例来说，数值`0x2211`使用两个字节储存：高位字节是`0x22`，低位字节是`0x11`。

> - **大端字节序**：高位字节在前，低位字节在后，这是人类读写数值的方法。
> - **小端字节序**：低位字节在前，高位字节在后，即以`0x1122`形式储存。

{% asset_img 1.jpg  image %}

同理，`0x1234567`的大端字节序和小端字节序的写法如下图。

{% asset_img 2.gif  image %}

注意，在字`0x1234567`中，高位字节的十六进制为`0x01`，而低位字节值为`0x67`。

### 二.计算机如何处理字节序

大多数的Intel兼容机都只用小端模式。另一方面，IBM和Oracle（从其2010年收购Sun Microsystems开始）的大多数机器则是按大端模式操作。但注意我们说的只是“大多数”。这些规则并没有严格按照企业界限来划分。比如IBM和Oracle制造的个人计算机使用的是Intel兼容的处理器，因此使用小端法。许多比较新的微处理器是`双端法（bi-endian）`，也就是说可以把它们配置成作为大段或小端的机器运行。然而实际情况是一旦选择了特定的操作系统，那么字节顺序也就固定下来了。例如，许多移动电话的ARM微处理器，其硬件可以按照小端或大端两种模式操作，但是这些芯片上最常见的两种操作系统——Android和iOS——却只能运行于小端模式。



显然大端法更符合人类的阅读习惯，那为什么要有小端法呢？

答案是，计算机电路先处理低位字节，效率比较高，**因为计算都是从低位开始的**。所以，计算机的内部处理都是小端字节序。

但是，人类还是习惯读写大端字节序。所以，除了计算机的内部处理，其他的场合几乎都是大端字节序，比如网络传输和文件储存。



计算机处理字节序的时候，不知道什么是高位字节，什么是低位字节。它只知道按顺序读取字节，先读第一个字节，再读第二个字节。

如果是大端字节序，先读到的就是高位字节，后读到的就是低位字节。小端字节序正好相反。

理解这一点，才能理解计算机如何处理字节序。



字节序的处理，就是一句话：

> **"只有读取的时候，才必须区分字节序，其他情况都不用考虑。"**

处理器读取外部数据的时候，必须知道数据的字节序，将其转成正确的值。然后，就正常使用这个值，完全不用再考虑字节序。

即使是向外部设备写入数据，也不用考虑字节序，正常写入一个值即可。外部设备会自己处理字节序的问题。



举例来说，处理器读入一个16位整数。如果是大端字节序，就按下面的方式转成值。

> ```cpp
> x = buf[offset] * 256 + buf[offset+1];
> ```

上面代码中，`buf`是整个数据块在内存中的起始地址，`offset`是当前正在读取的位置。第一个字节乘以256，再加上第二个字节，就是大端字节序的值，这个式子可以用逻辑运算符改写。

> ```cpp
> x = buf[offset]<<8 | buf[offset+1];
> ```

上面代码中，第一个字节左移8位（即后面添8个`0`），然后再与第二个字节进行或运算。

如果是小端字节序，用下面的公式转成值。

> ```cpp
> x = buf[offset+1] * 256 + buf[offset];
> ```

32位整数的求值公式也是一样的。

> ```cpp
> /* 大端字节序 */
> i = (data[3]<<0) | (data[2]<<8) | (data[1]<<16) | (data[0]<<24);
> 
> /* 小端字节序 */
> i = (data[0]<<0) | (data[1]<<8) | (data[2]<<16) | (data[3]<<24);
> ```

### 三.判断自己的电脑的字节序

```cpp
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int n = 10;
	printf("%x\n", n);
	char *p = (char*)&n;
	for (int i=0; i<4; ++i) {
		printf("%d %p\n", *(p+i), p+i);
	}
	if (*p==10) {
		cout << "Little-endian in this PC." << endl;
	}
	else {
		cout << "Big-endian in this PC." << endl;
	}

	int x=1;
  if (*(char *) &x ==1)
  	printf("Little endian!\n");
  else    
  	printf("Big endian!\n");
	return 0;
}
```

Output:

```cpp
a
10 0x7ffeef765b6c
0 0x7ffeef765b6d
0 0x7ffeef765b6e
0 0x7ffeef765b6f
Little-endian in this PC.
Little endian!
```

### 四.大小端的转换

```cpp
#include <iostream>
typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i=0; i<len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void*));
}

int32_t swapInt32(int32_t value) {
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24) ;
}

void read(int data) {
    printf("data is %d\n", data);
    printf("bytes order of data is");   show_int(data);
    char* pa = (char*) &data;
    int big_data = (pa[3]<<0) | (pa[2]<<8) | (pa[1]<<16) | (pa[0]<<24);
    int little_data = (pa[0]<<0) | (pa[1]<<8) | (pa[2]<<16) | (pa[3]<<24);
    printf("big_endian order data is %d\n", big_data);
    printf("little_endian order data is %d\n", little_data);
}

int main(int argc, char const *argv[])
{
    int a = 12345;
    show_int(12345);
    show_float(12345.6789);
    printf("%p\n", &a);
    show_pointer(&a);

    int data = 0x01234567;
    read(data);
    printf("--------After swap bytes order--------\n");
    data = swapInt32(data);
    read(data);
    return 0;
}
```

Output:

```cpp
 39 30 00 00
 b7 e6 40 46
0x7ffee5f20b5c
 5c 0b f2 e5 fe 7f 00 00
data is 19088743
bytes order of data is 67 45 23 01
big_endian order data is 1732584193
little_endian order data is 19088743
--------After swap bytes order--------
data is 1732584193
bytes order of data is 01 23 45 67
big_endian order data is 19088743
little_endian order data is 1732584193
```

### 五.参考文章

- [理解字节序](https://www.ruanyifeng.com/blog/2016/11/byte-order.html)
- 深入理解计算机系统
- [请简述大端字节序和小端字节序的概念，设计一个小程序来判断当前机器的字节 序](https://blog.csdn.net/qq_37941471/article/details/81301536?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase)
- [【百度笔试题】简述大小端字节序的概念并写一个小程序检测当前机器的大小端字节序](https://blog.csdn.net/bitzhidu/article/details/106332088)
- [［c/c++ ］字节序与大小端转换](https://blog.csdn.net/kuai0705/article/details/20841133)
- [C/C++ 大小端理解及转换](https://blog.csdn.net/sunboyiris/article/details/77574566)

