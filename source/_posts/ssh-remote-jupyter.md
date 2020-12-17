---
title: 远程访问服务器上的jupyter notebook
date: 2020-12-17 10:46:06
updated:
tags:
- ssh
- jupyter
---

从北京回到武汉了，开始水我的毕业论文了。毕业论文需要用到神经网络训练模型，这个不用说，自己的机子肯定带不动，要连接实验室的服务器。运行深度学习的代码，习惯使用jupyter notebook，因此需要远程访问服务器上的jupyter notebook。在网上搜了几种远程访问的方法，有的成功了，有的估计因为实验室内网IP等原因没有成功……

<!--more-->

### 一.ssh远程使用jupyter notebook

1. 在远程服务器上，启动jupyter notebooks服务：

   ```
   jupyter notebook --no-browser --port=8889
   ```

2. 在本地终端中启动SSH：

   ```shell
   ssh -N -f -L localhost:8888:localhost:8889 username@serverIP
   ```

   其中： -N 告诉SSH没有命令要被远程执行； -f 告诉SSH在后台执行； -L 是指定port forwarding的配置，远端端口是8889，本地的端口号的8888。

3. 最后打开浏览器，访问：http://localhost:8888/

### 二. 利用jupyter notebook自带的远程访问功能

官方指南在此：[官方指南](http://jupyter-notebook.readthedocs.io/en/latest/public_server.html#notebook-server-security)

1. 生成默认配置文件

   ```shell
   jupyter notebook --generate-config
   ```

2. 生成访问密码(token)
   终端输入`ipython`，设置你自己的jupyter访问密码，注意复制输出的`sha1:xxxxxxxx`密码串

   ```python
   In [1]: from notebook.auth import passwd
   In [2]: passwd()
   Enter password:
   Verify password:
   Out[2]: 'sha1:xxxxxxxxxxxxxxxxx'
   ```

3. 修改`./jupyter/jupyter_notebook_config.py`中对应行如下

   ```json
   c.NotebookApp.ip='*'
   c.NotebookApp.password = u'sha:ce...刚才复制的那个密文'
   c.NotebookApp.open_browser = False
   c.NotebookApp.port =8888 #可自行指定一个端口, 访问时使用该端口
   c.NotebookApp.allow_remote_access = True
   ```

4. 在服务器上启动`jupyter notebook`

   ```shell
   jupyter notebook
   ```

5. 最后打开浏览器，访问：http://ip:8888/

这个方法在第3步的时候做过很多尝试，似乎还是无法从本地访问服务器的8888端口，一开始以为是防火墙的问题，后面关闭防火墙了还是不太行，所以这个方法我一直没试成功……

### 三.ssh添加隧道

关于ssh隧道，原理参考：[SecureCRT高效操作——反空闲、按钮栏、端口转发跳板](https://juejin.cn/post/6844903946096476173#heading-4)

Windows上有很多远程连接的软件是支持添加隧道的，但在Mac上并不多，一开始是在用FinalShell。

如下就是我自己配置的隧道：

{% asset_img 1.png  image %}

通过有隧道连接的ssh服务器之后，在服务器端运行

```shell
jupyter notebook --no-browser --port=8889
```

然后打开浏览器，登陆对应的IP地址，即可访问远程jupyter notebook。



### #参考文章

- [远程访问服务器Jupyter Notebook的两种方法](https://www.jianshu.com/p/8fc3cd032d3c)
- [SecureCRT高效操作——反空闲、按钮栏、端口转发跳板](https://juejin.cn/post/6844903946096476173#heading-4)

