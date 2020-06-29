#include <iostream>
using namespace std;

void check() {
	int n = 10;
	printf("%x\n", n);
	char *p = (char*)&n;
	for (int i=0; i<4; ++i) {
		printf("%d %p\n", *(p+i), p+i);
	}
	if (*p==10) {
		cout << "Little-endian in this PC." << endl;
	}
	else {
		cout << "Big-endian in this PC." << endl;
	}

	int x=1;
    if (*(char *) &x ==1)
            printf("Little endian!\n");
    else    printf("Big endian!\n");
}

int32_t swapInt32(int32_t value) {
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24) ;
}

void read(int data) {
	printf("data is %d\n", data);
	char* pa = (char*) &data;
    int big_data = (pa[3]<<0) | (pa[2]<<8) | (pa[1]<<16) | (pa[0]<<24);
    int little_data = (pa[0]<<0) | (pa[1]<<8) | (pa[2]<<16) | (pa[3]<<24);
	printf("big_endian order data is %d\n", big_data);
	printf("little_endian order data is %d\n", little_data);
}

int main(int argc, char const *argv[])
{
	check();
    
	return 0;
}