#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int i = 3;
	int *ci = &i, &ri = i;
	cout << ci << endl;	//ci = 0x7ffee43d269c
	cout << ri << endl;	//ri = 3

	cout << sizeof(ci) << endl; // sizeof(ci) = 8
	cout << sizeof(ri) << endl;	// sizeof(ri) = 4

	int *cii;
	int *ciii = NULL;
	cout << (long)ciii << endl;
	//int &rii;	// 错误：引用必须初始化
	//int &riii = 1;	// 错误：非const引用不能指向const
	// 上面语句实际的操作是
	// const int tmp = 1;
	// int &riii = tmp;	// 这一步错误

	ri++;
	cout << i << endl; // i = 4
	(*ci)++;
	cout << i << endl; // i = 5
	//*ci++;
	//cout << ci << endl; // ci = 0x7ffee43d26a0


	int *p1 = nullptr;
	int *p2 = 0;
	int *p3 = NULL;
	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << (long)p1 << endl;

	int ival = 1024;
	int &refVal = ival;
	//int &refVal2;
	//const int &refVal2 = 1024;
	int &refVal2 = ri;
	int j = refVal2;

	//int &refVal4 = 10;	// 错误：引用类型初始值必须是一个对象
	double dval = 3.14;
	//int &refVal5 = dval;	// 错误：此处引用类型的初始值必须是int型对象

	const int &refVal4 = 10; // valid
	const int &refVal5 = dval;	// valid
	return 0;
}