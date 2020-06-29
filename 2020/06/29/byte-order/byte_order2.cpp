#include <iostream>
typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i=0; i<len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void*));
}

int32_t swapInt32(int32_t value) {
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24) ;
}

void read(int data) {
    printf("data is %d\n", data);
    printf("bytes order of data is");   show_int(data);
    char* pa = (char*) &data;
    int big_data = (pa[3]<<0) | (pa[2]<<8) | (pa[1]<<16) | (pa[0]<<24);
    int little_data = (pa[0]<<0) | (pa[1]<<8) | (pa[2]<<16) | (pa[3]<<24);
    printf("big_endian order data is %d\n", big_data);
    printf("little_endian order data is %d\n", little_data);
}

int main(int argc, char const *argv[])
{
    int a = 12345;
    show_int(12345);
    show_float(12345.6789);
    printf("%p\n", &a);
    show_pointer(&a);

    int data = 0x01234567;
    read(data);
    printf("--------After swap bytes order--------\n");
    data = swapInt32(data);
    read(data);
    return 0;
}