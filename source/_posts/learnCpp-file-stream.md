---
title: C++中的文件和流
date: 2020-08-17 00:24:04
updated:
tags:
- C++
---

最近在牛客网刷题，和leetcode不一样，牛客网需要要自己控制从键盘输入变量。另外在实习的时候，碰巧页遇到几个C++读写文件的问题，之前都是直接网上搜索code，这几天抽空研究了这一块，发现无论是从键盘输入字符串还是从读取文件，都可以采用“流”的思想去理解。

<!--more-->

### 一、stream家族

回忆一下我们敲打的第一个C/C++程序，打印“hello,world!"，无论是C还是C++，都不能像python和PHP这些脚步语言直接`pirnt("hello,world!");` ，而是要先`#include XXX`。C中是`#include <stdio.h>`，C++是`#include <iostream>`。熟悉C的小伙伴应该清楚，`stdio.h`是C当中的标准输入输出的头文件，只有在代码的开头加上`#include <stdio.h>`，你的代码才能使用`printf`和`scanf`这些输出和输入的函数，这里我们不展开讨论C的细节，我们来看看C++的`iostream`。

#### iostream

C++里的`#include`后面没有`.h`后缀，C++包含的不叫头文件，是**库**。导入了`iostream`库我们才可以使用`cin`和`cout`去输入和输出。`iostream`的意思是输入输出流，直接点说就是in（输入） out（输出） stream（流），取in、out的首字母与stream合成。

iostream 库的基础是两种命名为 istream 和 ostream 的类型,分别表示输入流和输出流。流是指要从某种 IO 设备上读出或写入的字符序列。术语“流”试图说明字符是随着时间顺序生成或消耗的。

标准库定义了 4 个 IO 对象。处理输入时使用命名为 cin(读作 see-in)的 istream 类型对象。这个对象也称为标准输入。处理输出时使用命名为 cout(读作 see-out)的 ostream 类型对象,这个对象也称为标准输出。标准库还定义了另外两个 ostream 对象,分别命名为 cerr 和 clog(分别读作“see-err”和“see-log”)。cerr 对象又叫作标准错误,通常用来输出警告和错误信息给程序的使用者。而 clog 对象用于产生程序执行的一般信息。

#### fstream

和`iostream`相似的还有`fstream`，文件流。而`ofstream` 和 `ifstream`是两个继承自`fstream`的两个类，他们能够重新定义文件输入输出流。他们的关系如下图所示：

 {% asset_img 1.gif  image %}

```cpp
#include <fstream>
ofstream         //文件写操作 内存写入存储设备 
ifstream         //文件读操作，存储设备读区到内存中
fstream          //读写操作，对打开的文件可进行读写操作
```



### 二、键盘输入

#### cin

这个对象不用多说了，大家都会，只是需要注意

```cpp
string s;
cin >> s;
// 如果从键盘输入 "abc def"
s = "abc";
```

`cin`在遇到空格、‘\t’、回车这些符号会停止读取流。

所以当我们如果需要读取一整行的时候可以考虑`getline`函数

#### getline

`getline()`函数是一个比较常见的函数。根据名字直接"望文->生义"，就知道这个函数是来完成读入一行数据。

下面就对C++ -- getline()函数的用法说明，以及`getline()`函数作为while条件的问题，总结一下：

在C++中本质上有两种`getline`函数，（称为第一种）一种在库`<istream>`中，是`istream`类的成员函数。

（称为第二种）一种在头文件`<string>`中，是普通函数。



第一种： 在`<istream>`中的getline()函数有两种重载形式：

```cpp
istream& getline (char* s, streamsize n );

istream& getline (char* s, streamsize n, char delim );
```

作用是： 从`istream`中读取至多n个字符(包含结束标记符)保存在s对应的数组中。即使还没读够n个字符，

如果遇到`delim`或字数达到限制，则读取终止，`delim`都不会被保存进s对应的数组中。

 

第二种： 在`<string>`中的`getline`函数有四种重载形式：

```cpp
istream& getline (istream&  is, string& str, char delim);

istream& getline (istream&& is, string& str, char delim);

istream& getline (istream&  is, string& str);

istream& getline (istream&& is, string& str);
```

