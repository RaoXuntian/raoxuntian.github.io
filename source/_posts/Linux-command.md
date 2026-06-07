---
title: Linux常用命令
date: 2020-07-21 23:33:57
updated:
tags:
- Linux
- interview
---

在实际工作中，许多服务器是Linux操作系统，作为程序员无法避免和Linux打交道，所以在应届生面试的时候，Linux常用指令也是面试官经常考察的一个点。

除了我们常用的`cd`、`ls`，我们应该掌握一些常用的指令

#### 面试常见的Linux指令

<!--more-->

### 1.pwd

- `pwd`:显示当前目录

```bash
[root@izbp1783u2o2usauzn9srez bin]# pwd
/root/miniconda3/bin
```

### 2.mkdir/rmdir

- `mkdir`:建立一个新目录

这个指令在默认的情况下是要一层一层地建立你所需要的目录。默认的时候你要建立的目录的上级目录必须也要存在，如果想一次建立多层目录，可以`-p`选项。

```bash
[root@izbp1783u2o2usauzn9srez ~]# mkdir test1/test2
mkdir: 无法创建目录"test1/test2": 没有那个文件或目录
[root@izbp1783u2o2usauzn9srez ~]# mkdir test1/test2 -p
[root@izbp1783u2o2usauzn9srez ~]# ll |grep test
drwxr-xr-x  3 root root      4096 7月  22 15:45 test1
```

- `rmdir`:删除一个**空**目录

注意这个指令默认是删除一个空目录，加入`-p`选项连同上层“空的”目录也一起删除。

```bash
[root@izbp1783u2o2usauzn9srez ~]# rmdir test1/ <==因为尚有内容，无法删除
rmdir: 删除 "test1/" 失败: 目录非空
[root@izbp1783u2o2usauzn9srez ~]# rmdir test1/test2/ -p
[root@izbp1783u2o2usauzn9srez ~]# ll |grep test
```

如果想把目录下的东西都删除，这个时候可以使用`rm -rf`。

### 3.cp/rm/mv

- `cp`:复制文件或目录

`cp`这个指令很重要的，不同身份者执行这个命令会有不同的结果产生。

```bash
cp [-adfilprsu] 源文件(source) 目标文件(destination)
cp [option] source1 source2 source3 …… directory
选项与参数：
-a	:	相当于-dr --preserve=all的意思（常用）
-d	:	若源文件为链接文件的属性（link file），则复制链接文件属性而非文件本身；
-i	:	若目标文件（destination）已经存在，在覆盖时会先询问操作的进行（常用）；
-p	:	连同文件的属性（权限、用户、时间）一起复制过去，而非使用默认属性（备份常用）；
-r	:	递归复制，用于目录的复制操作（常用）；
最后需要注意的是，如果源文件有两个以上，则最后一个目标文件一定要是“目录”才行。
```



- `rm`:删除文件或目录

```bash
rm [-fir] 文件或目录
选项与参数：
-f	:	就是force的意思，忽略不存在文件，不会出现警告信息；
-I	:	交互模式，在删除前会询问使用者是否操作；
-r	:	递归删除，最常用于目录的删除，这是非常危险的选项。
```

我们在网上经常看到删库跑路的梗`rm -rf /`，现在你应该知道这个命令的意思了吧~



- `mv`:移动文件或目录，或重命名

```
mv [-fiu] source destination
mv [option] source1 source2 source3 …… directory
选项与参数：
-f	:	就是force的意思，如果目标文件以及存在，不会询问而直接覆盖；
-i	:	若目标文件（destination）已经存在，就会询问是否覆盖；
-u	:	若目标文件已经存在，且source比较新，才会更新（update）。
```



### 4.cat/tac/nl/more/less/head/tail/od

- `cat`:从第一行开始显示文件内容。
- `tac`:从最后一行开始显示，可以看出tac是cat的倒着写。
- `nl`:显示的时候，同时输出行号。
- `more`:一页一页地显示文件内容。
- `less`:与more类似，但是比more更好的是，它可以往前翻页。
- `head`:只看前面几行。
- `tail`:只看后面几行。
- `od`:以二进制的方式读取文件内容。



### 5.touch

- `touch`:创建新文件或修改文件时间

`touch`可以创建新文件并不新鲜，但很多人可能不知道它可以修改文件时间，在说修改文件时间之前，我们看看Linux下的文件有哪些时间：

- 修改时间（modification time, mtime）

  当该文件的**内容数据**变更时，就会更新这个时间，内容数据指的是文件的内容，而不是文件的属性或权限。

