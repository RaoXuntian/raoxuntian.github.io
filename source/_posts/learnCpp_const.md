---
title: 浅谈C++关键字之const
date: 2020-06-03 17:52:56
tags:
	- C++
	- interview

---



C++关键字之const



### 1.const含义

const 是 constant 的缩写，本意是不变的，不易改变的意思。在 C++ 中是用来修饰内置类型变量，自定义对象，成员函数，返回值，函数参数。

### 2.const作用

#### 2.1定义const常量

`const int* bufSize = 64;`

#### 2.2便于进行类型检查

const*常量有数据类型，而宏常量没有数据类型。编译器可以对前者进行类型安全检查，而对后者只进行字符替换，没有类型安全检查，并且在字符替换时可能会产生意料不到的错误。

<!--more-->

#### 2.3可以保护别修饰的东西

防止修改，起保护作用，增加程序健壮性

```cpp
void f(const int i){
	i++; //error!    
}

```

#### 2.4为函数重载提供一个参考

```cpp
class A
{
           ......
  void f(int i)       {......} //一个函数
  void f(int i) const {......} //上一个函数的重载
           ......
};

```

#### 2.5可以节省空间，避免不必要的内存分配

const定义常量从汇编的角度来看，只是给出了对应的内存地址，而不是象#define一样给出的是立即数，所以，const定义的常量在程序运行过程中只有一份拷贝，而#define定义的常量在内存中有若干个拷贝

```cpp
#define PI 3.14159         //常量宏
const doulbe  Pi=3.14159;  //此时并未将Pi放入ROM中
              ......
double i=Pi;   //此时为Pi分配内存，以后不再分配！
double I=PI;  //编译期间进行宏替换，分配内存
double j=Pi;  //没有内存分配
double J=PI;  //再进行宏替换，又一次分配内存！

```

#### 2.6提高了效率

可以很方便地进行参数的调整和修改，同宏定义一样，可以做到不变则已，一变都变。

编译器通常不为普通const常量分配存储空间，而是将它们保存在符号表中，这使得它成为一个编译期间的常量，没有了存储与读内存的操作，使得它的效率也很高



### 3.const使用

1. 修饰变量，说明该变量不可以被改变；
2. 修饰指针，分为指向常量的指针（pointer to const）和自身是常量的指针（常量指针，const pointer）；
3. 修饰引用，指向常量的引用（reference to const），用于形参类型，即避免了拷贝，又避免了函数对值的修改；
4. 修饰函数相关，包括修饰函数参数和函数返回值；
5. 修饰类成员函数，说明该成员函数内不能修改成员变量。

#### 3.1修饰变量

```cpp
const int bufSize = 512; 
int const bufSize1 = 1024; 
// 以上两种定义形式在本质上是一样的，const修饰的类型为int的变量是不可变的
bufSize = 1024	// 错误：试图向const int对象写值，不能改变bufSize

int a = 64;
const int ci = a;	// ci=64
const int cis = sizeof(a);	// cis=4
const int k;	// 错误：k是一个未经初始化的变量

```

#### 3.2修饰指针

将const用于指针有一些很微妙的地方（指针本身看上去就很微妙），我们将详细探讨一下用两种不同的方式将const关键字用于指针。

##### 3.2.1 pointer to const

```cpp
int age = 17;
const int *pt = &age;	// a pointer to const int
// 该声明指出，pt指向一个const int(这里是17)，因此不能用pt来改变这个值。
// 换句话说，*pt的值为const，不能修改。

(*pt)++;	// 错误：指针pt指向的对象是const int
cin >> *pt	// 错误：同上
  
// 现在来看一个微妙的问题。
// pt的声明并不意味着它指向的值实际上就是一个常量，而只是意味着对pt而言，这个值是常量。
*pt = 23;	// 错误：指针pt指向的对象是const int
age = 23;	// valid:beacause age is not declared to be const

```

##### 3.2.2 const pointer

```cpp
int sloth = 3;
const int *ps = &sloth;	// a pointer to const int
int * const finger = &sloth;	// a const pointer to int
// finger只能指向sloth，但允许使用finger来修改sloth的值。
// ps不能修改sloth的值，但允许ps指向另一个位置。
finger = &age;	// invalid
*finger = 5;	// valid

// 简言之：finger和*ps都是const，而*finger和ps不是

```

##### 3.2.3 summary

- 指针所指向的内容是常量不可变。
  `const int *pt; `

- 指针本身是常量不可变。
  `int * const pt;`

- 两者都不可变。
  `const int * const pt;`

**const在*前面，对象是const；**
**const在*后面，指针是const。**

