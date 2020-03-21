#### 题目描述

Emiya 是个擅长做菜的高中生，他共掌握 $n$种烹饪方法，且会使用 $m$ 种主要食材做菜。为了方便叙述，我们对烹饪方法从$1 \sim n$ 编号，对主要食材从 $1 \sim m$ 编号。

Emiya 做的每道菜都将使用恰好一种烹饪方法与恰好一种主要食材。更具体地，Emiya 会做 $a_{i, j}$ 道不同的使用烹饪方法 $i$和主要食材$j$ 的菜 ，这也意味着 Emiya 总共会做 $\sum_{i=1}^n\sum_{i=1}^ma_{i, j}$ 道不同的菜。

Emiya 今天要准备一桌饭招待 Yazid 和 Rin 这对好朋友，然而三个人对菜的搭配有不同的要求，更具体地，对于一种包含$k$ 道菜的搭配方案而言:

- Emiya 不会让大家饿肚子，所以将做至少一道菜，即 $k \ge 1$
- Rin 希望品尝不同烹饪方法做出的菜，因此她要求每道菜的烹饪方法互不相同
- Yazid 不希望品尝太多同一食材做出的菜，他要求每种主要食材至多在一半的菜（即$\lfloor \frac k 2 \rfloor$道菜）中被使用。

这些要求难不倒 Emiya，但他想知道共有多少种不同的符合要求的搭配方案。两种方案不同，当且仅当存在至少一道菜在一种方案中出现，而不在另一种方案中出现。

Emiya 找到了你，请你帮他计算，你只需要告诉他符合所有要求的搭配方案数对质数 998244353 取模的结果。

#### 输入格式

第 $1$ 行两个用单个空格隔开的整数 $n, m$。

第 $2$行至第 $n+1$ 行，每行 $m$ 个用单个空格隔开的整数，其中第 $i+1$ 行的 $m$ 个数依次为 $a_{i,1},a_{i,2},…a_{i,m}$	

#### 输出格式

输出一行一个整数，表示所求方案数对 998244353 取模的结果。

#### 样例

**样例输入1**

```
2 3
1 0 1
0 1 1
```

**样例输出1**

```
3
```

**样例输入2**

```
3 3
1 2 3
4 5 0
6 0 0
```

**样例输出2**

```
190
```

**样例输入3**

```
5 5
1 0 0 1 1
0 1 0 1 0
1 1 1 1 0
1 0 1 0 1
0 1 1 0 1
```

**样例输出3**

```
742
```

#### 数据范围

对于所有测试点，保证$1 \le n \le 100, 1 \le m \le 2000, 0 \le a_{i, j} \le 998244353$





考虑所有情形：令$all[i][j]$表示在前i种烹饪方法中做了j道菜的方案数，则$all[i][j] = all[i-1][j]+all[i-1][j-1] * \sum\nolimits_{k=1}^ma[i][k]$，两项分别对应在第i种烹饪方法中是否选菜。

考虑非法情形：因为非法情形出现的条件是一种食材在超过一半的菜中使用，因此只会有一种食材非法。

因此遍历所有食材，设当前遍历到的为食材t，记$illegal[i][j][k]$为前i种烹饪方法中做了j道菜，且k道菜使用食材t的方案数，则

$illegal[i][j][k] = illegal[i-1][j][k] + illegal[i-1][j-1][k-1] * a[i][t] + illegal[i-1][j-1][k] * (sum[i]-a[i][t])$

并在答案中减去$illegal[n][j][k]_{k>\lfloor \frac j2 \rfloor}$

进一步优化：维护j和k两个维度是没有必要的，维护差值$k-(j-k)$即可，代表选中t食材的方案数减去不选中t食材的方案数，该值大于0属于非法。

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 998244353
inline ll read()
{
    ll x = 0, k = 1;
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
int a[105][2005];
int sum[105];
ll all[105][105];
ll ilall[105][210];
int main()
{
    ll ans = 0;
    const int BIA = 100;
    int n = read(), m = read();
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= m;j++){
            a[i][j] = read();
            sum[i] = (sum[i] + a[i][j]) % MOD;
        }
    }
    all[0][0] = 1;
    for (int i = 1; i <= n;i++){
        for (int j = 0; j <= i;j++){
            all[i][j] = all[i - 1][j];
            for (int k = 1; k <= m;k++){
                all[i][j] = (all[i][j] + all[i - 1][j - 1] * a[i][k]) % MOD;
            }
        }
    }
    for (int i = 1; i <= n;i++)
        ans = (ans + all[n][i]) % MOD;

    for (int t = 1; t <= m; t++) {
        memset(ilall, 0, sizeof(ilall));
        ilall[0][0 + BIA] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = -i + BIA; j <= i + BIA; j++) {
                ilall[i][j] = ((ll)ilall[i - 1][j] + ilall[i - 1][j - 1] * a[i][t] + ilall[i - 1][j + 1] * (sum[i] - a[i][t])) % MOD;
            }
        }
        for (int i = 1; i <= n;i++){
            ans = (ans - ilall[n][i + BIA]) % MOD;
            ans = (ans + MOD) % MOD;
        }
    }
    cout << ans;
    return 0;
}
```

参考资料：https://blog.csdn.net/weixin_37517391/article/details/103110646