#include <iostream>

using namespace std;

int main() {
	int i = 0b10000000000000000000000000000000;
	int j = 0b01111111111111111111111111111111;
	cout << (i == INT_MIN) << endl;
	cout << (j == INT_MAX) << endl;
	cout << "-INT_MIN = " << -INT_MIN << endl; 
	cout << "INT_MIN = " << INT_MIN << endl;
	cout << "INT_MIN/10 = " << INT_MIN/10 << endl;
	cout << "INT_MIN%10 = " << INT_MIN%10 << endl;
	cout << "-INT_MIN%10 = " << -INT_MIN%10 << endl;
	cout << "-(INT_MIN%10) = " << -(INT_MIN%10) << endl;
	cout << "INT_MAX + INT_MAX = " << INT_MAX + INT_MAX << endl;
	cout << "INT_MIN + INT_MIN = " << INT_MIN + INT_MIN << endl;
	return 0;
}
