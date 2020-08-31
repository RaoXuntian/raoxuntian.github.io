#include <iostream>
#include <vector>

int partition(std::vector<int>& arr, int l, int r) {
	int x=arr[r], i=l-1;
	for (int j=l; j<=r; ++j) {
		if (arr[j]<x) {
			std::swap(arr[++i], arr[j]);
		}
	}
	std::swap(arr[++i], arr[r]);
	return i;
}

void quickSort(std::vector<int>& arr, int l, int r) {
	if (l>r) return ;
	int p=partition(arr, l, r);
	quickSort(arr, l, p-1);
	quickSort(arr, p+1, r);
}

int main(int argc, char const *argv[])
{
	std::vector<int> arr={8,7,6,3,5,4,1,2,9,0};
	quickSort(arr, 0, arr.size()-1);
	for (int i:arr) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}