- 状态时间（status time, ctime）

  当该文件的**状态（status）**改变时，就会更新这个时间，举例来说，像是权限与属性被更改了都会更新这个时间。

- 读取时间（access time, atime）

  当**该文件的内容被读取**时，就会更新这个读取时间（access），举例来说，我们使用cat去读取file.txt，就会更新该文件的atime。

```bash
[root@izbp1783u2o2usauzn9srez ~]# date; ll /etc/man_db.conf; ll --time=ctime /etc/man_db.conf; ll --time=atime /etc/man_db.conf 
2020年 07月 24日 星期五 23:49:14 CST
-rw-r--r--. 1 root root 5171 6月  10 2014 /etc/man_db.conf		<== 这是mtime
-rw-r--r--. 1 root root 5171 8月  18 2017 /etc/man_db.conf		<== 这是ctime
-rw-r--r--. 1 root root 5171 7月  23 03:48 /etc/man_db.conf	<== 这是atime
```

```bash
touch [-acdmt] 文件
参数：
-a : 仅修改访问时间。
-c : 仅修改文件的时间，若该文件不存在则不新建文件。
-d : 后面可以接欲修改的日期而不使用目前的日期。
-m : 仅修改 mtime。
-t : 后面可以接欲修改的时间而不用目前的时间，格式为[YYMMDDhhmm]。
```

无论如何，`touch`这个命令最常被使用的情况是：

- 建立一个空文件
- 将某个文件日期自定义为目前（mtime和atime）



### 6.find

- `find`:查找某路径下指定文件。

```bash
find /root（路径） -name 文件名
find /root（路径） -mtime 0 当前目录下查找今天之内有改动的文件  
-mtime +n : 列出在n天之前（不含n天本身）被更改过的文件名；  
-mtime -n : 列出在n天之内（含n天本身）被更改过的文件名；
```



### 7.grep/wc

- `grep`:文本搜索

```bash
语法：grep 参数 查找条件 文件名（注：是文件名，目录名下查找不行）
主要参数：
－i：不区分大小写(只适用于字母字符。）
－l：查询多文件时只输出包含匹配字符的 文件名。
－n：显示匹配行内容及行号。
```

- `wc`:统计字数

```bash
wc [-clw][--help][--version][文件...]
参数：
-c或--bytes或--chars 只显示Bytes数。
-l或--lines 只显示行数。
-w或--words 只显示字数。
--help 在线帮助。
--version 显示版本信息。
```

在默认的情况下，wc将计算指定文件的行数、字数，以及字节数。使用的命令为：

```bash
(base) saladdays@MacBook-Pro _posts % wc learnCpp-static.md 
     222     516    9427 learnCpp-static.md
```



找出某个文件里关键字出现的次数

```bash
grep 字符串 文件名 | wc -l
```



### 8.ps/top/kill

- `ps`:查看进程，显示系统中进程的信息。包括进程ID、控制进程终端、执行时间和命令。

- `top`:显示当前系统正在执行的进程的相关信息，包括进程ID、内存占用率、CPU占用率等。

  top命令是Linux下常用的性能分析工具，能够实时显示系统中各个进程的资源占用状况，类似于Windows的任务管理器。

- `kill`:杀死进程。

### 9.netstat/lsof

- `netstat`:常用于查看路由表，显示各种网络相关信息，如网络连接，路由表，接口状态(Interface Statistics),masquerade连接，多播成员。

```bash
命令参数

注：netstat命令默认是不显示LISTEN状态的网络连接和LISTEING状态的UNIX域连接，只有使用带-a或者-l参数的命令才能显示出来。

    -a (all)显示所有状态的连接
    -t (tcp)仅显示tcp相关连接
    -u (udp)仅显示udp相关连接
    -n 拒绝显示别名，能显示数字的全部转化成数字。
    -l 仅列出有在监听状态的连接

    -p 显示建立相关链接的程序名
    -r 显示路由信息，路由表
    -e 显示扩展信息，例如uid等
    -s 按各个协议进行统计
    -c 每隔一个固定时间，执行该netstat命令。

```

