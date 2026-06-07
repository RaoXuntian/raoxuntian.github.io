#include <iostream>
using namespace std;

void show() {
	cout << "type: \t\t" << "************size**************"<< endl;  
    cout << "bool: \t\t" << "所占字节数：" << sizeof(bool) << endl;  
    cout << "char: \t\t" << "所占字节数：" << sizeof(char) << endl;  
    cout << "signed char: \t" << "所占字节数：" << sizeof(signed char) << endl;  
    cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char) << endl;  
    cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t) << endl;  
    cout << "short: \t\t" << "所占字节数：" << sizeof(short) << endl;  
    cout << "int: \t\t" << "所占字节数：" << sizeof(int) << endl;  
    cout << "unsigned: \t" << "所占字节数：" << sizeof(unsigned) << endl;  
    cout << "long: \t\t" << "所占字节数：" << sizeof(long) << endl;  
    cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long) << endl;  
    cout << "double: \t" << "所占字节数：" << sizeof(double) << endl;  
    cout << "long double: \t" << "所占字节数：" << sizeof(long double) << endl;  
    cout << "float: \t\t" << "所占字节数：" << sizeof(float) << endl;  
    cout << "size_t: \t" << "所占字节数：" << sizeof(size_t) << endl;  
    cout << "string: \t" << "所占字节数：" << sizeof(string) << endl;  
    cout << "type: \t\t" << "************size**************"<< endl;  
}

#pragma pack(1)
class A
{
	char c;
	short s;
	int i;
	char ch[5];
	float f;
};
class B
{
	A a;
	short s;
	char c;
	int i;
	float d;
};
class C
{
	double d;
	int i;
	short s;
	char c;
};
#pragma pack()

int main(int argc, char const *argv[])
{
	
	A a;
	B b;
	C c;
	printf("%lu\n", sizeof(a));
	printf("%lu\n", sizeof(b));
	printf("%lu\n", sizeof(c));
	//show();
	return 0;
}