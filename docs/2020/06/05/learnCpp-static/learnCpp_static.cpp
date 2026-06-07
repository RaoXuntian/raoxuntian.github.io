/*
#include <iostream>
using namespace std;

static int gi;

size_t count_calls() {
	static size_t ctr=0;
	return ++ctr;
}

int main(int argc, char const *argv[])
{
	for (size_t i=0; i<10; ++i) {
		cout << count_calls() << " ";
	}
	cout << "\n" << gi << endl;
	return 0;
}
*/
/*
#include <iostream>
using namespace std;

class A
{
public:
	int y;      //普通变量成员
    int &r;     //引用成员变量
    const int d;    //常量成员变量
    static int c;   //静态成员变量

	A():y(1), r(y), d(3){};
	~A(){};
	
};

int A::c = 2;
int main(int argc, char const *argv[])
{
	A a;
	A b;
	a.c=2;
	cout << a.c << endl;
	b.c=3;
	cout << a.c << " " << b.c << endl;
	A::c=4;
	cout << a.c << " " << b.c << endl;
	A c;
	cout << c.c << endl;
	return 0;
}
*/

#include <iostream>
using namespace std;

class A
{
public:
	A(){cout << "running A()" << endl;};
	~A(){cout << "running ~A()" << endl;};
	static void f() {cout << "running f()" << endl;};
	
};

int main(int argc, char const *argv[])
{
	A::f();
	{
		static A a;
		a.f();
	}
	cout << "END of main" << endl;
	return 0;
}