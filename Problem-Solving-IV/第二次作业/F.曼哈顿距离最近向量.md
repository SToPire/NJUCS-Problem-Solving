#### 题目描述

给定一个$n$维向量$v=(a_1,a_2,…,a_n)^T$，给定$m (m \ge n)$个数$b_1,b_2,…,b_m$，要求从这$m$个数中选择$n$个数组成一个新向量$w=(b_{k_1},b_{k_2},…,b_{k_n})^T$，每个数只能用一次，即$k_i$两两不同。注意$k_i$的顺序没有限制，即可以任意排列这$n$个数。

定义$\mathbb{v}$和$\mathbb{w}$之间的曼哈顿距离为$|a1−b_{k_1}|+|a2−b_{k_2}|+⋯+|an−b_{k_n}|$，问$\mathbb{v}$和$\mathbb{w}$的曼哈顿距离最小值是多少？

#### 输入格式

第一行输入整数$m$和$n$，用空格隔开。

第三行输入$m$个整数$b_1,b_2,…,b_m$

第二行输入$n$个整数$a_1,a_2,…,a_n$

#### 输出格式

输出一个数，代表$\mathbb{v}$和$\mathbb{w}$的曼哈顿距离最小值。

#### 样例

**样例输入1**

```
5 3
28 -42 -23 -25 9
-6 -30 -44
```

**样例输出1**

```
22
```

#### 数据范围与提示

30%的数据满足 $m \le 16, n \le 10$

60%的数据满足 $m \le 1000, n \le 500$

100%的数据满足 $m \le 20000, n \le 10000, m \ge n, -10^9 \le a_i, b_i \le 10^9$





首先把两个数组的元素合在一起排序。每个$a_i$处于“匹配”或“暂未匹配”的状态，每个$b_i$处于“匹配”，“暂未匹配”或“被抛弃”的状态，如果对于一个没有与某个$a_i$匹配的$b_i$，当前考虑的状态里比它大的最小的那个$a_i$已经匹配了，说明在当前考虑的状态里这个$b_i$被抛弃了。排序的必要性是：从左到右扫过，如果尚有未匹配的$a_i$，一个新的$b_i$必定和最小的那个未匹配$a_i$发生匹配。

$dp[i][j]$表示考虑前$i$个数，且“暂未匹配”$a_i$的个数-“暂未匹配”$b_i$的个数==$j$。不难看出，$-n\le j\le n$，下界是$-n$是因为一旦已经有了$n$个$b_i$处于“暂未匹配”状态，当新的$b_i$到来时，最小的那个$b_i$会被抛弃。

约定在新扫过的元素“加重“了当前匹配的不平衡性时做减法。比如现在$j>0$，即暂未匹配的$a_i$多于暂未匹配的$b_i$，此时如果新扫过一个$a_i$元素，它加剧了不平衡性，状态转移时要在$dp[i-1][j-1]$基础上做减法，以此类推。注意当$j==0$时无论如何都会产生不平衡，都做减法。

如果新扫过的元素是$b_i$，我们可以选择不将它与某个比它小的$a_i$匹配，此时无事发生，体现在第52行。

最后输出$dp[n+m][0]$即为答案，使用滚动数组可将行数降至2.

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxm = 20000;
const int maxn = 10000;
const long long INF = 1e18;
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
struct node {
    int v;
    bool t;
} input[maxn + maxm + 5];
long long dp[2][2 * maxn + 5];
int main(void)
{
    int m = read(), n = read();
    for (int i = 1; i <= m; i++) {
        input[i].v = read();
        input[i].t = 0;
    }
    for (int i = 1; i <= n; i++) {
        input[i + m].v = read();
        input[i + m].t = 1;
    }
    sort(input + 1, input + 1 + n + m, [](node& l, node& r) { return l.v < r.v; });
    const int BIA = maxn;
    dp[0][BIA] = 0;
    int i = 1;
    for (; i <= n + m; i++) {
        for (int j = -n; j <= n; j++)
            dp[i & 1][j + BIA] = INF;
        int tmp = min(i - 1, n);
        for (int j = -tmp; j <= tmp; j++) {
            if (input[i].t == 1) { //数组a中元素
                if (j >= 0) //当前未配对的元素中，来自数组a的较多
                    dp[i & 1][j + 1 + BIA] = min(dp[i & 1][j + 1 + BIA], dp[1 - (i & 1)][j + BIA] - input[i].v);
                else //当前未配对的元素中，来自数组b的较多
                    dp[i & 1][j + 1 + BIA] = min(dp[i & 1][j + 1 + BIA], dp[1 - (i & 1)][j + BIA] + input[i].v);
            } else { //数组b中元素
                dp[i & 1][j + BIA] = min(dp[i & 1][j + BIA], dp[1 - (i & 1)][j + BIA]);
                if (j <= 0) //当前未配对的元素中，来自数组b的较多
                    dp[i & 1][j - 1 + BIA] = min(dp[i & 1][j - 1 + BIA], dp[1 - (i & 1)][j + BIA] - input[i].v);
                else //当前未配对的元素中，来自数组a的较多
                    dp[i & 1][j - 1 + BIA] = min(dp[i & 1][j - 1 + BIA], dp[1 - (i & 1)][j + BIA] + input[i].v);
            }
        }
    }
    cout << dp[(--i)&1][0 + BIA];
    return 0;
}
```

