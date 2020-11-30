---
title: item2自动连接远程服务器
date: 2020-11-30 15:43:45
updated:
tags:
- item2
---

用了5年的MacBook，一直用的是系统自带的terminal 终端。对于item2也略有耳闻，但没有去研究它。实习期间一直在用SecureCRT，实习结束之后，面对原生自带的终端，感觉到十分不友好，遂决定改用item2……

### 一.新增item2配置文件

{% asset_img 1.png  image %}

<!--more-->

在第三步那里，我们需要在对应的目录`~/.ssh/`下面新建(touch)文件xxx来记录远程服务器的相关配置。

### 二.配置远程服务器相关文件

```bash
#!/usr/bin/expect -f
set host 192.168.100.119(服务器ip地址)
set user root(登录服务器的用户名)
set password admin(登录服务器的密码)
#set timeout -1

spawn ssh $user@$host
expect "*assword:*"
send "$password\r"
interact
expect eof
```

### 三.配置完成直接连接

{% asset_img 2.png  image %}



### 参考文章

- [mac下面iterm2自动连接远程服务器](https://www.jianshu.com/p/d75dc43be7a7)

