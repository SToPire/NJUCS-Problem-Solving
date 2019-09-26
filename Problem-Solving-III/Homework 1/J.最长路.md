#### 题目描述

给定$n$个点，$m$条边的带边权有向无环图，请求出其中最长的一条路，并输出长度。

#### 输入格式

第一行为两个数$n, m$，表示有$n$个点，$m$条有向边。

接下来$m$行每行三个数$x, y, z$，表示点$x$有一条连向$y$的边权为$w$的有向边。

#### 输出格式

输出一个数，表示最长路长度。

#### 样例

##### Input

```
3 3
1 2 1
2 3 1
1 3 1
```

##### Output

```
2
```

#### 数据范围与提示

对于60%的数据，$1 \leq n \leq 2000$。

对于所有数据，$1≤n≤2∗10^5$，$1 \leq m \leq \min(\frac{n(n - 1)}{2}, 5 * 10^5)$，$1 \leq w \leq 10^4$。

保证该图无重边和自环。







dp:记$dist[i]$表示从$i$点出发所能得到的最长路长度，我们要求所有$dist[i],1 \le i \le n$的最大值。

类似最短路，该问题有最优子结构，状态转移为:
$$
dist[i]=\max(dist[i],dist[j]+w(i,j)),(i,j) \in G(E)
$$
我们可以自下而上的计算这个值。每个点被访问的时候，它会获取每个后代的dist值以更新自己的dist值，此时以该点开始的最长路长度已经计算好了，因此我们遇到$dist[i] > 0$时直接return.

我们还注意到一点，那就是最长路开始的结点一定是一个入度为0的点，这样我们就不用对每个结点都进行dp了。

```
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define maxm 500005
#define maxn 200005
#define INF 1e18
inline int read()
{
	int x = 0, k = 1;
	char c = getchar();
	while (c <'0' || c>'9') { if (c == '-')k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + c - '0'; c = getchar(); }
	return x * k;
}
struct Edge {
	int u, v, w, next;
} e[maxm];
int n,m,cnt, first[maxn];
int dist[maxn];
int in_deg[maxn];
void add(int u, int v, int w)
{
	e[++cnt].u = u;
	e[cnt].v = v;
	e[cnt].w = w;
	e[cnt].next = first[u];
	first[u] = cnt;
	++in_deg[v];
}

int dp(int n)
{
	if (dist[n] > 0) return dist[n];
	for (int k = first[n];k;k=e[k].next) {
		dist[n] = max(dist[n], dp(e[k].v) + e[k].w);
	}
	return dist[n];
}
int main()
{
	n = read(), m = read();	
	for (int i = 1, t1, t2, t3; i <= m; i++) {
		t1 = read(); t2 = read(); t3 = read();
		add(t1, t2, t3);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if(!in_deg[i]) ans = max(ans, dp(i));
	}
	cout << ans;
	system("pause");
	return 0;
}
```

