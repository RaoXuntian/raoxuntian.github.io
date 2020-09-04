#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	//对于基础类型 默认是大顶堆
    priority_queue<int> a; 
    //等同于 priority_queue<int, vector<int>, less<int> > a;
    
    //             这里一定要有空格，不然成了右移运算符↓
    priority_queue<int, vector<int>, greater<int> > c;  //这样就是小顶堆
    priority_queue<string> b;

    std::vector<int> v{1,2,9,8,4,0,-5};

    for (size_t i=0; i<v.size(); ++i) {
    	a.push(v[i]);
    	c.push(v[i]);
    }

    while (!a.empty()) {
        cout << a.top() << ' ';
        a.pop();
    } 
    cout << endl;

    while (!c.empty()) {
        cout << c.top() << ' ';
        c.pop();
    }
    cout << endl;

    b.push("abc");
    b.push("abcd");
    b.push("cbd");
    while (!b.empty()) 
    {
        cout << b.top() << ' ';
        b.pop();
    } 
    cout << endl;
    
	return 0;
}