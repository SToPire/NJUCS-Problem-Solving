

#### 题目描述

给一张 $n$ 个点，$m$ 条边的有向带权图，求 $1$ 号点到所有点的最短路长度。图中可能有负权边，但不存在负环。

#### 输入格式

第一行 $2$ 个正整数$n,m$，表示点,边的个数。

接下来 $m$ 行，每行3个整数$u,v,w$，表示有一条从$u$连向$v$，边权为$w$的有向边。保证$1\leq u,v\leq n,-10^9\leq w \leq 10^9$

#### 输出格式

一行 $n$ 个整数，第 $i$ 个整数表示 $1$ 号点到 $i$ 号点的最短距离。保证所有点都从1号点可达。（$1$ 号点到自身的距离认为是$0$ ）

#### 样例

##### 样例输入 1

```plain
4 4
1 2 2
1 3 1
1 4 0
2 4 -3
```

##### 样例输出 1

```plain
0 2 1 -1
```

#### 数据范围与提示



对于前50%的数据，保证$1\leq n\leq 100,1\leq m \leq 5000$。

对于100%的数据，保证$1\leq n\leq 2000,1\leq m \leq 5000$。



使用SPFA实现。与dij的区别是，不使用优先队列，而是一个普通的FIFO队列。另外每当寻访到一个新结点时，一旦松弛过程中更新了它的d值，我们就要把它加入队列（除非它已经在队列里了），而不管它之前有没有进过队列。


```
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define maxm 5005
#define maxn 2005
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
int n,m,cnt, now_in_queue[maxn], first[maxn];
//{节点编号，d值}
long long d[maxn];
queue<int> q;
void add(int u, int v, int w)
{
	e[++cnt].u = u;
	e[cnt].v = v;
	e[cnt].w = w;
	e[cnt].next = first[u];
	first[u] = cnt;
}
void SPFA() 
{
	for (int i = 1; i <= n; i++) d[i] = INF;
	d[1] = 0; q.push(1); now_in_queue[1] = true;
	while (!q.empty()) {
		auto tmp = q.front(); q.pop();
		now_in_queue[tmp] = false;
		for (int k = first[tmp]; k; k = e[k].next) {
			if (d[e[k].v] > d[tmp] + e[k].w) {
				d[e[k].v] =  d[tmp] + e[k].w;
				if (!now_in_queue[e[k].v]) {
					q.push(e[k].v);
					now_in_queue[e[k].v] = true;
				}
			}
		}
	}
}
int main()
{
	n = read(), m = read();	
	for (int i = 1, t1, t2, t3; i <= m; i++) {
		t1 = read(); t2 = read(); t3 = read();
		add(t1, t2, t3);
	}
	SPFA();
	for (int i = 1; i <= n; i++) {
		printf("%ld ", d[i]);
	}
	system("pause");
	return 0;
}
```

