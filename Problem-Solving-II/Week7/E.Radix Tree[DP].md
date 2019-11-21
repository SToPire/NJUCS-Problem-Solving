#### 题目描述

给定 $n$ 个数 $a_1, a_2, \cdots, a_n$, 询问有多少个有序对 $(i, j)$, 使得 $a_i \otimes a_j = 0$, 其中 $\otimes$ 是位运算与操作.

#### 输入格式

读入 $n$, 接下来再读入$n$个数表示$a_i$

#### 输出格式

输出一个数表示答案.

#### 样例输入

```plain
5
0 1 2 3 4
```

#### 样例输出

```plain
17
```

#### 数据范围与提示

$1 \le n \le 200000$

$0 \le a_i < 2^{20}$



令$dp[i][j]$表示对于给定的$i$，仅在第$0$位到第$j$位允许与i不同的子集个数。

（子集：一个数的子集定义为，他的二进制表示中的置位可为1或0，非置位只能为0的数。）

例如$dp[1011010][3] $包括${1011010,1010010,1011000,1001000}$

于是有递推关系
$$
dp[i][j]= \begin{cases}  dp[i][j-1] &\text{第j位非置位} \\ dp[i][j-1]+dp[i \oplus2^j][j-1] & \text{第j位置位}\end{cases}
$$

注意这里$i \oplus2^j$一定比$i$小，保证了从小到大枚举$i$的顺序是正确的。

```c++
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int a[200005];
int dp[(1ll<<20)+5][25];
int times[(1ll << 20) + 5];
int main(void)
{
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		times[a[i]]++;
	}
	long long ans = 0;
	long long upperbound = 1ll << 20;
	for (int mask = 0; mask < upperbound; mask++) {
		dp[mask][0] = times[mask];
		if (mask & 1) dp[mask][0] += times[mask ^ 1];
		for (int j = 1; j <= 20; j++) {
			dp[mask][j] = dp[mask][j - 1];
			if (mask & (1ll << j)) dp[mask][j] += dp[mask ^ (1ll << j)][j - 1];
		}
	}
	for (int i = 1; i <= n; i++)
		ans += dp[upperbound - 1 - a[i]][19];
	cout << ans;
	system("pause");
}
```

第27行的upperbound-1-a[i]的意义是对a[i]按位取反。因为$a_i \& a_j$为0的条件是$a_i$为$1$的位上，$a_j$只能为0，这一条件等价于$a_j$是$a_i取反$的子集。

参考：

http://codeforces.com/blog/entry/45223?tdsourcetag=s_pcqq_aiomsg

https://www.hackerearth.com/zh/practice/algorithms/dynamic-programming/bit-masking/practice-problems/algorithm/special-pairs-7/editorial/