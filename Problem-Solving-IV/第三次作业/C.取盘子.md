#### 题目描述

小明有$N$叠盘子。每叠都有$K$个盘子。每个盘子都有一个正数价值$v_{ij}$。小明想从中取$P$个盘子用于今晚的晚餐。如果他想取一个盘子，他必须取这个盘子上面的所有盘子，问怎么选盘子才能使盘子的价值之和最大。

#### 输入格式

第一行为三个整数$N, K, P$，接下来$N$行，每行有$K$个数，按顺序代表从顶部到底部每个盘子的价值。

#### 输出格式

输出一个数，为选择的盘子的最大价值和。

#### 样例

**样例输入1**

```
2 4 5
10 10 100 30
80 50 10 50
```

**样例输出1**

```
250
```

**样例输入2**

```
3 2 3
80 80
15 50
20 10
```

**样例输出2**

```
180
```

#### 数据范围与提示

对100%的数据，$1 \le K \le 30, 1 \le N \le 50, 1 \le P \le N \times K, 1 \le V_{ij} \le 100$



令$dp[j]$表示到目前为止，取$j$个盘子的最高价值。注意考虑第一叠时应该假设所有的$dp[i]$都是0，因此遍历P的时候应该从大到小。

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
int dp[1505];
int sum[55][55];
int main(void)
{
    int N = read(), K = read(), P = read();
    int ans = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= K; j++)
            sum[i][j] = sum[i][j - 1] + read();
    for (int i = 1; i <= N; i++) 
        for (int j = P; j; j--)  //倒着遍历是为了防止在同一叠里重复计算
            for (int k = 0; k <= min(j, K); k++)
                dp[j] = max(dp[j], dp[j - k] + sum[i][k]);
    for (int i = 1; i <= P; i++)
        ans = max(ans, dp[i]);
    cout << ans;
}
```