用法和上第一种类似，但是读取的istream是作为参数is传进函数的。读取的字符串保存在string类型的str中。

函数的变量：

`is`  ：表示一个输入流，例如cin。

`str`  ：string类型的引用，用来存储输入流中的流信息。

`delim` ：char类型的变量，所设置的截断字符；在不自定义设置的情况下，遇到’\n’，则终止输入。



回忆一下`cin`的`getline`用法

我们可以

```cpp
string s;
char ch[256];
cin.getline(ch, 256)
getline(cin, s, '\t');
```

两种`getline`函数有一个地方需要注意，第一种函数的参数是字符数组(char*)，第二种函数的参数是字符串（string类）

关于`string`和`char*`的转换有个函数是`c_str()`，可以参考[这篇文章](https://www.cnblogs.com/devilmaycry812839668/p/6353807.html)。

还需要注意 getline需要的是输入流，`istream`类的对象，`cin`这些都可以，但如果是`fstream`就不行。

 另外 `getline(file, buffer, '\t');` 并不是执行完之后文件指针file会指向下一行，而是在'\t'的后面一位

`getline(file, buffer);` 是读完一整行。

#### ignore

`cin.ignore(a,ch)`方法是从输入流（cin）中提取字符，提取的字符被忽略（ignore），不被使用。每抛弃一个字符，它都要计数和比较字符：如果计数值达到a或者被抛弃的字符是ch，则cin.ignore()函数执行终止；否则，它继续等待。它的一个常用功能就是用来清除以回车结束的输入缓冲区的内容，消除上一次输入对下一次输入的影响。比如可以这么用：`cin.ignore(1024,’\n’)`，通常把第一个参数设置得足够大，这样实际上总是只有第二个参数’\n’起作用，所以这一句就是把回车（包括回车）之前的所以字符从输入缓冲（流）中清除出去。

### 三、读取文件

从文本读取文件分三个步骤，打开文件，读写文件，关闭文件。

#### 打开文件

在从文件读取信息或者向文件写入信息之前，必须先打开文件。**ofstream** 和 **fstream** 对象都可以用来打开文件进行写操作，如果只需要打开文件进行读操作，则使用 **ifstream** 对象。

下面是 open() 函数的标准语法，open() 函数是 fstream、ifstream 和 ofstream 对象的一个成员。

```
void open(const char *filename, ios::openmode mode);
```

在这里，**open()** 成员函数的第一参数指定要打开的文件的名称和位置，第二个参数定义文件被打开的模式。

| 模式标志   | 描述                                                         |
| :--------- | :----------------------------------------------------------- |
| ios::app   | 追加模式。所有写入都追加到文件末尾。                         |
| ios::ate   | 文件打开后定位到文件末尾。                                   |
| ios::in    | 打开文件用于读取。                                           |
| ios::out   | 打开文件用于写入。                                           |
| ios::trunc | 如果该文件已经存在，其内容将在打开文件之前被截断，即把文件长度设为 0。 |

您可以把以上两种或两种以上的模式结合使用。例如，如果您想要以写入模式打开文件，并希望截断文件，以防文件已存在，那么您可以使用下面的语法：

```cpp
ofstream outfile;
outfile.open("file.dat", ios::out | ios::trunc );
```

类似地，您如果想要打开一个文件用于读写，可以使用下面的语法：

```cpp
ifstream  afile;
afile.open("file.dat", ios::out | ios::in );
```

#### 写入文件

在 C++ 编程中，我们使用流插入运算符（ << ）向文件写入信息，就像使用该运算符输出信息到屏幕上一样。唯一不同的是，在这里您使用的是 **ofstream** 或 **fstream** 对象，而不是 **cout** 对象。

```cpp
 // writing on a text file
    #include <fiostream.h>
    int main () {
        ofstream out("out.txt");
        if (out.is_open()) 
       {
            out << "This is a line.\n";
            out << "This is another line.\n";
            out.close();
        }
        return 0;
    }
   //结果: 在out.txt中写入：
   This is a line.
   This is another line
```



#### 读取文件

在 C++ 编程中，我们使用流提取运算符（ >> ）从文件读取信息，就像使用该运算符从键盘输入信息一样。唯一不同的是，在这里您使用的是 **ifstream** 或 **fstream** 对象，而不是 **cin** 对象。

```cpp
// reading a text file
    #include <iostream.h>
    #include <fstream.h>
    #include <stdlib.h>
    
    int main () {
        char buffer[256];
        ifstream in("test.txt");
        if (! in.is_open())
        { cout << "Error opening file"; exit (1); }
        while (!in.eof() )
        {
            in.getline (buffer,100);
            cout << buffer << endl;
        }
        return 0;
    }
    //结果 在屏幕上输出
     This is a line.

```

上面的例子读入一个文本文件的内容，然后将它打印到屏幕上。注意我们使用了一个新的成员函数叫做eof ，它是ifstream 从类 ios 中继承过来的，当到达文件末尾时返回true 。

#### 状态标志符的验证(Verification of state flags)

除了eof()以外，还有一些验证流的状态的成员函数（所有都返回bool型返回值）：

- **bad()**

  如果在读写过程中出错，返回 true 。例如：当我们要对一个不是打开为写状态的文件进行写入时，或者我们要写入的设备没有剩余空间的时候。

- **fail()**

  除了与bad() 同样的情况下会返回 true 以外，加上格式错误时也返回true ，例如当想要读入一个整数，而获得了一个字母的时候。

- **eof()**

  如果读文件到达文件末尾，返回true。

- **good()**

  这是最通用的：如果调用以上任何一个函数返回true 的话，此函数返回 false 。

要想重置以上成员函数所检查的状态标志，你可以使用成员函数clear()，没有参数。



#### 获得和设置流指针(get and put stream pointers)

所有输入/输出流对象(i/o streams objects)都有至少一个流指针：

- ifstream， 类似istream, 有一个被称为get pointer的指针，指向下一个将被读取的元素。
- ofstream, 类似 ostream, 有一个指针 put pointer ，指向写入下一个元素的位置。
- fstream, 类似 iostream, 同时继承了get 和 put

我们可以通过使用以下成员函数来读出或配置这些指向流中读写位置的流指针：

- **tellg() 和 tellp()**

  这两个成员函数不用传入参数，返回pos_type 类型的值(根据ANSI-C++ 标准) ，就是一个整数，代表当前get 流指针的位置 (用tellg) 或 put 流指针的位置(用tellp).

- **seekg() 和seekp()**

  这对函数分别用来改变流指针get 和put的位置。两个函数都被重载为两种不同的原型：

  seekg ( pos_type position );
  seekp ( pos_type position );

  使用这个原型，流指针被改变为指向从文件开始计算的一个绝对位置。要求传入的参数类型与函数 tellg 和tellp 的返回值类型相同。

  seekg ( off_type offset, seekdir direction );
  seekp ( off_type offset, seekdir direction );

  使用这个原型可以指定由参数direction决定的一个具体的指针开始计算的一个位移(offset)。它可以是：

  | ios::beg | 从流开始位置计算的位移         |
  | -------- | ------------------------------ |
  | ios::cur | 从流指针当前位置开始计算的位移 |
  | ios::end | 从流末尾处开始计算的位移       |

#### 关闭文件

当 C++ 程序终止时，它会自动关闭刷新所有流，释放所有分配的内存，并关闭所有打开的文件。但程序员应该养成一个好习惯，在程序终止前关闭所有打开的文件。

下面是 close() 函数的标准语法，close() 函数是 fstream、ifstream 和 ofstream 对象的一个成员。

```cpp
void close();
```

### 参考文章

- [C++文件读写详解（ofstream,ifstream,fstream）](https://blog.csdn.net/kingstar158/article/details/6859379)
- [C++ getline()函数的用法](https://blog.csdn.net/MisterLing/article/details/51697098)
- [C++ 文件和流](https://www.runoob.com/cplusplus/cpp-files-streams.html)
- [C++ seekp和seekg函数用法详解](http://c.biancheng.net/view/1541.html)

