---
title: 猿辅导二面面经
date: 2020-09-05 11:28:08
updated:
tags:
- interview
- mysql
- 计算机网络
---

2020.9.5早上九点猿辅导二面，问的问题不多，但感觉问的挺好，还让我手撕一道链表的题目，没有找到最优解，十分钟的时间用暴力的方法写出代码，自己觉得不是很满意。事后诸葛亮，最优解总在面试完突然想到，把自己蠢哭了，一顿捶胸顿足之后决定记一下这道题目。

顺便再记一些面试官问的网络和数据库的问题，用倒叙的手法整理成一篇面经吧。

<!--more-->

### 代码

题目：

给出一条单链表：1->2->3->4->5->NULL

交叉首尾交叉变成：1->5->2->4->3->NULL

**要求空间复杂度O(1).**

当时比较紧张，想到递归的方法，时间复杂度O(n*n)。面试官让我想想能不能优化一下时间复杂度，达到O(NlogN)甚至O(N)。当时时间不够，我说O(N)应该可以，又不是遍历一遍，遍历2遍3遍也是O(N)，但时间不允许我继续思考。面试结束后点完外卖再看一眼草稿纸，突然就想明白了 = =

1. 我们可以第一遍遍历链表，得到链表的长度n

2. 第二遍遍历将链表从中间（(n+1)/2）的地方断开

   1->2->3->NULL  4->5->NULL

3. 将后半段的链表翻转

   1->2->3->NULL  5->4->NULL

4. 将两段链表原地合并

5. 再考虑一下边界条件

```cpp
#include <iostream>

using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x): val(x), next(nullptr) {};
};

ListNode* reverse(ListNode* head) {
	if (head==nullptr || head->next==nullptr) return head;
	ListNode* nex = head->next;
	ListNode* ans = reverse(nex);
	nex->next = head;
	head->next = nullptr;
	return ans;
}

ListNode* solve(ListNode* head) {
	ListNode* p = head;
	int cnt = 0;
	while (p!=nullptr) {
		++cnt;
		p = p->next;
	}
	if (cnt<3) return head;
	p = head;
	int stop=1;
	while (stop++<(cnt+1)/2) {
		p = p->next;
	}
	ListNode* last = reverse(p->next);
	p->next = nullptr;
	p = head;

	ListNode* q = last;
	while (q!=nullptr) {
		ListNode* tmp = p->next;
		p->next = q;
		q = q->next;
		p->next->next = tmp;
		p = tmp;
	}
	return head;
}

int main(int argc, char const *argv[])
{
	ListNode* head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);
	head->next->next->next->next->next = new ListNode(6);
	ListNode* p = solve(head);
	ListNode* cur = p;
	while (cur!=nullptr) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	cout << endl;
	return 0;
}
```

最后面试官问我这个程序如果要做测试需要考虑什么情况，我说什么奇数偶数个节点的情况，空节点单节点非常多（内存塞不下）节点的情况，面试官提示我有一种链表独有的需要考虑的情况，我立马想到了，是**循环链表**。这个程序没有考虑对循环链表的检测，所以有兴趣的同学可以自行考虑一下输入循环链表会发生什么。

### 数据库

面试的时候，面试官问我数据库掌握到什么程度，要如实的说。我就说，在项目中用过MySQL和MongoDB，但数据量不大不足以使用索引，对索引不熟悉。数据库的书也看了，八股文面经那些也背了，你问吧……

面试官：那好，那我就问一个你应该从来没遇见过的、面经上也没有的问题吧

```sql
CREATE TABLE `table_a` (
 `name` VARCHAR/INTEGER ,
 INDEX index_name (`name`),
)
SELECT * FORM table_a
WHERE name = 1;
WHERE name = '1';
```

