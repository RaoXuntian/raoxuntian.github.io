---
title: git常用指令小结
date: 2020-06-02 00:38:02
tags: 
	- git
---

<!--
<font face="黑体" size=6>Git常用指令小结</font>
-->

废话不多说，直接总结，方便自己以后查~


## 1.获得项目的git仓库

### 1.1通过git init初始化本地的新仓库

```bash
mkdir git
cd git
git init # 初始化git仓库
```
<!-- more -->
### 1.2通过git clone克隆已有的仓库

```bash
git clone [url]
```

比如克隆一个具体的项目：

```bash
git clone https://github.com/RaoXuntian/raoxuntian.github.io.git
```

如果希望在克隆的时候，自己定义要新建的项目目录名称，可以在上面的命令末尾指定新的名字：

```bash
git clone https://github.com/RaoXuntian/raoxuntian.github.io.git myBlog
```

如果希望克隆时直检出指定的分支，可以指定 `-b <分支名>` 选项，如下：

```bash
git clone -b hexo https://github.com/RaoXuntian/raoxuntian.github.io.git myBlog
```

通常clone命令会把整个仓库的(包含所有分支的)版本数据给克隆下来，如果只想获取某个分支的版本数据，只需要加上 `--single-branch`选项，如下：

```bash
git clone --single-branch -b hexo https://github.com/RaoXuntian/raoxuntian.github.io.git myBlog
```

如果你想在克隆仓库时给仓库设置一些不同于全局的git配置，可以通过 `--config` 选项，其简写选项是 `-c`，比如，你想给克隆的仓库设置 用户名 和 邮箱：

```bash
git clone --config user.name=小饶 -c user.email=raoxuntian@gmail.com https://github.com/RaoXuntian/raoxuntian.github.io.git myBlog
```



## 2.添加跟踪文件、暂存

用命令git add告诉Git，把文件添加到仓库(实际上就是把文件修改添加到暂存区)：

```bash
git add filename

git add -A
```



## 3.提交更新

用命令git commit告诉Git，把文件提交到仓库(实际上就是把暂存区的所有内容提交到当前分支)：

```bash
git commit -m "有意义的附加说明"
```



## 4.检测当前工作区状态

```bash
git status

git status -sb
```



## 5.查看修改内容

```bash
git diff
```



## 6.移除文件

要从 Git 中移除某个文件，就必须要从已跟踪文件清单中移除（确切地说，是从暂存区域移除），然后提交。可以用 `git rm` 命令完成此项工作，并连带从工作目录中删除指定的文件，这样以后就不会出现在未跟踪文件清单中了，如：

```bash
git rm 文件
```

如果删除之前修改过并且已经放到暂存区域的话，则必须要用强制删除选项 -f（译注：即 force 的首字母），以防误删除文件后丢失修改的内容。

另外一种情况是，我们想把文件从 Git 仓库中删除（亦即从暂存区域移除），但仍然希望保留在当前工作目录中。换句话说，仅是从跟踪清单中删除。比如一些大型日志文件或者一堆.a 编译文件，不小心纳入仓库后，要移除跟踪但不删除文件，以便稍后在 .gitignore 文件中补上，用 --cached 选项即可：

```bash
git rm --cached 文件
```

后面可以列出文件或者目录的名字，也可以使用 glob 模式。比方说：

```bash
git rm log/\*.log
```

注意到星号 * 之前的反斜杠 \，因为 Git 有它自己的文件模式扩展匹配方式，所以我们不用 shell 来帮忙展开（译注：实际上不加反斜杠也可以运行，只不过按照 shell 扩展的话，仅仅删除指定目录下的文件而不会递归匹配。上面的例子本来就指定了目录，所以效果等同，但下面的例子就会用递归方式匹配，所以必须加反斜杠。）。此命令删除所有log/ 目录下扩展名为 .log 的文件。类似的比如：

```bash
git rm \*~
```

会递归删除当前目录及其子目录中所有 ~ 结尾的文件。



