---
title: 浅谈C++的封装、继承、多态
date: 2020-07-20 12:25:04
updated:
tags:
- C++
- interview
- 多态
- 虚函数
- 封装
- 继承
---

面向对象的三个基本特征：**封装**、**继承**、**多态**。其中，**封装**可以隐藏实现细节，使得代码模块化；**继承**可以扩展已存在的代码模块（类）；它们的目的都是为了——代码重用。而**多态**则是为了实现另一个目的——接口重用！

<!--more-->

#### 一、封装

封装可以隐藏实现细节，使得代码模块化；封装是把过程和数据包围起来，对数据的访问只能通过已定义的界面。面向对象计算始于这个基本概念，即现实世界可以被描绘成一系列完全自治、封装的对象，这些对象通过一个受保护的接口访问其他对象。在面向对象编程上可理解为：**把客观事物封装成抽象的类，并且类可以把自己的数据和方法只让可信的类或者对象操作，对不可信的进行信息隐藏。**

封装是指保护类的成员不被随意访问的能力。我们在C++中使用的class类就是常用的一种封装思想。分离类的实现与接口，从而隐藏了类的实现细节。在C++语言中，通过把实现部分设为private完成封装的任务。

封装的优点：

1. 确保用户代码不会无意间破坏封装对象的状态；
2. 被封装的类的具体实现细节可以随时改变，而无须调整用户级别的代码。

一旦把数据成员定义成private的，类的作者就可以比较自由地修改数据了。当时实现的部分发生改变时，只需要检查类的代码本身以确认这次改变有什么影响；换句话说，只要类的接口不变，用户代码就无须改变。如果数据是public的，则所有使用了原来数据成员的代码都可能失效，这时我们必须定位并重写所有依赖于老版本实现的代码，之后才能重新使用该程序。

把数据成员的访问权限设为private还有另一个好处，这么做能防止由于用户的原因造成数据被破坏。如果我们发现有程序缺陷破坏了对象的状态，则可以在有限的范围内定位缺陷：因为只有实现部分的代码可能产生这样的错误。因此，错误的搜索限制在有限范围内将能极大地简化更改问题及修正程序等工作。

```cpp
#include <iostream>
using namespace std;

class person
{
private:
	double money;
public:
	int height;
	int weight;
	string name;
	person():height(180), weight(100), name("Jack"){cout << "创建默认人物……\n";};
	person(int a, int b, const string s):height(a), weight(b), name(s){};
	~person(){};
	void getMoney(double x) {money+=x;};
	void costMoney(double x) {money-=x;};
	void judge() {if (money>0) cout << name << "是有钱人！\n"; else cout << name << "是穷逼！\n";};
	double remainMoney() {return money;};
};

int main(int argc, char const *argv[])
{
	person a;
	cout << a.height << " " << a.weight << " " << a.name << endl;
	a.costMoney(50);
	a.judge();
	person *b = new person(178, 160, "Tom");
	b->getMoney(100);
	b->judge();
	//a.money();	//error: 'money' is a private member of 'person'
	cout << a.name << "还有" << a.remainMoney() << "元。" << endl;
	cout << b->name << "还有" << b->remainMoney() << "元。" << endl;
	return 0;
}
```



#### 二、继承

面向对象程序设计的核心思想是数据抽象、继承和动态绑定。通过使用数据抽象，我们可以将类的接口与实现分离；使用继承，可以定义相似的类型并对其相似的关系建模；使用动态绑定，可以在一定程度上忽略相似类型的区别，而以统一的方式使用它们的对象。



继承是指这样一种能力：它可以使用现有类的所有功能，并在无需重新编写原来的类的情况下对这些功能进行扩展。其继承的过程，就是从一般到特殊的过程。

通过继承联系在一起的类构成一种层次关系。通常在层次关系的根部有一个基类(base class)，也称为父类，其他类则直接或间接地从基类继承而来，这些继承得到的类称为派生类(derived class)，也称为子类。基类负责定义在层次关系中所有类共同拥有的成员，而每个派生类定义各自特有的成员。



在子类继承父类的过程中，构造函数和析构函数比较特殊，他们是不能被子类继承的。

