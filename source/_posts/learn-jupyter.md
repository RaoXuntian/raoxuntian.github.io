---
title: jupyter学习笔记
date: 2020-12-21 16:18:58
updated:
tags:
- jupyter
---

**Jupyter**（[![聆听](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3b/Speakerlink-new.svg/11px-Speakerlink-new.svg.png)](https://upload.wikimedia.org/wikipedia/commons/c/c5/En-us-Jupiter.ogg)**[i](https://zh.wikipedia.org/wiki/File:En-us-Jupiter.ogg)**[/ˈdʒuːpɪtər/](https://zh.wikipedia.org/wiki/Help:英語國際音標)）是一个[非营利组织](https://zh.wikipedia.org/wiki/非营利组织)，旨在“为数十种编程语言的[交互式计算](https://zh.wikipedia.org/w/index.php?title=交互式计算&action=edit&redlink=1)开发[开源软件](https://zh.wikipedia.org/wiki/开源软件)，开放标准和服务”。2014年由Fernando Pérez从[IPython](https://zh.wikipedia.org/wiki/IPython)中衍生出来，Jupyter支持几十种语言的执行环境。Jupyter Project的名称是对Jupyter支持的三种核心编程语言的引用，这三种语言是[Julia](https://zh.wikipedia.org/wiki/Julia_(编程语言))、[Python](https://zh.wikipedia.org/wiki/Python)和[R](https://zh.wikipedia.org/wiki/R语言)，也是对[伽利略](https://zh.wikipedia.org/wiki/伽利略)记录发现[木星的卫星](https://zh.wikipedia.org/wiki/木星的卫星)的笔记本的致敬。Jupyter项目开发并支持交互式计算产品Jupyter Notebook、JupyterHub和JupyterLab，这是Jupyter Notebook的下一代版本。

<!--more-->



### 一.Jupyter中打印所有结果的解决办法

我们都知道，在Jupyter中，除非加上print，每个cell只会显示最后一个输出结果，这里，我们通过加上如下代码，使之打印所有的交互式输出，而不仅仅是最后一个：

```python
from IPython.core.interactiveshell import InteractiveShell
InteractiveShell.ast_node_interactivity = "all"
```



### 参考文章

- [Jupyter中打印所有结果的解决办法](https://blog.csdn.net/m0_37422217/article/details/107032565)