```bash
常用命令参考

a、列出所有连接（包括监听和未监听状态）

    命令：netstat -a；列出所有状态下的连接

    命令：netstat -at；列出所有状态下的tcp连接

    命令：netstat -au；列出所有状态下的udp连接 

    命令：netstat -ax；列出所有状态下的UNINX域连接

b、列出处于LISTEN状态的连接

    命令：netstat -l；列出所有处于LISTEN状态的连接

    命令：netstat -lt；列出所有处于LISTEN状态的tcp连接

    命令：netstat -lu；列出所有处于LISTEN状态的udp连接

    命令：netstat-lx；列出所有处于LISTENING状态的UNIX域连接

c、统计通信协议连接信息

    命令：netstat -s；统计所有连接的通信协议连接信息

    命令：netstat -st；统计基于tcp连接的通信协议连接信息

    命令：netstat -su；统计基于udp连接的通信协议连接信息

d、输出中显示进程ID和进程名信息（可搭配其他参数使用）

    命令：netstat -p；列出除LISTEN和LISTENING状态下的连接，包含连接所属进程的进程ID和进程名

    命令：netstat -tp；列出除LISTEN和LISTENING状态下的tcp连接，包含连接所属进程的进程ID和进程名

    命令：netstat -up；列出除LISTEN和LISTENING状态下的udp连接，包含连接所属进程的进程ID和进程名

e、动态输出连接信息

    命令：netstat -c；每间隔一秒输出当前连接信息

f、列出特定的连接

    命令：netstat -ap|grep postgres

```

- `lsof`:查端口

```bash
lsof -i:443 #显示所有打开443端口的进程
netstat -an | grep tcp | grep 80
```



### 10.scp

- `scp`:通过网络在两台主机之间拷贝文件，可以支持Windows。

```bash
scp local_file remote_username@remote_ip:remote_folder #本地复制到远程，文件未重命名。
scp local_file remote_username@remote_ip:remote_file #本地复制到远程，文件重命名。
scp local_file remote_ip:remote_folder #未指定用户名，执行后需输入用户名和密码，未修改文件名进行移动文件。
scp local_file remote_ip:remote_file #未指定用户名，执行后需输入用户名和密码，修改文件名进行移动文件。

参数：
-r 递归拷贝指定的整个文件夹。
```

从远程复制到本地，只需要将上述命令的后2个参数调换顺序就可以了。
 相比于CP命令，主要就是在source跟dest之前加上remote_username@remote_ip:，通过加的位置的不同区分出到底从远程到本地还是本地到远程。



### 11.tar/zip

- `tar`:打包/压缩文件
- `zip`:打包/压缩文件

详见：

[打包 压缩 命令tar zip](https://www.cnblogs.com/centos2017/p/7896807.html)

[Linux中常用的tar解压打包命令语法介绍](https://blog.csdn.net/guo_qiangqiang/article/details/87934655)

### 12.chmod

- `chmod`:改变文件的权限

```bash
语法：chmod [options] mode files 
options：-R 可递归遍历子目录，把修改应到目录下所有文件和子目录 
who：u 用户 、 g 组 、o 其他 、a 所有用户 
opcode：+ 增加权限 、 - 删除权限 、= 重新分配权限 
permission： r 读 、w 写 、 x 执行
```

我们多数用三位八进制数字的形式来表示权限，第一位指定属主的权限，第二位指定组权限，第三位指定其他用户的权限，每位通过4(读)、2(写)、1(执行)三种数值的和来确定权限。如6(4+2)代表有读写权，7(4+2+1)有读、写和执行的权限

```bash
 chmod u+x file ：给file的属主增加执行权限

 chmod 751 file ：给file的属主分配读、写、执行(7)的权限，给file的所在组分配读、执行(5)的权限，给其他用户分配执行(1)的权限

 chmod u=rwx,g=rx,o=x file ：上例的另一种形式
```



### 参考文章

- [面试常见的Linux命令及问题整理](https://blog.csdn.net/zlx312/article/details/79398557)
- [Linux文件操作高频使用命令](https://blog.csdn.net/gexiaoyizhimei/article/details/100122368)
- [linux命令——ps和netstat](https://blog.csdn.net/jjwyll/article/details/62091307)
- [Linux如何查看进程、杀死进程、启动进程等常用命令](https://blog.csdn.net/wojiaopanpan/article/details/7286430)
- [每天一个linux命令（44）：top命令](https://www.cnblogs.com/peida/archive/2012/12/24/2831353.html)
- [linux中scp命令的使用](https://www.jianshu.com/p/552322d2c412)
- [打包 压缩 命令tar zip](https://www.cnblogs.com/centos2017/p/7896807.html)
- [Linux中常用的tar解压打包命令语法介绍](https://blog.csdn.net/guo_qiangqiang/article/details/87934655)