**构造函数和析构函数是用来处理对象的创建和析构的，它们只知道对在它们的特殊层次的对象做什么。**

所以，**在整个层次中的所有的构造函数和析构函数都必须被调用，也就是说，构造函数和析构函数不能被继承。**

子类的构造函数会显示的调用父类的构造函数或隐式的调用父类的默认的构造函数进行父类部分的初始化。

析构函数也一样。它们都是每个类都有的东西，如果能被继承，那就没有办法初始化了。

此外，在创建子类对象时，为了初始化从父类继承来的数据成员，系统需要调用其父类的构造方法。

如果没有显式的构造函数，编译器会给一个默认的构造函数，并且该默认的构造函数仅仅在没有显式地声明构造函数情况下创建。

构造原则如下：

1. 如果子类没有定义构造方法，则调用父类的无参数的构造方法。
2. 如果子类定义了构造方法，不论是无参数还是带参数，在创建子类的对象的时候,首先执行父类无参数的构造方法，然后执行自己的构造方法。
3. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数，则会调用父类的默认无参构造函数。
4. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类自己提供了无参构造函数，则会调用父类自己的无参构造函数。
5. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类只定义了自己的有参构造函数，则会出错（如果父类只有有参数的构造方法，则子类必须显示调用此带参构造方法）。
6. 如果子类调用父类带参数的构造方法，需要用初始化父类成员对象的方式，

```cpp
#include <iostream>
using namespace std;

class person
{
private:
	double money;
public:
	int height;
	int weight;
	string name;
	person():height(180), weight(100), name("Jack"){cout << "person()\n";};
	person(const string s):height(180), weight(100), name(s) {cout << "person(string name)\n";};
	person(int a, int b, const string s):height(a), weight(b), name(s){cout << "person(int height, int weight, string name)\n";};
	~person(){cout << "~person()\n";};
	void getMoney(double x) {money+=x;};
	void costMoney(double x) {money-=x;};
	void judge() {if (money>0) cout << name << "是有钱人！\n"; else cout << name << "是穷逼！\n";};
	double remainMoney() {return money;};
};

class testSex: public person
{
private:
	bool sex;
public:
  void show(){cout << height << " " << weight << " " << name << endl;};
};

class boy: public person
{
private:
	bool sex;
public:
	boy():sex(true){cout << "boy()\n";};
	boy(const string s):sex(true), person(s) {cout << "boy(string name)\n";};
	boy(int a, int b, const string s):sex(true), person(a, b, s) {cout << "boy(int height, int weight, string name)\n";};
	~boy(){cout << "~boy()\n";};
	void getSex(){string sexx; sexx=sex?"Boy":"Girl"; cout << name << " is a " << sexx << endl;};
};

class girl: public person
{
private:
	bool sex;
public:
	girl():sex(false){cout << "girl()\n";};
	girl(const string s):sex(false), person(s) {cout << "girl(string name)\n";};
	girl(int a, int b, string s):sex(false), person(a, b, s){cout << "girl(int height, int weight, string name)\n";};
	~girl(){cout << "~girl()\n";};
	void getSex(){string sexx; sexx=sex?"Boy":"Girl"; cout << name << " is a " << sexx << endl;};
};

int main(int argc, char const *argv[])
{
	boy c(100, 200, "Milky");
	girl d("Rose");
	boy e;
	c.getSex();
	d.getSex();
	testSex test;
	test.show();
	return 0;
}
```

Output:

```cpp
person(int height, int weight, string name)
boy(int height, int weight, string name)
person(string name)
girl(string name)
person()
boy()
Milky is a Boy
Rose is a Girl
person()
180 100 Jack
~person()
~boy()
~person()
~girl()
~person()
~boy()
~person()
[Finished in 1.0s]
```

在上面的代码中，我们还可以用new的方法来定义一个对象

```cpp
//girl *f = new person();	// error!
	person *f = new girl();
	cout << f->remainMoney() << endl;
	delete f;
```

Output:

```cpp
person()
girl()
0
~person()
[Finished in 2.9s]
```

我们可以看到，因为在子类对象中含有与其父类对应的组成部分，所以我们能把子类的对象当成父类对象来使用，而且我们也能将**父类的指针或引用绑定到子类的对象中的父类部分上**。

