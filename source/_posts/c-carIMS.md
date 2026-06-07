---
title: A Car Information Management System (车辆信息管理系统) with C
date: 2020-06-17 15:10:05
tags:
- C
---

这几天在家接了个私活，帮一个本科生做C语言课设...难度虽然不大，但回想起我大一时C语言的期末考试，又想起前一阵子看到清华贵系大一C语言课设——雷课堂，看着不同学校不同的标准，感慨万千...



开发环境 Linux + gcc 9.0

无GUI界面

数据结构用的是多层次的十字链表，数据存储在文件当中。

{% asset_img 1.png  image %}

<!-- more -->

主要的操作就是定义结构体，链表的增删查改，文件的读写，模糊查询用到KMP算法。

C定义结构体可以和C++风格一致，但也有属于C自己风格的定义：

```c
typedef struct OrderInfo    // 租车订单信息
{
    char id[20];            // 订单编号
    char clientName[20];    // 客户姓名
    char clientId[20];      // 客户身份证号码
    char clientPhone[20];	// 客户电话号码
    int carNo;          	// 租用的车辆编号
    char startTime[18];     // 取车时间
    float deposit;          // 押金
    char planEndTime[18];   // 预约还车时间
    char actualEndTime[18]; // 实际还车时间
    float planCost;         // 应缴费用
    float actualCost;       // 实缴费用
    struct OrderInfo* next; // 下一个订单
} order;

typedef struct CarInfo  		// 车辆基本信息
{
    int carNo;          		// 车辆编号
    char carId[3];         		// 车辆类型编码   '1'-'5'
    char license[10];   		// 车牌号 
    char carName[20];   		// 车辆名称
    char carWay[10];    		// 排档方式
    float price;        		// 每日租金
    char status[3];        		// 出租状态 'y' 'n'
    order* firstOrder;  		// 此车辆的订单追踪
    struct CarInfo* next;		// 指向同类型的下一个车辆
} car;

typedef struct CarType  		// 车辆分类信息
{
    char carId[3];         		// 车辆类型编码   '1'-'5'
    char type[20];      		// 车辆类型名称
    int count;          		// 库存数量
    struct CarType* next;      		// 下一个车辆分类信息
    car* sub;           		// 此类型车辆的具体车辆信息
} cartype;
```



链表的增删查改，插入的时候一般有头插法和尾插法，就不赘述了。

查询的时候我想用hash结构，但发现C里面并没有哈希表，得自己造轮子……

而且C也没有动态数组……没有容器……都是定义指针、分配地址

说到分配地址，面试的时候面试官可能就会问new和malloc关键词有什么区别？

很显然，new是C++的关键词，而malloc是C的关键词。

new一个对象后一般用delete释放内存，malloc用free释放内存。

new的时候不需要指定内存块的大小，编译器会帮你计算，而malloc需要输入内存块大小，一般用sizeof(obj)。

具体的区别如下：

> 0.       属性
>
> new/delete是C++关键字，需要编译器支持。malloc/free是库函数，需要头文件支持。
>
> 1.       参数
>
> 使用new操作符申请内存分配时无须指定内存块的大小，编译器会根据类型信息自行计算。而malloc则需要显式地指出所需内存的尺寸。
>
> 2.       返回类型
>
> new操作符内存分配成功时，返回的是对象类型的指针，类型严格与对象匹配，无须进行类型转换，故new是符合类型安全性的操作符。而malloc内存分配成功则是返回void * ，需要通过强制类型转换将void*指针转换成我们需要的类型。
>
> 3.       分配失败
>
> new内存分配失败时，会抛出bac_alloc异常。malloc分配内存失败时返回NULL。
>
> 4.      自定义类型
>
>          new会先调用operator new函数，申请足够的内存（通常底层使用malloc实现）。然后调用类型的构造函数，初始化成员变量，最后返回自定义类型指针。delete先调用析构函数，然后调用operator delete函数释放内存（通常底层使用free实现）。
>
>          malloc/free是库函数，只能动态的申请和释放内存，无法强制要求其做自定义类型对象构造和析构工作。
>
> 5.      重载
>
> C++允许重载new/delete操作符，特别的，布局new的就不需要为对象分配内存，而是指定了一个地址作为内存起始区域，new在这段内存上为对象调用构造函数完成初始化工作，并返回此地址。而malloc不允许重载。
>
> 6.       内存区域
>
> new操作符从自由存储区（free store）上为对象动态分配内存空间，而malloc函数从堆上动态分配内存。自由存储区是C++基于new操作符的一个抽象概念，凡是通过new操作符进行内存申请，该内存即为自由存储区。而堆是操作系统中的术语，是操作系统所维护的一块特殊内存，用于程序的内存动态分配，C语言使用malloc从堆上分配内存，使用free释放已分配的对应内存。自由存储区不等于堆，如上所述，布局new就可以不位于堆中。