面试官洋洋洒洒地在屏幕上打了几行SQL的语法，说到：我现在有个表格，里面有索引name，name如果是VARCHAR类型索引的时候，我查找数据，`WHERE name = 1;` 查找索引条件给name的是个INT，那你说一下这次查询能成功吗？反过来，如果name是个INT索引，我查询的索引条件是`WHERE name = '1';`给它一个VARCHAR类型索引查询，会发生什么呢？

通过查阅资料，我总结了一下，直接说结论吧：

前者，字段name是VARCHAR类型索引，但在查询的时候，name传入的类型是INT，会导致**索引失效**，执行的是**全表查询**。

后者，字段name是INT类型索引，查询时name传入的类型是VARCHAR不会导致索引失效，依然可以根据索引进行查询。

好的，我们做个实验吧，用explain来进行分析。

（1）新建测试表、索引

```sql
CREATE TABLE index_test_1 (
id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT,
str_test VARCHAR(100) NOT NULL DEFAULT '',
num_test INT(11) NOT NULL DEFAULT '0',
other_test  VARCHAR(200) DEFAULT NULL,
PRIMARY KEY(id),
KEY idx_str (str_test),
KEY idx_num (num_test)
)ENGINE=INNODB DEFAULT CHARSET=utf8;
```

（2）插入测试数据

```sql
INSERT INTO index_test_1(str_test,num_test,other_test) VALUE("111", 111, "测试数据1");
INSERT INTO index_test_1(str_test,num_test,other_test) VALUE("111", 111, "测试数据2");
INSERT INTO index_test_1(str_test,num_test,other_test) VALUE("222", 222, "测试数据3");
```

（3）int类型输入，分别使用idx_num和idx_str两种索引查看执行计划

idx_num对应的num_test字段类型是int；执行计划如下图：

```sql
mysql> explain select * from index_test_1
    -> where num_test = 111;
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
| id | select_type | table        | partitions | type | possible_keys | key     | key_len | ref   | rows | filtered | Extra |
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | index_test_1 | NULL       | ref  | idx_num       | idx_num | 4       | const |    2 |   100.00 | NULL  |
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
1 row in set, 1 warning (0.00 sec)
```

idx_str对应的str_test字段类型是varchar；执行计划如下图：

```sql
mysql> explain select * from index_test_1
    -> where str_test = 111;
+----+-------------+--------------+------------+------+---------------+------+---------+------+------+----------+-------------+
| id | select_type | table        | partitions | type | possible_keys | key  | key_len | ref  | rows | filtered | Extra       |
+----+-------------+--------------+------------+------+---------------+------+---------+------+------+----------+-------------+
|  1 | SIMPLE      | index_test_1 | NULL       | ALL  | idx_str       | NULL | NULL    | NULL |    3 |    33.33 | Using where |
+----+-------------+--------------+------------+------+---------------+------+---------+------+------+----------+-------------+
1 row in set, 3 warnings (0.00 sec)
```

从两个执行计划很明显的发现，idx_str索引的执行计划中key=null，ref=null，rows=3；没有使用到索引

（4）varchar类型输入，分别使用idx_num和idx_str两种索引查看执行计划

idx_num对应的num_test字段类型是int；执行计划如下图：

```sql
mysql> explain select * from index_test_1
    -> where num_test = '111';
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
| id | select_type | table        | partitions | type | possible_keys | key     | key_len | ref   | rows | filtered | Extra |
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | index_test_1 | NULL       | ref  | idx_num       | idx_num | 4       | const |    2 |   100.00 | NULL  |
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
1 row in set, 1 warning (0.00 sec)
```

idx_str对应的str_test字段类型是varchar；执行计划如下图：

```sql
mysql> explain select * from index_test_1
    -> where str_test = '111';
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
| id | select_type | table        | partitions | type | possible_keys | key     | key_len | ref   | rows | filtered | Extra |
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
|  1 | SIMPLE      | index_test_1 | NULL       | ref  | idx_str       | idx_str | 302     | const |    2 |   100.00 | NULL  |
+----+-------------+--------------+------------+------+---------------+---------+---------+-------+------+----------+-------+
1 row in set, 1 warning (0.00 sec)
```

