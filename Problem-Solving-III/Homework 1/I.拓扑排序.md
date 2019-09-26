#### 题目描述

给定$n$个点，$m$条边的有向无环图，输出其字典序最小的拓扑序。

#### 输入格式

第一行为两个数$n, m$，表示有$n$个点，$m$条有向边。

接下来$m$行，每行两个数$x, y$，表示有一条$x$连向$y$的有向边。

#### 输出格式

输出一行用空格分隔的$n$个数，应当为$1, 2, \cdots, n$的一个排列。

表示该有向无环图字典序最小的拓扑序。

#### 样例

##### Input

```
3 3
2 1
2 3
1 3
```

##### Output

```
2 1 3
```

#### 数据范围与提示

对于60%的数据，$1 \leq n \leq 2000$。

对于所有数据，$1≤n≤10^5$，$1 \leq m \leq \min(\frac{n(n - 1)}{2}, 3 * 10^5)$。

保证该图无重边和自环。



拓扑排序的做法：建图时存下每个点的入度，把入度为0的点加入队列。每次循环取出一个点，去掉它的所有边（等价于对其所有邻点入度-1），如果新产生了一个入度为0的点，则把它加入队列。最后所有结点都应进队一次，否则说明无法拓扑排序。

此题还要求输出一个字典序最小的拓扑序，我们只要把队列改为优先队列即可。

```
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define maxm 300005
#define maxn 100005
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
	int u, v, next;
} e[maxm];
int n,m,cnt, first[maxn];
int in_deg[maxn];
void add(int u, int v)
{
	e[++cnt].u = u;
	e[cnt].v = v;
	e[cnt].next = first[u];
	first[u] = cnt;
	++in_deg[v];
}
priority_queue<int, vector<int>, greater<int>> q;
vector<int> ans;
int main()
{
	n = read(), m = read();	
	for (int i = 1, t1, t2; i <= m; i++) {
		t1 = read(); t2 = read();
		add(t1, t2);
	}
	for (int i = 1; i <= n; i++) {
		if (in_deg[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		auto u = q.top(); q.pop();
		ans.push_back(u);
		for (int k = first[u]; k; k = e[k].next) {
			auto v = e[k].v;
			--in_deg[v];
			if (in_deg[v] == 0) q.push(v);
		}
	}
	for (auto e : ans) {
		printf("%d ", e);
	}
	system("pause");
	return 0;
}
```