## 7.查看历史

```bash
git log

git log --pretty=oneline   #——要求版本信息只能在一行中显示
```



## 8.撤销修改

### 8.1修改最后一次提交

```undefined
git commit --amend
```

此命令将使用当前的暂存区域快照提交。如果刚才提交完没有作任何改动，直接运行此命令的话，相当于有机会重新编辑提交说明，但将要提交的文件快照和之前的一样。
 如果刚才提交时忘了暂存某些修改，可以先补上暂存操作，然后再运行 `--amend` 提交：

```bash
git commit -m 'initial commit'
git add forgotten_file
git commit --amend
```

上面的三条命令最终只是产生一个提交，第二个提交命令修正了第一个的提交内容。

### 8.2取消已经暂存的文件

```bash
git reset HEAD <file>…
```

### 8.3取消对文件的修改

```bash
git checkout -- <file>…
```

命令git checkout -- filename意思就是，把filename文件在工作区的修改全部撤销，这里有两种情况：

一种是filename自修改后还没有被放到暂存区，现在，撤销修改就回到和版本库一模一样的状态；

一种是filename已经添加到暂存区后，又作了修改，现在，撤销修改就回到添加到暂存区后的状态。

总之，就是让这个文件回到最近一次git commit或git add时的状态。

场景1：当你改乱了工作区某个文件的内容，想直接丢弃工作区的修改时，用命令git checkout -- file。

git checkout其实是用版本库里的版本替换工作区的版本，无论工作区是修改还是删除，都可以“一键还原”。

场景2：当你不但改乱了工作区某个文件的内容，还添加到了暂存区时，想丢弃修改，分两步，第一步用命令git reset HEAD file，就回到了场景1，第二步按场景1操作。

场景3：已经提交了不合适的修改到版本库时，想要撤销本次提交，版本回退，不过前提是没有推送到远程库。



## 9.移动文件

```bash
git mv 文件_from  文件_to
```

其实，运行 git mv 就相当于运行了下面三条命令：

```bash
mv  文件_from  文件_to 
git rm  文件_from 
git add  文件_to
```



## 10.远程仓库

### 10.1查看当前远程库

```bash
git remote
```

查看当前配置的远程仓库。它会列出每个远程库的简短名字。在克隆完某个项目后，至少可以看到一个名为 origin 的远程库，Git 默认使用这个名字来标识你所克隆的原始仓库；

```bash
 -v ：（译注：此为 --verbose 的简写，取首字母），显示对应的克隆地址，提供更多信息；
```

### 10.2添加远程仓库

```bash
 git remote add [仓库名] [url]
```

添加一个新的远程仓库，指定名字为 `仓库名`，以便将来引用；

### 10.3从远程仓库抓取数据

```bash
git fetch [远程仓库名]
```

此命令会到名为 `远程仓库名` 的远程仓库中拉取所有你本地仓库中还没有的数据。运行完成后，你就可以在本地访问该远程仓库中的所有分支，将其中某个分支合并到本地，或者只是取出某个分支，一探究竟。

如果是克隆了一个仓库，此命令会自动将远程仓库归于 origin 名下。所以，`git fetch origin` 会抓取从你上次克隆以来别人上传到此远程仓库中的所有更新（或是上次 fetch 以来别人提交的更新）。有一点很重要，需要记住，fetch 命令只是将远端的数据拉到本地仓库，并不自动合并到当前工作分支，只有当你确实准备好了，才能手工合并。
 如果设置了某个分支用于跟踪某个远端仓库的分支，可以使用 `git pull`  命令自动抓取数据下来，然后将远端分支自动合并到本地仓库中当前分支。在日常工作中我们经常这么用，既快且好。实际上，默认情况下 `git clone` 命令本质上就是自动创建了本地的 master 分支用于跟踪远程仓库中的 master 分支（假设远程仓库确实有 master 分支）。所以一般我们运行 `git pull`，目的都是要从原始克隆的远端仓库中抓取数据后，合并到工作目录中的当前分支。

