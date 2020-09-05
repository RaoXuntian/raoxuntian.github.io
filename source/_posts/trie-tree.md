---
title: Trie Tree
date: 2020-06-18 19:34:52
tags:
- 数据结构
- trie tree
---

### 一.什么是Trie树

**Trie树**，又叫**字典树**、**前缀树（Prefix Tree）**、**单词查找树** 或 **键树**，是一种多叉树结构。如下图：

{% asset_img 1.png  TrieTree %}

<!--more-->

上图是一棵Trie树，表示了关键字集合{“a”, “to”, “tea”, “ted”, “ten”, “i”, “in”, “inn”} 。从上图可以归纳出Trie树的基本性质：

根节点不包含字符，除根节点外的每一个子节点都包含一个字符。
从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
每个节点的所有子节点包含的字符互不相同。
通常在实现的时候，会在节点结构中设置一个标志，用来标记该结点处是否构成一个单词（关键字）。

可以看出，Trie树的关键字一般都是字符串，而且Trie树把每个关键字保存在一条路径上，而不是一个结点中。另外，两个有公共前缀的关键字，在Trie树中前缀部分的路径相同，所以Trie树又叫做前缀树（Prefix Tree）。


### 二.Trie树的优缺点

Trie树的核心思想是空间换时间，利用字符串的公共前缀来减少无谓的字符串比较以达到提高查询效率的目的。

#### 优点

1. 插入和查询的效率很高，都为O(m)，其中 m 是待插入/查询的字符串的长度。

   关于查询，会有人说 hash 表时间复杂度是O(1)不是更快？但是，哈希搜索的效率通常取决于 hash 函数的好坏，若一个坏的 hash 函数导致很多的冲突，效率并不一定比Trie树高。
   Trie树中不同的关键字不会产生冲突。

2. Trie树只有在允许一个关键字关联多个值的情况下才有类似hash碰撞发生。

3. Trie树不用求 hash 值，对短字符串有更快的速度。通常，求hash值也是需要遍历字符串的。

4. Trie树可以对关键字按**字典序**排序。


#### 缺点

1. 当 hash 函数很好时，Trie树的查找效率会低于哈希搜索。
2. 空间消耗比较大。

### 三.Trie树的实现

https://leetcode-cn.com/problems/implement-trie-prefix-tree/

```c++
class Trie {
    Trie *child[26];
    bool isWord;
public:
    /** Initialize your data structure here. */
    Trie() {
        isWord=false;
        for (int i=0; i<26; ++i)
            child[i]=nullptr;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie *t=this;
        for (char c:word) {
            if (!t->child[c-'a']) {
                t->child[c-'a']=new Trie();
            }
            t=t->child[c-'a'];
        }
        t->isWord=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie *t=this;
        for (char c:word) {
            if (!t->child[c-'a']) {
                return false;
            }
            t=t->child[c-'a'];
        }
        return t->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie *t=this;
        for (char c:prefix) {
            if (!t->child[c-'a']) {
                return false;
            }
            t=t->child[c-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

### 四.Trie树的应用

https://leetcode-cn.com/problems/longest-common-prefix/

这是一道easy级别的题目，编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 `""`。

示例 1:

`输入: ["flower","flow","flight"]`
`输出: "fl"`

示例 2:

`输入: ["dog","racecar","car"]`
`输出: ""`
解释: 输入不存在公共前缀。
说明:

所有输入只包含小写字母 a-z 。

常规方法，也就是暴力法，假设最短字符串长度为m，字符串数组长度为n，那么时间复杂度就是O(m*n)：

```c++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n=strs.size();
        if (n==1) return strs[0];
        if (n==0) return "";
        string res;
        for (int i=0; ; ++i) {
            for (auto str: strs) {
                if (i>=str.size() || str[i]!=strs[0][i]) {
                    return str.substr(0,i);
                }
            }
        }
        return "";
    }
};
```

如果我们引用Trie树这一数据结构来解决这道题目：

```c++
class Trie {
    Trie *child[26];
    bool isWord;
    public:
    /** Initialize your data structure here. */
    Trie() {
        isWord=false;
        for (int i=0; i<26; ++i)
            child[i]=nullptr;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie *t=this;
        for (char c:word) {
            if (!t->child[c-'a']) {
                t->child[c-'a']=new Trie();
            }
            t=t->child[c-'a'];
        }
        t->isWord=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie *t=this;
        for (char c:word) {
            if (!t->child[c-'a']) {
                return false;
            }
            t=t->child[c-'a'];
        }
        return t->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie *t=this;
        for (char c:prefix) {
            if (!t->child[c-'a']) {
                return false;
            }
            t=t->child[c-'a'];
        }
        return true;
    }

    /*  判断当前这个节点是否是整个树的前缀，也就是孩子只有一个字母 */
    char isPrefixNode() {
        Trie *t=this;
        int cnt=0;
        char c='\0';
        for (int i=0; i<26; ++i) {
            if (t->child[i] != nullptr) {
                c=(char) ('a'+i);
                ++cnt;
            }
            if (cnt>1) break;
        }
        return cnt==1?c:'\0';
    }

    string searchMaxPrefix() {
        string res="";
        Trie *t=this;
        char c = t->isPrefixNode();
        while (!t->isWord && c!='\0') {
            res+=c;
            t=t->child[c-'a'];
            c=t->isPrefixNode();
        }
        return res;
    }
};
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        Trie *root = new Trie();
        for (auto str:strs) {
            if (str=="") return "";
            root->insert(str);
        }
        return root->searchMaxPrefix();
    }
};
```

算上构建Trie树的时间，可能还不如暴力法快，但在实际情况中，面向更海量的数据，如果将不用vector<string>来存储这些字符串，而是用一棵Trie树来存储这些字符串，那么无论是空间复杂度还是寻找最长前缀的时间复杂度，都将更优。

Trie树还有的一些应用：

#### 1、字符串检索

检索/查询功能是Trie树最原始的功能。思路就是从根节点开始一个一个字符进行比较：

- 如果沿路比较，发现不同的字符，则表示该字符串在集合中不存在。
- 如果所有的字符全部比较完并且全部相同，还需判断最后一个节点的标志位（标记该节点是否代表一个关键字）。

```c++
struct trie_node
{
    bool isKey;   // 标记该节点是否代表一个关键字
    trie_node *children[26]; // 各个子节点 
};
```

#### 2、词频统计

Trie树常被搜索引擎系统用于文本词频统计 。

```c++
struct trie_node
{
    int count;   // 记录该节点代表的单词的个数
    trie_node *children[26]; // 各个子节点 
};
```


思路：为了实现词频统计，我们修改了节点结构，用一个整型变量count来计数。对每一个关键字执行插入操作，若已存在，计数加1，若不存在，插入后count置1。

注意：第一、第二种应用也都可以用 hash table 来做。

#### 3、字符串排序

Trie树可以对大量字符串按字典序进行排序，思路也很简单：遍历一次所有关键字，将它们全部插入trie树，树的每个结点的所有儿子很显然地按照字母表排序，然后先序遍历输出Trie树中所有关键字即可。

#### 4、前缀匹配

例如：找出一个字符串集合中所有以ab开头的字符串。我们只需要用所有字符串构造一个trie树，然后输出以a->b->开头的路径上的关键字即可。

trie树前缀匹配常用于搜索提示。如当输入一个网址，可以自动搜索出可能的选择。当没有完全匹配的搜索结果，可以返回前缀最相似的可能。

#### 5、作为其他数据结构和算法的辅助结构

如后缀树，AC自动机等。

### 五.相关文章

- https://blog.csdn.net/lisonglisonglisong/article/details/45584721

