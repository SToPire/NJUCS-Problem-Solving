#### 题目描述

Acesrc每年有很多栅栏要修理。他总是骑着马穿过每一个栅栏并修复它破损的地方。

Acesrc是一个十分懒惰的人。他讨厌骑马，因此从来不两次经过一个栅栏。你必须编一个程序，读入栅栏网络的描述，并计算出一条修栅栏的路径，使每个栅栏都恰好被经过一次。Acesrc能从任何一个顶点(即两个栅栏的交点)开始骑马，在任意一个顶点结束。

每一个栅栏连接两个顶点，顶点用$1$到$500$标号(虽然有的农场并没有$500$个顶点)。一个顶点上可连接任意多$(>=1)$个栅栏。两顶点间可能有多个栅栏。所有栅栏都是连通的(也就是你可以从任意一个栅栏到达另外的所有栅栏)。

你的程序必须输出骑马的路径(用路上依次经过的顶点号码表示)。我们如果把输出的路径看成是一个$500$进制的数，那么当存在多组解的情况下，输出$500$进制表示法中最小的一个 (也就是输出第一位较小的，如果还有多组解，输出第二位较小的，等等)。

输入数据保证至少有一个解。

#### 输入格式

第$1$行: 一个整数$F$，表示栅栏的数目

第$2$到$F+1$行: 每行两个整数$i, j(1 <= i,j <= 500)$表示这条栅栏连接$i$与$j$号顶点。

#### 输出格式

输出应当有$F+1$行，每行一个整数，依次表示路径经过的顶点号。注意数据可能有多组解，但是只有上面题目要求的那一组解是认为正确的。

#### 样例

##### 样例输入

```plain
9
1 2
2 3
3 4
4 2
4 5
2 5
5 6
5 7
4 6
```

##### 样例输出

```plain
1
2
3
4
2
5
4
6
5
7
```

#### 数据范围与提示

对于$100\%$的数据，有$1\leq F\leq 1024$



为了满足字典序要求，我们从序号最小且度为奇数的点出发。如果所有点度数均为偶数，就为序号最小且度数不为0的点出发。按照序号从小到大的方式做dfs，并记录访问顺序，按照逆序打印。每访问一条边，就把这条边删去。



之所以不把打印放在dfs的过程中，是因为dfs实际上在贪心，不保证每次都走到正确的路上。

```
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
#define maxm 1030
#define maxn  505
#define INF 1e18
inline int read()
{
	int x = 0, k = 1;
	char c = getchar();
	while (c <'0' || c>'9') { if (c == '-')k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + c - '0'; c = getchar(); }
	return x * k;
}
int m, n;
int G[maxn][maxn],deg[maxn];
stack<int> S;
void dfs(int n)
{
	for (int i = 1; i < maxn; i++) {
		if (G[n][i]) {
			G[n][i]--; G[i][n]--;
			deg[n]--; deg[i]--;
			dfs(i);
		}
	}
	S.push(n);
}
void add(int u, int v)
{
	G[u][v]++; G[v][u]++;
	deg[u]++; deg[v]++;
}

int main()
{
	m = read();
	for (int i = 1, t1, t2; i <= m; i++) {
		t1 = read(); t2 = read();
		add(t1, t2);
	}
	int start;
	for (int i = 1; i < maxn; i++) 
		if (deg[i]) {
			start = i; break;
		}
	for (int i = 1; i < maxn; i++) 
		if (deg[i] % 2 == 1) {
			start = i; break;
		}
	dfs(start);
	while (!S.empty()) {
		cout << S.top() << endl;
		S.pop();
	}
	system("pause");
	return 0;
}
```

