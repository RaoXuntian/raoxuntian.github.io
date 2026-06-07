#include<iostream>
using namespace std;

int global_i = 0;	// global_i在全局（初始化）区

char* global_p;		// global_p在全局（未初始化）区

int main(int argc, char const *argv[])
{
	printf("&global_i = %p\n", &global_i);
	printf("&global_p = %p\n", &global_p);
	printf("global_p = %p\n", global_p);

	static int static_i = 1;	// 全局静态区
	int i = 2;	// 	栈
	const int const_i = 3;	// 栈
	
	char p1[] = "HUST";		// p1在栈，"HUST"在常量区
	const char *p2 = "Computer Science";	// p2在栈，"Computer Science"在常量区
	global_p = new char(10);	
	// 指针变量global_p依然在全局区，但在堆上开辟了10个char长度的空间，global_p的值是堆上开辟空间的首地址
	char* p3 = new char(20);	
	// 这行代码在Heap中开辟了20个char长度的空间，同时在Stack上压入了p3，
	// 指针变量p存在于栈上，其值为刚刚在堆上开辟的空间的首地址。
	
	printf("&static_i = %p\n", &static_i);
	printf("&i = %p\n", &i);
	printf("&const_i = %p\n", &const_i);
	printf("%lu\n", sizeof(i));
	printf("%lu\n", sizeof(const_i));

	printf("&p1 = %p\n", &p1);
	printf("&p2 = %p\n", &p2);
	printf("%lu\n", sizeof(p2));
	printf("p1 = %p\n", p1);
	printf("p2 = %p\n", p2);

	printf("&global_p = %p\n", &global_p);
	printf("global_p = %p\n", global_p);
	printf("&p3 = %p\n", &p3);
	printf("p3 = %p\n", p3);
	return 0;
}