| Pointers and constants | int i;  | const int ci = 3;  |
| :----------------------------------- | :-------- | :------------------- |
| int *ip;//可以通过ip修改           | ip = &i;  | ip = &ci;  // ERROR! |
| const int *cip;//不可以通过cip修改 | cip = &i; | cip = &ci;           |

> **尽可能使用const**
>
> 将指针参数声明为指向常量数据的指针有两条理由：
>
> - 这样可以避免由于无意间修改数据而导致的编程错误。
> - 使用const使得函数能够处理const和非const实参，否则将只能接受非const数据。
>
> 如果条件允许，则应该将指针形参声明为指向const的指针。

#### 3.3修饰引用

可以把引用绑定到const对象上，就像绑定到其它对象上一样，我们称之为对**常量的引用**(**reference to const**)。

与普通引用不同的是，对常量的引用不能被用作修改它所绑定的对象。

```cpp
const int ci = 1024;
const int &r1 = ci;	// 正确：引用及其对应的对象都是常量
r1 = 42;	// 错误：r1是对常量的引用
int &r2 = ci;	// 错误：试图让一个非常量引用(r2)指向一个常量对象(ci)

```

因为不允许直接为ci赋值，当然也不能通过引用去改变ci。因此，对r2的初始化是错误的。假设该初始化合法，则可以通过r2来改变它引用对象的值，这显然是不正确的。

> **术语：常量引用是对const的引用**
>
> ------
>
> c++程序猿们经常把词组”对const的引用“简称为“常量引用”，这一简称还是挺靠谱的，不过前提是你得时刻记得这就是个简称而已。
>
> 严格来说，并不存在常量引用。因为引用不是一个对象，所以我们没法让引用本身恒定不变。事实上，由于c++语言并不允许随意改变引用所绑定的对象，所以从这层意思上理解所有的引用又都算是常量。引用的对象是常量还是非常量可以决定其所能参与的操作，却无论如何都不会影响到引用和对象的绑定关系本身。

- 指向常量的引用(reference to const)
- 没有const reference，因为引用本身就是const pointer

**对const的引用可能引用一个并非const的对象**

必须认识到，**常量引用仅对引用可参与的操作做出了限定**，对应引用的对象本身是不是一个常量未作限定。因为对象也可能是个非常量，所以允许通过其他途径改变它的值：

```cpp
int i = 42;
int &r1 = i; 		// 引用r1绑定对象i
const int &r2 = i;	// r2也绑定对象i，但不允许通过r2修改i的值
r1 = 0;			// r1并非常量，i的值修改为0
r2 = 0;			// 错误：r2是一个常量引用

```



#### 3.4修饰函数相关

##### 3.4.1修饰函数参数

1. 传递过来的参数在函数内不可以改变(无意义，因为Var本身就是形参)

   `void function(const int Var);`

2. 参数指针所指内容为常量不可变

   `void function(const char* Var);`

3. 参数指针本身为常量不可变(也无意义，因为char* Var也是形参)

   `void function(char* const Var);`

4. 参数为引用，为了增加效率同时防止修改。修饰引用参数时：

   `void function(const Class& Var); //引用参数在函数内不可以改变`

   `void function(const TYPE& Var); //引用参数在函数内为常量不可变`

这样的一个const引用传递和最普通的函数按值传递的效果是一模一样的，他禁止对引用的对象的一切修改，唯一不同的是按值传递会先建立一个类对象的副本， 然后传递过去,而它直接传递地址，所以这种传递比按值传递更有效。另外只有引用的const传递可以传递一个临时对象，因为临时对象都是const属性，且是不可见的，他短时间存在一个局部域中，所以不能使用指针，只有引用的const传递能够捕捉到这个家伙。

##### 3.4.2修饰函数返回值

 const修饰函数返回值其实用的并不是很多，它的含义和const修饰普通变量以及指针的含义基本相同。

1. `const int fun1()`	

      //这个其实无意义，因为参数返回本身就是赋值。

2. `const int * fun2()`

      //调用时 const int *pValue = fun2();
      //我们可以把fun2()看作成一个变量，即指针内容不可变。

3. `int* const fun3()`

      //调用时 int * const pValue = fun2();
      //我们可以把fun2()看作成一个变量，即指针本身不可变。

***一般情况下，函数的返回值为某个对象时，如果将其声明为const时，多用于操作符的重载。通常，不建议用const修饰函数的返回值类型为某个对象或对某个对象引用的情况。***原因如下：如果返回值为某个对象为const（const A test = A 实例）或某个对象的引用为const（const A& test = A实例） ，则返回值具有const属性，则返回实例只能访问类A中的公有（保护）数据成员和const成员函数，并且不允许对其进行赋值操作，这在一般情况下很少用到。


