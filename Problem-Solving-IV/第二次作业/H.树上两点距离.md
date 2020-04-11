#### 题目描述

给定$n$个点$n - 1$条边的树，$m$个询问每次询问树上两点，求它们的最短距离。

#### 输入格式

第一行输入两个数$n$和$m$

#### 输出格式

接下来$n - 1$行，每行输入三个数$x, y, v$，代表从编号为$x$的点到编号为$y$的点有一条权重为的$v$边，点从1开始编号。

接下来$m$行，每行输入两个数$x, y$，代表询问$x$到$y$的最短距离。

#### 样例

**样例输入1**

```
5 3
1 2 2
1 3 3
2 4 5
2 5 7
2 3
3 4
4 5
```

**样例输出1**

```
5
10
12
```

#### 数据范围与提示

对于 30% 的数据，$n \le 10, m \le 10$。

对于 70% 的数据，$n \le 10000, m \le 10000$。

对于 100% 的数据，$n \le 100000, m \le 100000, 1 \le x, y \le n, 1 \le v \le 1000$。



这和求树上两点最近公共祖先是同一个问题，可以任选一个根，并在`dfs`中维护每个点到根的距离。最后的答案就是$x, y$的距离和减去它们公共祖先距离的两倍。

```c++
#include <bits/stdc++.h>
#define maxn 100105
#define maxm 200105
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
struct Node {
    int sz, depth, father, son, top, distToRoot;
    int first;
} V[maxn];
struct Edge {
    int u, v, w, next;
} E[maxm];
int cnt;
void add(int u, int v, int w)
{
    E[++cnt].u = u;
    E[cnt].v = v;
    E[cnt].w = w;
    E[cnt].next = V[u].first;
    V[u].first = cnt;
}
int n, m, s;
void dfs1(int x)
{
    V[x].sz = 1;
    V[x].depth = V[V[x].father].depth + 1;
    for (int k = V[x].first; k; k = E[k].next) {
        int tmp = E[k].v;
        if (tmp == V[x].father)
            continue;
        V[tmp].father = x;
        V[tmp].distToRoot = V[x].distToRoot + E[k].w;
        dfs1(tmp);
        V[x].sz += V[tmp].sz;
        if (V[x].son == 0 || V[V[x].son].sz < V[tmp].sz)
            V[x].son = tmp;
    }
}

void dfs2(int x, int v)
{
    V[x].top = v;
    if (V[x].son)
        dfs2(V[x].son, v);
    for (int k = V[x].first; k; k = E[k].next) {
        int tmp = E[k].v;
        if (tmp == V[x].father || tmp == V[x].son)
            continue;
        dfs2(tmp, tmp);
    }
}

int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= n - 1; i++) {
        int x = read();
        int y = read();
        int w = read();
        add(x, y, w);
        add(y, x, w);
    }
    dfs1(1);
    dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        int x = read();
        int y = read();
        int tmp = (V[x].distToRoot + V[y].distToRoot);
        while (V[x].top != V[y].top) {
            if (V[V[x].top].depth <= V[V[y].top].depth)
                y = V[V[y].top].father;
            else
                x = V[V[x].top].father;
        }
        auto upper = (V[x].depth > V[y].depth) ? y : x;
        cout << tmp - 2 * V[upper].distToRoot << endl;
    }
    return 0;
}
```

