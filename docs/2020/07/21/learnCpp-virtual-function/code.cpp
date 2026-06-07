#include <iostream>
using namespace std;

class ClassA
{
public:
	ClassA() { cout << "ClassA::ClassA()" << endl; }
	virtual ~ClassA() { cout << "ClassA::~ClassA()" << endl; }

	void func1() { cout << "ClassA::func1()" << endl; }
	void func2() { cout << "ClassA::func2()" << endl; }

	virtual void vfunc1() { cout << "ClassA::vfunc1()" << endl; }
	virtual void vfunc2() { cout << "ClassA::vfunc2()" << endl; }
private:
	int aData;
};

class ClassB : public ClassA
{
public:
	ClassB() { cout << "ClassB::ClassB()" << endl; }
	virtual ~ClassB() { cout << "ClassB::~ClassB()" << endl; }

	void func1() { cout << "ClassB::func1()" << endl; }
	virtual void vfunc1() { cout << "ClassB::vfunc1()" << endl; }
private:
	int bData;
};

class ClassC : public ClassB
{
public:
	ClassC() { cout << "ClassC::ClassC()" << endl; }
	virtual ~ClassC() { cout << "ClassC::~ClassC()" << endl; }

	void func2() { cout << "ClassC::func2()" << endl; }
	virtual void vfunc2() { cout << "ClassC::vfunc2()" << endl; }
private:
	int cData;
};

int main(int argc, char const *argv[])
{
	ClassA *a = new ClassB();
	a->func1();                    // "ClassA::func1()"   隐藏了ClassB的func1()
	a->func2();                    // "ClassA::func2()"
	a->vfunc1();                   // "ClassB::vfunc1()"  重写了ClassA的vfunc1()
	a->vfunc2();                   // "ClassA::vfunc2()"

	return 0;
}