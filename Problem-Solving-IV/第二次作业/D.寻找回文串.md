#### 题目描述

给定一个数列$a_1,a_2,…,a_n$，请你判断这个数列是否存在长度为3的子序列$a_{i_1}, a_{i_2}, a_{i_3}$，使得其为回文串（即$a_{i_1} = a_{i_3}$）。

#### 输入格式

第一行输入一个数$T$，代表样例组数

每组样例的第一行输入一个数$n$，代表数列长度，接下来一行输入$n$个数$a_1,a_2,…,a_n$

#### 输出格式

每组样例输出一行`YES`或`NO`，代表是否存在这样的回文子序列

#### 样例

**样例输入1**

```
5
3
1 2 1
5
1 2 2 3 2
3
1 1 2
4
1 2 2 1
10
1 1 2 2 3 3 4 4 5 5
```

**样例输出1**

```
YES
YES
NO
YES
NO
```

#### 数据范围与提示

对20%的数据，$3 \le n \le 5000$

 对100%的数据，$3 \le n \le 5 \times 10^4, 1 \le T \le 10, 1 \le a_i \le 10^9$



对于每个$a_i$可能的值，维护这个值第一次出现的位置。若当前位置为$i$，如果发现该值已经出现在$i-2$位置之前则说明回文串存在。

鉴于$a_i$范围太大开不下数组，可以使用哈希表`map`

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, k = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            k = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    return x * k;
}
int a[50005];
map<int, int> m;
void once()
{
    memset(a, 0, sizeof(a));
    m.clear();
    int n = read();
    bool YES = false;
    for (int i = 1; i <= n;i++){
        a[i] = read();
        if(m[a[i]]==0)
            m[a[i]] = i;
        else if(m[a[i]] >= 1 && m[a[i]] <=i-2)
            YES = true;
    }
    if(YES)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
int main()
{
    int T = read();
    while(T--)
        once();
    return 0;
}
```

