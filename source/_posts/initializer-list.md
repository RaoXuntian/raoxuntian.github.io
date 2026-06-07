---
title: initializer_list
date: 2020-06-23 17:09:58
updated: 2020-06-23
tags:
- C++
- 数据结构
---

我记得有次面试的时候面试官提过一句initializer_list，当时只是知道这个东西是C++11中的新类型，但并没有去深入了解它，今天突然想到了就看了一些文章，随便记录一下。



C++11提供的新类型，定义在<initializer_list>头文件中。

```cpp
template< class T >
class initializer_list;
```

回忆一下我们初始化一个vector有哪些方法？

<!--more-->

```cpp
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void show(T s) {
	for (auto i: s) 
		std::cout << i << " ";
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
	int a[] = {1,0,3,7};
	vector<int> v1;
	vector<int> v2(4);
	vector<int> v3(4, 8);
	vector<int> v4(a, a+sizeof(a)/sizeof(int));
	vector<int> v5(v4.begin(), v4.end());
	vector<int> v6 = {1,0,3,7};
	vector<int> v7{1,0,3,7};

	show(v1);
	show(v2);
	show(v3);
	show(v4);
	show(v5);
	show(v6);
	show(v7);
	//show({1,0,3,7});	// invalid: note: candidate template ignored: couldn't infer template argument 'T'
	return 0;
}
```

上面罗列了6种初始化vector的方法，但我在电脑上执行的时候，v6报错了：

{% asset_img 1.png  image %}

我们忽略auto语法的warning，专注一下最后一个error：**error:** **non-aggregate type 'vector< int >' cannot be initialized with an initializer list**。大概意思就是我们不能用一个initializer list去初始化一个vector< int >，为啥不行呢？

我们从C++官网可以找到答案：

>  A `std::initializer_list` object is automatically constructed when:
>
> - a *braced-init-list* is used to [list-initialize](https://en.cppreference.com/w/cpp/language/list_initialization) an object, where the corresponding constructor accepts an `std::initializer_list` parameter
> - a *braced-init-list* is used as the right operand of [assignment](https://en.cppreference.com/w/cpp/language/operator_assignment#Builtin_direct_assignment) or as a [function call argument](https://en.cppreference.com/w/cpp/language/overload_resolution#Implicit_conversion_sequence_in_list-initialization), and the corresponding assignment operator/function accepts an `std::initializer_list` parameter
> - a *braced-init-list* is bound to [`auto`](https://en.cppreference.com/w/cpp/language/auto), including in a [ranged for loop](https://en.cppreference.com/w/cpp/language/range-for)

上面这段话的意思大概就是，在这些情况下会自动构造一个`std::initializer_list`对象：

- 对一个对象初始化是使用大括号`std::initializer_list`初始化的时候，`std::initializer_list`对象会被自动构造，同时也适用于赋值和函数调用的参数。
- 上面的前提是你要初始化的对象、对应的赋值运算符和函数**必须可以接受(accepts)一个`std::initializer_list`参数**。
- 涉及到for循环的时候，或者auto的时候，使用大括号也会也会被自动构造成一个`std::initializer_list`。

也就是说initializer_list对象只能用大括号{}初始化。

```cpp
auto il = {10,20, 30}; // the type of il is an initializer_list<int>
```

在C++11之前的vector这些STL并没有参数为`std::initializer_list`的构造函数，所以当我们将一个`std::initializer_list`赋值拷贝或者拷贝构造给一个对象的前提是，这个对象有提供参数为`std::initializer_list`的赋值拷贝运算符或拷贝构造函数。上面的程序在C++11的环境下执行就没有问题了。

另外，拷贝一个initializer_list对象并不会拷贝里面的元素。其实只是引用而已。而且里面的元素全部都是const的，所以我们不能去修改一个`std::initializer_list`里的数值。

```cpp
auto il = {10,20,30};
std::vector<int> v=il;
std::initializer_list<int> ill=il;
printf("%p\n", &v);
printf("%p\n", il.begin());
printf("%p\n", ill.begin());
printf("%p\n", &il);
printf("%p\n", &ill);

//0x7ffee328a828
//0x10c978e30
//0x10c978e30
//0x7ffee328a840
//0x7ffee328a808
```

通过查看对象和对象里元素的地址，我们可以证实了，`std::initializer_list`里的元素作为const是存在常量区里，随着整个程序的结束才被系统释放，而我们定义出来的`std::initializer_list ill` 和`std::vector v`是作为局部变量存在栈区的，函数生命周期结束局部变量也就随之释放了内存。

还有一点关于对`std::initializer_list`里的元素访问，我们并不能像访问数组那样用数字下标去访问，因为`std::initializer_list`并没有提供这样的操作符，我们只能像使用vector一样使用迭代器去访问`std::initializer_list`里的元素。

```cpp
void error_msg(initializer_list<string> il)
{
   for(auto beg=il.begin();beg!=il.end();++beg)
      cout<<*beg<<" ";
   cout<<endl;
}
```



最后让我们再品味一下官方提供的代码吧，你细品你细品~

```cpp
#include <iostream>
#include <vector>
#include <initializer_list>

template <class T>
struct S {
    std::vector<T> v;
    S(std::initializer_list<T> l) : v(l) {
         std::cout << "constructed with a " << l.size() << "-element list\n";
    }
    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }
    std::pair<const T*, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // copy list-initialization in return statement
                                   // this is NOT a use of std::initializer_list
    }
};
 
template <typename T>
void templated_fn(T s) {
    for (auto i: s)
        std::cout << i << " ";
    std::cout << std::endl;
}
 
int main()
{
    S<int> s = {1, 2, 3, 4, 5}; // copy list-initialization
    s.append({6, 7, 8});      // list-initialization in function call
 
    std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";
 
    for (auto n : s.v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    std::cout << "Range-for over brace-init-list: \n";
 
    for (int x : {-1, -2, -3}) // the rule for auto makes this ranged-for work
        std::cout << x << ' ';
    std::cout << '\n';
 
    auto al = {10, 11, 12};   // special rule for auto
 
    std::cout << "The list bound to auto has size() = " << al.size() << '\n';
 
//    templated_fn({1, 2, 3}); // compiler error! "{1, 2, 3}" is not an expression,
                             // it has no type, and so T cannot be deduced
    templated_fn<std::initializer_list<int>>({1, 2, 3}); // OK
    templated_fn<std::vector<int>>({1, 2, 3});           // also OK
}
```

output:

```cpp
constructed with a 5-element list
The vector size is now 8 ints:
1 2 3 4 5 6 7 8 
Range-for over brace-init-list: 
-1 -2 -3 
The list bound to auto has size() = 3
1 2 3 
1 2 3 
```



### 参考文章

- https://en.cppreference.com/w/cpp/utility/initializer_list
- [C++11中新特性之：initializer_list详解](https://www.cnblogs.com/lysuns/p/4278589.html)
- [C++ 11 initializer_list关键字](https://blog.csdn.net/wangkai_123456/article/details/76252073)
- [C++11中std::initializer_list的使用](https://blog.csdn.net/fengbingchun/article/details/77938005)

