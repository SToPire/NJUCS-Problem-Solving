#### 题目描述

对于$(1, 2, ..., n)$的任意一个排列: $A = (a_1, a_2, ..., a_n)$，定义一个新的序列$ P(A)=(p_1,p_2,…,p_{n−1})$

其中: $p_i$的值按如下方式确定：若 $a_i> a_{i+1}$, 则 $p_i =0$，若 $a_i<a_{i+1}$, 则 $p_i =1$。

编写一个程序，对于上述任意的排列 $A$, 确定有$(1, 2, ..., n)$的多少个不同排列，与 $A$ 具有相同的 $P$ 序列。

#### 输入格式

第一行输入一个数$n$，代表排列的长度

接下来一行输入空格分割的$n$个数$a_1, a_2, \cdots, a_n$

#### 输出格式

输出一行一个整数，代表具有这种大小关系的排列个数

#### 样例

**样例输入1**

```
4
1 3 2 4
```

**样例输出1**

```
5
```

#### 数据范围与提示

**样例解释**

满足条件的排列有如下5个

```
1 3 2 4
1 4 2 3
2 3 1 4
2 4 1 3
3 4 1 2
```

**数据范围**

对60%的数据 $2 \le n \le 10$

对100%的数据 $2 \le n \le 20, 1 \le a_i \le n$



$dp[chosen][last]$表示已经使用过chosen表示的数字，且以last数字结尾的方案数。用一个队列规划dp的顺序，按照`index`从小到大的顺序执行，注意`index==n`与`chosen == (1<<n)-1`等价。对每个node考察其已经确定的最后一位和下一位应是何种大小关系，尝试所有可取的数字，加入队列。



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
struct node {
    int index;
    int chosen;
    int last;
};
int a[21];
long long dp[(1 << 21) - 1][21];
bool inQueue[(1 << 21) - 1][21];

int main()
{
    long long ans = 0;
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    queue<node> q;
    q.push((node) { 0, 0, 0 });
    while (!q.empty()) {
        node x = q.front();
        q.pop();
        if (x.index == n) {
            assert(x.chosen == (1 << n) - 1);
            ans += dp[x.chosen][x.last];
            continue;
        }
        if (x.index == 0) {
            for (int i = 1; i <= n; i++) {
                q.push((node) { 1, 1 << (i - 1), i });
                dp[1 << (i - 1)][i] = 1;
                inQueue[1 << (i - 1)][i] = 1;
            }
        } else {
            if (a[x.index] < a[x.index + 1]) {
                for (int i = x.last + 1; i <= n; i++) {
                    if (((1 << (i - 1)) & x.chosen) != 0)
                        continue;
                    if(!inQueue[x.chosen|(1<<(i-1))][i])
                        q.push((node) { x.index + 1, x.chosen | (1 << (i - 1)), i });
                    dp[x.chosen | (1 << (i - 1))][i] += dp[x.chosen][x.last];
                    inQueue[x.chosen | (1 << (i - 1))][i] = 1;
                }
            } else {
                for (int i = 1;i<=x.last-1;i++) {
                    if (((1 << (i - 1)) & x.chosen) != 0)
                        continue;
                    if (!inQueue[x.chosen | (1 << (i - 1))][i])
                        q.push((node) { x.index + 1, x.chosen | (1 << (i - 1)), i });
                    dp[x.chosen | (1 << (i - 1))][i] += dp[x.chosen][x.last];
                    inQueue[x.chosen | (1 << (i - 1))][i] = 1;
                }
            }
        }
    }
    cout << ans;
    return 0;
}
```

