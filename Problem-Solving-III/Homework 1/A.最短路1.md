

#### 题目描述

给一张 $n$ 个点，$m$ 条边的有向带权图，求 $1$ 号点到所有点的最短路长度。

#### 输入格式

第一行 $2$ 个正整数$n,m$，表示点,边的个数。

接下来 $m$ 行，每行3个整数$u,v,w$，表示有一条从$u$连向$v$，边权为$w$的有向边。保证$1\leq u,v\leq n,1\leq w \leq 10^9$

#### 输出格式

一行 $n$ 个整数，第 $i$ 个整数表示 $1$ 号点到 $i$ 号点的最短距离。如果不存在一条路径，能够从$1$ 号点到达$i$ 号点，则第$i$个整数输出$-1$ 。（$1$ 号点到自身的距离认为是$0$ ）

#### 样例

##### 样例输入 1

```plain
4 4
4 1 100
1 2 3
1 3 1
3 2 1
```

##### 样例输出 1

```plain
0 2 1 -1
```

#### 数据范围与提示

对于前20%的数据，保证$1\leq n\leq 100,1\leq m \leq 2000$。

对于前50%的数据，保证$1\leq n\leq 1000,1\leq m \leq 2000$。

对于100%的数据，保证$1\leq n\leq 100000,1\leq m \leq 200000$。



Dijkstra样板题。维护一个优先队列，每次取出d值最小的点。每个点仅被访问一次，因为dij的特性保证了每个点第一次被取出并松弛后，就已经达到了最短路。


```
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
#define maxm 200005
#define maxn 100005
#define INF 1e18
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
struct Node{
    bool done;
    int first;
    long long d;

    friend bool operator<(const Node&l, const Node&r) {
        return l.d > r.d;
    }
} V[maxn];
struct Edge{
    int u, v, w, next;
} E[maxm];
int n, m, cnt;
void add(int u, int v, int w)
{
    E[++cnt].u = u;
    E[cnt].v = v;
    E[cnt].w = w;
    E[cnt].next = V[u].first;
    V[u].first = cnt;
}
priority_queue<Node> heap;
void dijkstra()
{
    for (int i = 1; i <= n; i++){
        V[i].done = false;
        V[i].d = INF;
    }
    V[1].d = 0;
    heap.push(V[1]);
    while (!heap.empty()){
        auto tmp = heap.top();
        heap.pop();
        for (int k = tmp.first; k; k = E[k].next){
            if (!V[E[k].v].done && V[E[k].v].d > tmp.d + E[k].w){
                V[E[k].v].d = tmp.d + E[k].w;
                heap.push(V[E[k].v]);
            }
        }
        tmp.done=true;
    }
}
int main()
{
    n = read(), m = read();
    for (int i = 1, t1, t2, t3; i <= m; i++)
    {
        t1 = read();
        t2 = read();
        t3 = read();
        add(t1, t2, t3);
    }
    dijkstra();
    for (int i = 1; i <= n; i++)
    {
        if (V[i].d == INF)
            printf("%d ", -1);
        else
            printf("%lld ", V[i].d);
    } 
    system("pause");
    return 0;
}
```

