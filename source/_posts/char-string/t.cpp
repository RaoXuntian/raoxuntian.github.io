#include <cstdio>
#include <cstring>
int main(int argc, char const *argv[])
{
	
	{	// ASCII码
		for (int i=32; i<128; ++i) {
			printf("[%3d -> %c] ", i, i);
			if (i%10==0) printf("\n");
		}
	}
	
	{
		char a[] = {'h','e','l','l','o','~'};
		char c[] = "hello~";
		char ch[10] = "Hello~";

		printf("%lu\n", sizeof(a));
		for (int i=0; i<sizeof(a); ++i) {
			printf("%c ", a[i]);
		}
		printf("\n%lu\n", sizeof(c));
		for (int i=0; i<sizeof(c); ++i) {
			printf("%c ", c[i]);
		}
		printf("\n%lu\n", sizeof(ch));
		for (int i=0; i<sizeof(ch); ++i) {
			printf("%c ", ch[i]);
		}
		
		strcpy(a, "world");
		strcpy(ch, "world");
		printf("\n%s %s\n", a, ch);
		printf("%p %p %p\n", a, c, ch);
	}
	
	{
		char* p;
		char ch[10] = "hello~";
		int a[4] = {1,0,3,7};
		int* pa = &a[0];
		printf("sizeof(p)==%lu\n", sizeof(p));
		printf("sizeof(ch)==%lu\n", sizeof(ch));
		printf("sizeof(pa)==%lu\n", sizeof(pa));
		printf("sizeof(a)==%lu\n", sizeof(a));
		
		p = ch;
		printf(" p ==%p\n", p);
		printf("ch ==%p\n", ch);
		printf("&p ==%p\n", &p);
		printf("&ch==%p\n", &ch);

		printf(" a ==%p\n", a);
		printf("pa ==%p\n", pa);
		printf("&a ==%p\n", &a);
		printf("&pa==%p\n", &pa);

		//char* p1 = &ch;
		char* p1 = &ch[0];
		char (*p2)[10] = &ch;
		printf("%c\n", p2[0][1]);
		printf("%c\n", (*p2)[1]);

		ch[1] = 'E';
		printf("%s\n", ch);
	}

	{
		//char* p0 = "C++!!!";
		const char* p0 = "C++!!!";
		p0 = "JAVA~";
		//*p0 = "Python...";
		//p0[1] = 'a';
		char ch[] = "Gooooo";
		//char* p1 = &ch[0];
		char* p1 = ch;
		p1[3] = 'O';
		printf("%s\n", ch);
		strcpy(p1, "Golang");
		printf("%s %s\n", p1, ch);
	}
	return 0;
}