这种转换通常称为**派生类到基类**(derived-to-base)的类型转换。和其他类型转换一样，编译器会隐式地执行派生类（子类）到基类（父类）的转换。

可以将父类的指针或引用绑定到子类对象上有一层极为重要的含义：当使用父类的引用（或指针）时，实际上我们并不清楚该引用（或指针）所绑定对象的真实类型。该对象可能是父类的对象，也可能是子类的对象。

反之，不存在从基类（父类）向派生类（子类）的隐式类型转换……

#### 三、多态

多态性可以简单地概括为“一个接口，多种方法”，程序在运行时才决定调用的函数，它是面向对象编程领域的核心概念。多态(polymorphism)，字面意思多种形状。

C++多态性是通过**虚函数**来实现的，虚函数允许子类重新定义成员函数，而子类重新定义父类的做法称为**覆盖**(override)，或者称为**重写**。（这里我觉得要补充，重写的话可以有两种，直接重写成员函数和重写虚函数，只有重写了虚函数的才能算作是体现了C++多态性）而**重载**(overload)则是允许有多个同名的函数，而这些函数的参数列表不同，允许参数个数不同，参数类型不同，或者两者都不同。编译器会根据这些函数的不同列表，将同名的函数的名称做修饰，从而生成一些不同名称的预处理函数，来实现同名函数调用时的重载问题。但这并没有体现多态性。

多态与非多态的实质区别就是函数地址是早绑定还是晚绑定。如果函数的调用，在编译器编译期间就可以确定函数的调用地址，并生产代码，是静态的，就是说地址是早绑定的。而如果函数调用的地址不能在编译器期间确定，需要在运行时才确定，这就属于晚绑定。

那么多态的作用是什么呢，封装可以使得代码模块化，继承可以扩展已存在的代码，他们的目的都是为了代码重用。而多态的目的则是为了接口重用。也就是说，不论传递过来的究竟是那个类的对象，函数都能够通过同一个接口调用到适应各自对象的实现方法。

最常见的用法就是**声明基类的指针，利用该指针指向任意一个子类对象，调用相应的虚函数，可以根据指向的子类的不同而实现不同的方法**。如果没有使用虚函数的话，即没有利用C++多态性，则利用基类指针调用相应的函数的时候，将总被限制在基类函数本身，而无法调用到子类中被重写过的函数。因为没有多态性，函数调用的地址将是一定的，而固定的地址将始终调用到同一个函数，这就无法实现一个接口，多种方法的目的了。

让我们再次修改一下之前的代码：

```cpp
#include <iostream>
using namespace std;

class person
{
protected:
	double money;
public:
	int height;
	int weight;
	string name;
  person(const person &p){cout << "person(person p)\n";};
	person():height(180), weight(100), name("Jack"){cout << "person()\n";};
	person(const string s):height(180), weight(100), name(s) {cout << "person(string name)\n";};
	person(int a, int b, const string s):height(a), weight(b), name(s){cout << "person(int height, int weight, string name)\n";};
	virtual ~person(){cout << "~person()\n";};
	virtual void getMoney(double x) {money+=x;};
	virtual void costMoney(double x) {money-=x;};
	virtual void slogan(){cout << "I am a person." << endl;};
	virtual void slogan(string s){cout << "I am a " << s << "." << endl;};
	void judge() {if (money>0) cout << name << "是有钱人！\n"; else cout << name << "是穷逼！\n";};
	double remainMoney() {return money;};

};

class testSex: public person
{
private:
	bool sex;
public:
	void show(){cout << height << " " << weight << " " << name << endl;};
};

class boy: public person
{
private:
	bool sex;
public:
	boy():sex(true){cout << "boy()\n";};
	boy(const string s):sex(true), person(s) {cout << "boy(string name)\n";};
	boy(int a, int b, const string s):sex(true), person(a, b, s) {cout << "boy(int height, int weight, string name)\n";};
	~boy(){cout << "~boy()\n";};
	void getSex(){string sexx; sexx=sex?"Boy":"Girl"; cout << name << " is a " << sexx << endl;};
	void getMoney(double x) {money+=x*2;};
	void costMoney(double x) {money-=x*0.5;};
	void slogan(){cout << "I am a boy." << endl;};
};

class girl: public person
{
private:
	bool sex;
public:
	girl():sex(false){cout << "girl()\n";};
	girl(const string s):sex(false), person(s) {cout << "girl(string name)\n";};
	girl(int a, int b, string s):sex(false), person(a, b, s){cout << "girl(int height, int weight, string name)\n";};
	~girl(){cout << "~girl()\n";};
	void getSex(){string sexx; sexx=sex?"Boy":"Girl"; cout << name << " is a " << sexx << endl;};
	void getMoney(double x) {money+=x*1.5;};
	void costMoney(double x) {money-=x*3;};
	void slogan(){cout << "I am a girl." << endl;};
};

int main(int argc, char const *argv[])
{
	person g;
	boy h;
	girl i;
	g.slogan();
	g.slogan("doctor");
	h.slogan();
	i.slogan();
	return 0;
}
```



