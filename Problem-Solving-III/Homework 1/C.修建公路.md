#### 题目描述

有$n$个城市，编号$1,2,...,n$。初始时，两两城市间都没有公路。现在要按顺序修建$m$条“单向”的公路，每条公路用二元组$(u,v)$表示，即一条从$u$城市到达$v$城市的单向公路。

现在对于每个$i=1,2,...,m$，求出修建完前ii*i*条公路后，有多少个有序对$(u,v)$，满足可以从城市$u$到达城市$v$。

#### 输入格式

第一行2个正整数$n,m$，表示城市的个数以及修建公路的条数。

接下来$m$行，每行2个正整数$u,v$，表示第$i$条公路从城市$u$到达城市$v$，保证$1\leq u,v\leq n,u \neq v$。

#### 输出格式

一行$m$个正整数，第$i$个正整数表示修建完前ii*i*条公路后，满足可以从城市$u$到达城市$v$的有序对$(u,v)$个数。

#### 样例

##### 样例输入 1

```plain
3 3
1 2
2 3
3 1
```

##### 样例输出 1

```plain
1 3 6
```

#### 数据范围与提示

对于前50%的数据，$1\leq n\leq 100$。

对于100%的数据，$1\leq n\leq 400, 1\leq m \leq n\cdot (n-1)$。

保证任意一条有向边至多只会出现 $1$次。



本题可以转化为最短路问题。第$i$条边赋权重为$i$，并把路的长度定义为：组成该路的所有边中最大的权值。我们在这样的前提下用Floyd算法计算多源最短路径，若$(u,v)$的最短路长度为$i$，说明第$i$条加入的边使得点u与点v联通。

```
#include<iostream>
using namespace std;
#define INF 1e9
inline int read()
{
	int x = 0, k = 1;
	char c = getchar();
	while (c <'0' || c>'9') { if (c == '-')k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + c - '0'; c = getchar(); }
	return x * k;
}
int n, m;
int cnt[160005];
int dp[405][405];
int main()
{
	for (int i = 0; i < 405; i++) for (int j = 0; j < 405; j++) dp[i][j] = INF;
	n = read(), m = read();
	for (int i = 1,t1,t2; i <= m; i++) {
		t1 = read(); t2 = read();
		dp[t1][t2] = i;
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j) continue;
				dp[i][j] = min(dp[i][j], max(dp[i][k], dp[k][j]));
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if(dp[i][j] != INF)
				++cnt[dp[i][j]];
		}
	}
	for (int i = 1, ans = 0; i <= m; i++) {
		ans += cnt[i];
		printf("%d ", ans);
	}	
	system("pause");
	return 0;
}
```