从两个执行计划看出，varchar类型输入，不管索引字段是int还是varchar都可以使用索引。

**说明：**

为什么varchar类型输入，索引是int类型或者是varchar类型的字段，都能生效呢？

原因是mysql在执行的时候，会将数值**隐式转换**，但是这个操作会有无法命中索引的风险。隐式转换还有其他的风险，比如sql注入、多查数据、多删数据等，所以大家在写sql时一定要细心。

#### 隐式转换的规则

- 如果一个或两个参数都是NULL，比较的结果是NULL，除了NULL安全的<=>相等比较运算符。对于NULL <=> NULL，结果为true。不需要转换
- 如果比较操作中的两个参数都是字符串，则将它们作为字符串进行比较。
- 如果两个参数都是整数，则将它们作为整数进行比较。
- 如果不与数字进行比较，则将十六进制值视为二进制字符串
- 如果其中一个参数是十进制值，则比较取决于另一个参数。 如果另一个参数是十进制或整数值，则将参数与十进制值进行比较，如果另一个参数是浮点值，则将参数与浮点值进行比较
- 如果其中一个参数是TIMESTAMP或DATETIME列，另一个参数是常量，则在执行比较之前将常量转换为时间戳。
- **在所有其他情况下，参数都是作为浮点数（实数）比较的。**

所以我们继续刚刚的实验，如果我继续添加几行来看看MySQL是如何在VARCHAR和INT之间发生隐式转换的。

 {% asset_img 1.png  image %}

### 网络

网络这一块，面试官貌似是抓住了我在HTTP的GET和POST方面不熟悉的弱点，一个劲地死怼，连问三道关于GET和POST的问题。

0. TCP三次握手，服务器端可以像客户端发起连接吗？

   不能，服务器端找不到客户端的IP地址。

1. GET和POST有什么区别？

   答：GET 用于HTTP的包头（URL）获取资源，而 POST 用于HTTP的正文传输实体主体。

   GET明文传输，POST可明可密（这个回答是错的）。。然后面试官热情地跟我普及不考虑HTTPS两者都是明文。虽说一个信息在头部，一个信息在主体，一旦被黑客拦截了，还是赤裸裸的明文暴露在外面。

2. 可以用POST去模仿/替代（有点忘了，大概就这么个意思）GET请求吗？

   这个就要扯到POST和GET的底层本质了。

   GET 和 POST 是什么？HTTP 协议中的两种发送请求的方法。

   HTTP 是什么？HTTP 是基于 TCP/IP 的关于数据如何在万维网中如何通信的协议。

   HTTP 的底层是 TCP/IP。所以 GET 和 POST 的底层也是 TCP/IP，也就是说，GET/POST 都是 TCP 链接。GET 和 POST 能做的事情是一样一样的。你要给 GET 加上 request body，给 POST 带上 url 参数，技术上是完全行的通的。

3. GET请求的长度大小有限制吗？

   业界不成文的规定是，（大多数）浏览器通常都会限制 url 长度在 2K 个字节，而（大多数）服务器最多处理 64K 大小的 url。

### 参考文章

- [mysql索引字段类型int和varchar的不同使用](https://blog.csdn.net/qq_18977307/article/details/101069053)
- [MySQL 性能优化神器 Explain 使用分析](https://segmentfault.com/a/1190000008131735)
- [Mysql引起索引失效的原因总结](https://blog.csdn.net/hehexiaoxia/article/details/54312130?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.channel_param)
- [MySQL SQL优化之字符串索引隐式转换](https://www.cnblogs.com/yuyue2014/p/4014330.html)
- [Mysql 数据类型隐式转换规则](https://segmentfault.com/a/1190000012500447)
- [99%的人都理解错了 HTTP 中 GET 与 POST 的区别](https://learnku.com/articles/25881)
- [http请求的url或body或header有长度或大小的限制吗？](https://blog.csdn.net/kris_lh123/article/details/101062026)