关于KMP算法，也是面试时候的一个难点，

```c
// KMP算法的辅助数组
void Next(char *T,int *next)
{
    int i=1;
    next[1]=0;
    int j=0;
    while (i<strlen(T)) {
        if (j==0||T[i-1]==T[j-1]) {
            i++;
            j++;
            next[i]=j;
        }else{
            j=next[j];
        }
    }
}

// 模糊查询的核心算法 KMP算法
int KMP(char *S, char *T)
{
    int next[MAX_LINE_SIZE];
    Next(T,next);//根据模式串T,初始化next数组
    int i=1;
    int j=1;
    while (i<=strlen(S)&&j<=strlen(T)) {
        //j==0:代表模式串的第一个字符就和当前测试的字符不相等；S[i-1]==T[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
        if (j==0 || S[i-1]==T[j-1]) {
            i++;
            j++;
        }
        else{
            j=next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
        }
    }
    if (j>strlen(T)) {//如果条件为真，说明匹配成功
        return i-(int)strlen(T);
    }
    return -1;
}
```



C语言文件读取这一块我感觉还是比C++和python麻烦，用fopen选择文件路径和打开的模式(mode)，这里想记录一下，文件读写结构体数据，fwrite()和fread()，如果结构体里有指针，那么这个结构体存入文件再读取的话，指针指向的地址可能已经释放了，成了野指针，所以从文件里读取结构体后需要对指针重新赋值。

```c
// 获取车辆类型信息csv
int read_car_type_csv()     
{
    cartype* p;
    p = p_type_head = (cartype*) malloc (CARTYPESIZE);
    FILE *fp;
    char *filePath = "./output/车辆分类信息表_.csv";
    fp = fopen(filePath, "r");
    if (!fp) 
    {
        fprintf(stderr, "[打开文件『 %s 』失败...]\n", filePath);
        return -1;
    }
    printf("[正在读取%s...]\n", filePath);
    char buff[MAX_LINE_SIZE];
    char *info;
    char *tok;
    info = fgets(buff, MAX_LINE_SIZE, fp);   // 读取csv内容到buff
    //printf("%s\n", buff);
    tok = strtok(buff, ",");
    tok = strtok(NULL, ",");
    tok = strtok(NULL, ",");
    while ((info = fgets(buff, MAX_LINE_SIZE, fp)) != NULL) 
    {
        //printf("%s\n", buff);
        cartype* cur;
        cur = (cartype*) malloc (CARTYPESIZE+1);
        tok = strtok(buff, ",");
        if (tok == NULL) break;
        strcpy(cur->carId, tok);
        tok = strtok(NULL, ",");
        if (tok == NULL) break;
        strcpy(cur->type, tok);
        tok = strtok(NULL, ",");
        if (tok == NULL) break;
        cur->count = atoi(tok);
        cur->sub = NULL;
        p->next = cur;
        p = cur;
        show_car_type(cur);
        //printf("%s | %s | %d\n", cur->carId, cur->type, cur->count);
    }
    p->next = NULL;
    p->sub = NULL;
    printf("[%s读取成功...]\n", filePath);
    fclose(fp);
    return 1;
}
```

C语言太久没接触了，这次写代码感觉经常出现内存方面的问题，通过排查发现绝大多数原因还是指针没有分配地址或者指针指向无效的地址这些原因导致的，所以写C的时候，一定要认真细致啊~

代码: https://github.com/RaoXuntian/c_carIMS