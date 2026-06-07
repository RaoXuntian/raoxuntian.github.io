#include <iostream>
#include <vector>
#include <initializer_list>
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
	vector<int> v7({1,0,3,7});

	auto il = {10,20,30};
	std::vector<int> v=il;
	std::initializer_list<int> ill=il;
	printf("%p\n", &v);
	printf("%p\n", il.begin());
	printf("%p\n", ill.begin());
	printf("%p\n", &il);
	printf("%p\n", &ill);
	show(il);
	show(v);
	show(v1);
	show(v2);
	show(v3);
	show(v4);
	show(v5);
	show(v6);
	show(v7);
	//show({1,0,3,7});
	return 0;
}