#### 重载和重写

所谓的重载(overload)就是，两个函数名相同，但是参数列表不同（个数、类型），返回值类型也可能不同。

比如在父类person中我们就对slogan()函数进行了重载。

```cpp
virtual void slogan(){cout << "I am a person." << endl;};
virtual void slogan(string s){cout << "I am a " << s << "." << endl;};
```

所谓的重写(override)，也就是覆盖，子类继承了父类，父类中的函数是虚函数，在子类中重新定义了这个虚函数，这种情况是重写。

上面的代码输出结果如下：

```cpp
person()
person()
boy()
person()
girl()
I am a person.
I am a doctor.
I am a boy.
I am a girl.
~girl()
~person()
~boy()
~person()
~person()
[Finished in 0.9s]
```

我们对子类中的slogan()函数进行了重写，重新定义了父类中的虚函数，方法是将父类中的slogan()添加虚函数关键词virtual。

除此之外，还对getMoney()和costMoney()进行了重写，这两个函数涉及到person中的private成员变量money，**子类无法访问父类的private成员**，因此只有把money改为**protected**成员变量。



我们再做个试验，我们尝试着将子类赋值拷贝给父类、父类的指针或引用绑定到子类对象，看看会有什么结果。

```cpp
// girl i;
person j = i;
person &j_ref = i;
person *j_p = &i;
j.slogan();
j_ref.slogan();
j_p->slogan();

/*
I am a person.
I am a girl.
I am a girl.
*/
```

`person j = i;`将子类对象i赋值拷贝给父类对象j，i和j是两个独立的对象，他们的地址不同，i是girl，j是person，所以j.slogan()是执行person类的slogan();

`person &j_ref = i;`和`person *j_p = &i;`则是用父类的引用或指针绑定到一个子类的对象或地址，引用和指针虽然是父类，但绑定的是子类的对象啊！

当我们使用父类的引用或指针调用子类中定义的一个函数时，我们并不知道该函数真正作用的对象是什么类型，因为它可能是一个父类的对象，也可能是一个子类的对象。如果该函数时虚函数，则直到运行时才会决定到底执行哪个版本，**判断的依据是引用或指针所绑定的对象的真实类型**。


总结一下：

多态的实现主要分为静态多态和动态多态，静态多态主要是重载，在**编译**的时候就已经确定；动态多态是用虚函数机制实现的，在**运行**期间动态绑定。

举个例子：一个父类类型的指针指向一个子类对象的时候，使用父类的指针去调用子类中重写了的父类中的虚函数的时候，会调用子类重写过后的函数，在父类中声明为加了virtual关键词的函数，在子类中重写的时候不需要加virtual也是虚函数。



关于虚函数更详细的原理，请听下回分解。

#### 四、参考文章

- C++ Primer 5th
- [C++封装继承多态总结](https://blog.csdn.net/ruyue_ruyue/article/details/8211809)
- [在C++中子类继承和调用父类的构造函数方法](https://blog.csdn.net/hemmingway/article/details/7853713)
- [构造函数与析构函数不能被继承](https://www.cnblogs.com/zzdbullet/p/10470681.html)
- [浅谈C++多态性](https://blog.csdn.net/Hackbuteer1/article/details/7475622)



