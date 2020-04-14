#### 题目描述

学习英语的人迟早会明白，英语语法中逗号的添加规则相当复杂、麻烦、且存在歧义。包括母语为英语的人在内的大多数人实际上会忽视这些规则并自己想出一套规则，甚至没有任何规则。

逗号播撒机老师制定了一套无歧义、不简单的规则，从而解决了这个问题。在本题中，你将会帮助播撒机老师编写算法来自动按照他的规则添加逗号。

播撒机老师对已有的文字添加逗号的规则如下：

1. 如果在文本的任何位置有一个词语的前面有一个逗号，就在文本中找到该词语出现的所有位置，并在该词语前面添加一个逗号，除非该词语是该句子的第一个词语，或者词语前面已经有一个逗号。
2. 如果在文本的任何位置有一个词语的后面有一个逗号，就在文本中找到该词语出现的所有位置，并在该词语后面添加一个逗号，除非该词语是该句子的最后一个词语，或者词语后面已经有一个逗号。
3. 重复 1 和 2 直到无法再添加新的逗号。

举例来说，考虑这样一段文字

```
please sit spot. sit spot, sit. spot here now here.
```

因为第二句在 spot 的后面有一个逗号，所以在第三句的 spot 后面也应该添加一个逗号（但第一个句子不用，因为第一句中 spot 是最后一个词语）。同时，由于在第二句中第二个 sit 前面有一个逗号，所以在第一句的 sit 前面也要添加一个逗号（第二个句子的第一个 sit 是第二句的第一个词语，所以不用添加逗号）。最后，发现第三句的 here 前面多出了一个逗号，因此在 here 所有出现位置的前面也添加一个逗号。无法再添加更多的逗号，所以最终的结果是

```
please, sit spot. sit spot, sit. spot, here now, here.
```

#### 输入格式

输入只有一行文本。

每个字符可能是以下四项之一：小写字母、逗号、句号或空格。定义单词为文本中的极长连续字母串。该文本满足以下约束条件：

- 文本开头一定是一个单词。
- 每两个单词之间要么有一个空格，一个逗号紧接着一个空格，或者一个句号紧接着一个空格（表示一个句子的结束和另一个句子的开始）。
- 文本结尾一定是一个句号，且没有多余空格。

#### 输出格式

输出文本经过播撒机老师算法处理后得到的结果。

#### 样例

**样例输入1**

```
please sit spot. sit spot, sit. spot here now here.
```

**样例输出1**

```
please, sit spot. sit spot, sit. spot, here now, here.
```

**样例输入2**

```
one, two. one tree. four tree. four four. five four. six five.
```

**样例输出2**

```
one, two. one, tree. four, tree. four, four. five, four. six five.
```

#### 数据范围与提示

共有60组数据，所有数据输入字符数在[2,1000000]范围内，其中22组数据输入字符数小于1000。





把句子按空格拆成单词，单词分以句号结尾，逗号结尾和无标点3种。对于每个单词维护整个句子里出现在它前一个位置和后一个位置的单词。注意对于a, b或a. b而言，a不是b的前驱，b也不是a的后继。做一次搜索即可，注意对于每个单词在其之前或之后加逗号只考虑一次。

```c++
#include <bits/stdc++.h>
using namespace std;
string s, word[1000010];
int cnt;
map<string, vector<string>> pre, nxt;
map<string, bool> vispre, visnxt;

void searchPre(string& s);
void searchNxt(string& s);

void div(string& s)
{
    int t = s.size();
    cnt = 1;
    for (int i = 0; i < t; i++)
        if (s[i] == ' ')
            word[cnt++] += ' ';
        else
            word[cnt] += s[i];
}
string pureWord(string& s)
{
    string t;
    for (auto e : s)
        if (e >= 'a' && e <= 'z')
            t += e;
    return t;
}
bool puncEnd(string& s)
{
    if (s[s.size() - 1] == '.' || s[s.size() - 1] == ',' || s[s.size() - 2] == '.' || s[s.size() - 2] == ',')
        return true;
    return false;
}
bool commaEnd(string& s)
{
    if (s[s.size() - 1] == ',' || s[s.size() - 2] == ',')
        return true;
    return false;
}
void searchNxt(string& s)
{
    visnxt[s] = true; //在s之后加逗号
    int t = nxt[s].size();
    for (int i = 0; i < t; i++) {
        if (!vispre[nxt[s][i]])
            searchPre(nxt[s][i]); //对于紧邻s之后的单词，在其之前加逗号
    }
}
void searchPre(string& s)
{
    vispre[s] = true;
    int t = pre[s].size();
    for (int i = 0; i < t; i++)
        if (!visnxt[pre[s][i]])
            searchNxt(pre[s][i]);
}
string addComma(string s)
{
    s[s.size() - 1] = ',';
    s += ' ';
    return s;
}
int main()
{
    getline(cin, s);
    div(s);

    for (int i = 2; i <= cnt; i++)
        if (!puncEnd(word[i - 1]))
            pre[pureWord(word[i])].push_back(pureWord(word[i - 1]));
    for (int i = 1; i < cnt; i++)
        if (!puncEnd(word[i]))
            nxt[pureWord(word[i])].push_back(pureWord(word[i + 1]));
    for (int i = 1; i < cnt; i++) {
        string t = pureWord(word[i]);
        if (commaEnd(word[i]) && !visnxt[t])
            searchNxt(t);
    }
    for (int i = 2; i <= cnt; i++) {
        string t = pureWord(word[i]);
        if (commaEnd(word[i - 1]) && !vispre[t])
            searchPre(t);
    }
    for (int i = 1; i <= cnt; i++) {
        if (visnxt[pureWord(word[i])] && !puncEnd(word[i]))
            cout << addComma(word[i]);
        else
            cout << word[i];
    }
    return 0;
}
```