#### 3.5修饰类成员函数

##### 3.5.1 const修饰成员变量

const修饰类的成员函数，表示成员常量，不能被修改，同时它只能在初始化列表中赋值。

```cpp
class A {
        …
        const int nValue;         //成员常量不能被修改
        …
        A(int x): nValue(x) { } ; //只能在初始化列表中赋值
}

```



##### 3.5.2 const修饰成员函数

const修饰类的成员函数，则该成员函数不能修改类中任何非const成员函数。一般写在函数的最后来修饰。**也就是说，这些函数是"只读"函数。**

```cpp
class A {
        …
       void function() const;	//常成员函数, 它不改变对象的成员变量.                        

				//也不能调用类中任何非const成员函数。
}

```

对于const类对象/指针/引用，只能调用类的const成员函数，因此，const修饰成员函数的最重要作用就是限制对于const对象的使用。

a. const成员函数不被允许修改它所在对象的任何一个数据成员。

b. const成员函数能够访问对象的const成员，而其他成员函数不可以。

 

##### 3.5.3 const修饰类对象/对象指针/对象引用

·             const修饰类对象表示该对象为常量对象，其中的任何成员都不能被修改。对于对象指针和对象引用也是一样。

·             const修饰的对象，该对象的任何非const成员函数都不能被调用，因为任何非const成员函数会有修改成员变量的企图。

·             const对象只能访问const成员函数，而非const对象可以访问任意的成员函数,包括const成员函数。

例如：

```cpp
class AAA {
 void func1();
 void func2() const;
}
const AAA aObj;
aObj.func1();	// invalid
aObj.func2();	// valid

const AAA* aObj = new AAA();
aObj-> func1();	// invalid
aObj-> func2();	// valid

```

##### 3.5.4 const修饰重载运算符

```cpp
bool operator <(const student &a ) const{     
        if(score!=a.score) return score<a.score;
        else if(name.compare(a.name)!=0) return name<a.name;
        else if(age!=a.age)return age<a.age;
        else
            return false;
    }
};

```

**加const是因为：**

1. 我们不希望在这个函数中对用来进行赋值的“原版”做任何修改。**函数加上const后缀的作用是表明函数本身不会修改类成员变量。**

2. 加上const，对于const的和非const的实参，函数就能接受；如果不加，就只能接受非const的实参。

**另外补充，用引用是因为：**
这样可以避免在函数调用时对实参的一次拷贝，提高了效率。

```cpp
// 类
class A
{
private:
    const int a;                // 常对象成员，只能在初始化列表赋值

public:
    // 构造函数
    A() : a(0) { };
    A(int x) : a(x) { };        // 初始化列表

    // const可用于对重载函数的区分
    int getValue();             // 普通成员函数
    int getValue() const;       // 常成员函数，不得修改类中的任何数据成员的值
};

void function()
{
    // 对象
    A b;                        // 普通对象，可以调用全部成员函数、更新常成员变量
    const A a;                  // 常对象，只能调用常成员函数
    const A *p = &a;            // 指针变量，指向常对象
    const A &q = a;             // 指向常对象的引用

    // 指针
    char greeting[] = "Hello";
    char* p1 = greeting;                // 指针变量，指向字符数组变量
    const char* p2 = greeting;          // 指针变量，指向字符数组常量（const 后面是 char，说明指向的字符（char）不可改变）
    char* const p3 = greeting;          // 自身是常量的指针，指向字符数组变量（const 后面是 p3，说明 p3 指针自身不可改变）
    const char* const p4 = greeting;    // 自身是常量的指针，指向字符数组常量
}

// 函数
void function1(const int Var);           // 传递过来的参数在函数内不可变
void function2(const char* Var);         // 参数指针所指内容为常量
void function3(char* const Var);         // 参数指针为常量
void function4(const int& Var);          // 引用参数在函数内为常量

// 函数返回值
const int function5();      // 返回一个常数
const int* function6();     // 返回一个指向常量的指针变量，使用：const int *p = function6();
int* const function7();     // 返回一个指向变量的常指针，使用：int* const p = function7();

```

### 4.const对象默认为文件局部变量

注意：非const变量默认为extern。要使const变量能够在其他文件中访问，必须在文件中显式地指定它为extern。

### 5.相关文章

- C++ Primer中文版第5版
- C++ Primer Plus中文版第五版
- https://blog.csdn.net/Eric_Jo/article/details/4138548
- https://interview.huihut.com/#/?id=const
- https://blog.csdn.net/qq_36770641/article/details/89884807

