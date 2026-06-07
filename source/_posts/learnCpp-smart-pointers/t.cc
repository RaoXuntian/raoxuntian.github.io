#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct A
{
private:
	int val_;
public:
	A():val_(0){cout << "A()" << endl;};
	A(int val):val_(val){cout << "A(" << val_ << ")" << endl;};
	~A(){cout << "~A(" << val_ << ")" << endl;};
	void print() {cout << "This is a test~ " << val_ << endl;};
};

int main(int argc, char const *argv[])
{
	shared_ptr<int> p1(new int(42));
	//auto p2=std::make_shared<vector<int> > ();
	shared_ptr<vector<int>> p2(new vector<int>{1,2,3});

	auto p4 = new A(13);
	shared_ptr<A> p3(p4);
	shared_ptr<A> p5=make_shared<A>(24);
	//auto p6(p3);

	cout << p3.use_count() << endl;
	p5.reset(); // 主动销毁p5
	p3.reset(new A); // reset里参数必须是原始指针 p3指向新的地址 原地址销毁
	// std::shared_ptr::reset() function required a raw pointer as parameter.
	//p5=p4;
	cout << *p1 << endl;
	cout << p2->at(0) << " " << p2->at(1) << " " << p2->at(2) << endl;
	p3->print();
	
	cout << "----------------" << endl;
	unique_ptr<string> p6(new string("hahahaha!!!"));
	// unique_ptr<string> p6_error(p6); // ERROR: unique_ptr不支持拷贝
	unique_ptr<string> p6_error;
	// p6_error=p6; // ERROR: unique_ptr不支持赋值
	cout << *p6 << endl;
	unique_ptr<string> p7(p6.release());	// release将p6置空
	unique_ptr<string> p8(new string("XXXDDD"));
	cout << "*p7 == " << *p7
		<< "\t*p8 == " << *p8 << endl;
	// 将所有权从p8转移给p7
	p7.reset(p8.release());	// reset释放了p7原来的指向的内存
	cout << "*p7 == " << *p7 << endl;
	return 0;
}