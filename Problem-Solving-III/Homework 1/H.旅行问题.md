#### 题目描述

给定$n$个点，以及矩阵$A$.

对于$1 \leq i, j \leq n$，点$i$和$j$之间存在一条长度为$A_{i, j}$的边.

请你求出从任意一点出发，遍历完所有的点至少一次，在任意一点结束所经过的最小距离.

#### 输入格式

输入共$n + 1$行.

第111行为一个数$n$，表示点的个数.

对于第$2$到$n + 1$行，每行$n$个数.

第$i + 1$行第$j$个数表示$A_{i, j}$.

#### 输出格式

输出一个数，表示最小距离.

#### 样例

##### Input

```
3
0 1 2
1 0 3
2 3 0
```

##### Output

```
3
```

#### 数据范围与提示

对于$1 \leq i \leq n$，$A_{i, i} = 0$,$i=0$.

对于$1 \leq i, j \leq n$，$A_{i, j} = A_{j, i}$.

$2 \leq n \leq 20$，$0 \leq A_{i, j} \leq 5000$.





令$dp[i][{v_1,v_2 ...v_n}]$表示从$i$出发，途径$v_1,v_2,...,v_n$的最短路径，转移方程如下：
$$
dp[i][v_1,v_2...,v_n]=\min (dp[v_1][v_2,...,v_n]+G[i][v_1],dp[v_2][v_1,...,v_n]+G[i][v_2]),...,dp[v_n][v_1,...,v_{n-1}]+G[i][v_n]
$$
这样做存在一个问题：$dp[i][{v_1,v_2 ...v_n}]$对应的真正的某条最短路径不一定只经过点${v_1,v_2 ...v_n}$，可能需要先拐向某个其他点。为了解决这个问题，我们先对整个图进行一次Floyd，把两点间的边权替换成它们的最短路长度，这样就保证了转移方程的正确性，不可能需要拐向其他的某个点，来得到途径$v_1,v_2...v_n$的最短路。

使用了$n$位二进制数，来表示哪些点是必须要途经的。

```
#include <algorithm>
#include <iostream>
using namespace std;
#define maxn 21
#define maxm 1048577 //pow(2,20)+1
#define INF 1e18
typedef long long ll;
inline int read()
{
    int x = 0, k = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            k = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    return x * k;
}
int m, n;
int G[maxn][maxn];
ll dp[maxn][maxm];
ll solve(int a, int b)
{
    if (dp[a][b] != INF)
    {
        return dp[a][b];
    }
    ll ans = dp[a][b];
    for (int i = 1; i <= n; i++)
    {
        if (i == a)
            continue;
        if (b & 1 << (i - 1)) //b的第i位是1
            ans = min(ans, solve(i, b & ~(1 << (i - 1))) + G[i][a]);
    }
    dp[a][b] = ans;
    return ans;
}
int main()
{
    n = read();
    for (int i = 0; i < maxn; i++)
        for (int j = 0; j < maxm; j++)
        {
            dp[i][j] = INF;
        }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            G[i][j] = read();
        }
        dp[i][0] = 0;
        dp[i][1 << (i - 1)] = 0;
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    continue;
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][1 << (j - 1)] = dp[j][1 << (i - 1)] = G[i][j];
        }
    }
    cout << solve(0, (1 << n) - 1);
    system("pause");
    return 0;
}
```