### 10.4推送数据到远程仓库

```bash
git push [远程仓库S] [本地分支L]:[远程分支R]
```

表示：把 `本地分支L` 推送到 `远程仓库S` 的 `远程分支R` 中，如果 `远程仓库S` 中不存在 `远程分支R`，则会在 `远程仓库S` 中 创建 `远程分支R` 并把 `本地分支L` 推送到 `远程分支R` 中；如果本地分支L和远程分支R名字相同，则可以简写为：

```bash
git push [远程仓库S] [本地分支L]
```

只有在所克隆的服务器上有写权限，或者同一时刻没有其他人在推数据，这条命令才会如期完成任务。如果在你推数据前，已经有其他人推送了若干更新，那 你的推送操作就会被驳回。你必须先把他们的更新抓取到本地，合并到自己的项目中，然后才可以再次推送。

### 10.5删除远程分支

```bash
git push [远程仓库S] :[远程分支R]
```

这个命令的格式意义比较无理头，为了方便记忆，可以这样理解：它是省略了本地分支名的推送命令 `git push [远程仓库S] [本地分支L]:[远程分支R]`，省略 `本地分支L` 表示：在这里提取空白然后把它变成 `远程分支R`。

### 10.6查看远程仓库信息

```bash
git remote show [远程仓库名]
```

查看名为 `远程仓库名` 的远程仓库的详细信息

### 10.7远程仓库的重命名

```bash
 git remote rename  [远程仓库旧名]   [远程仓库新名]
```

修改某个远程仓库在本地的名称（新版 Git 中支持）；
注意，对远程仓库的重命名，也会使对应的分支名称发生变化;

### 10.8远程仓库的删除

```bash
git remote rm  [远程仓库名]
```

### 10.9本地仓库同步远程仓库

```bash
git remote add origin https://github.com/RaoXuntian/raoxuntian.github.io.git	# 本地添加远程仓库
git push -u origin master:hexo	# 本地master分支同步到远程的hexo分支
```

## 11.分支

### 11.1新建分支

```bash
git branch  [分支名]
```

注意：此命令仅仅是建立了一个新的分支，但不会自动切换到这个分支中去；

### 11.2切换分支

```bash
git checkout [分支名]
```

### 11.3新建并切换分支

```bash
git checkout -b [分支名]
```

相当于以下2条命令：

```bash
git branch [分支名]
git checkout [分支名]
```

### 11.4合并分支

设当前分支为A

```bash
git merge [分支B]
```

此命令表示，把分支B合并到分支A

### 11.5删除分支

```bash
git branch -d [分支名]
```

### 11.6强制删除分支

```bash
git branch -D [分支名]
```

### 11.7查看当前分支列表

```bash
git branch
git branch -a # 包括远端的分支
```

返回结果如下：

```undefined
* master
  remotes/origin/hexo
```

带有 `*` 的分支表示是当前所在的分支；

### 11.8查看各个分支最后一次提交对象的信息

```bash
git branch -v
```

###  11.9查看已经合并到当前所在分支的分支

```bash
git branch --merged
```

### 11.10查看未合并到当前所在分支的分支

```bash
git branch --no-merged
```

### 11.11删除远程分支

```bash
git push [远程仓库S] :[远程分支R]
```

这个命令的格式意义比较无理头，为了方便记忆，可以这样理解：它是省略了本地分支名的推送命令 `git push [远程仓库S] [本地分支L]:[远程分支R]`，省略 `本地分支L` 表示：在这里提取空白然后把它变成 `远程分支R`。



## 12.恢复之前的版本

```bash
# 查看之前版本号
git log
# 版本回退
git reset --hard 目标版本号
# 提交更改
git push -f
```



## 13.相关文章

- https://github.com/windard/learngit/blob/master/git.txt
- https://www.jianshu.com/p/15a4dee9c5df
- https://blog.csdn.net/yxlshk/article/details/79944535

