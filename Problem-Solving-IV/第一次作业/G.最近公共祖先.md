#### 题目描述

给定一棵有根树，请求出指定两个点直接最近的公共祖先。

#### 输入格式

第一行包含三个正整数$N,M,S$，分别表示树的结点个数、询问的个数和树根结点的序号。

接下来 $N-1$ 行每行包含两个正整数 $x, y$，表示 $x$ 结点和 $y$ 结点之间有一条直接连接的边（数据保证可以构成树）。

接下来 $M$ 行每行包含两个正整数 $a, b$，表示询问 $a$ 结点和 $b$ 结点的最近公共祖先。

#### 输出格式

输出包含 $M$ 行，每行包含一个正整数，依次为每一个询问的结果。

#### 样例

输入

```
5 5 4
3 1
2 4
5 1
1 4
2 4
3 2
3 5
1 2
4 5
```

输出

```
4
4
1
4
4
```

#### 数据范围与提示

对于 30% 的数据，$N \le 10, M \le 10$。

对于 70% 的数据，$N \le 10000, M \le 10000$。

对于 100% 的数据，$N \le 100000, M \le 100000, 1 \le a, b \le N$。





基本思路是用并查集的思想把整棵树维护成一系列“树枝”的集合。一条树枝上的结点有共同的`top`值。对于每次查询，我们从较深的结点向上追溯到`.top.father`，也就是当前树枝的父树枝上，直到两个结点位于同一树枝为止。



为了维护这一数据结构，`dfs`时我们总是将当前结点规模最大的子树设为`son`，其他的都作为旁支。



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
    int sz, depth, father, son, top;
    int first;
} V[maxn];
struct Edge {
    int u, v, next;
} E[maxm];
int cnt;
void add(int u, int v)
{
    E[++cnt].u = u;
    E[cnt].v = v;
    E[cnt].next = V[u].first;
    V[u].first = cnt;
}
int n, m, s;
void dfs1(int x)
{
    V[x].sz = 1;
    V[x].depth = V[V[x].father].depth + 1;
    for (int k = V[x].first; k;k = E[k].next){
        int tmp = E[k].v;
        if(tmp == V[x].father)
            continue;
        V[tmp].father = x;
        dfs1(tmp);
        V[x].sz += V[tmp].sz;
        if(V[x].son == 0 || V[V[x].son].sz < V[tmp].sz)
            V[x].son = tmp;
    }
}

void dfs2(int x,int v){
    V[x].top = v;
    if(V[x].son)
        dfs2(V[x].son, v);
    for (int k = V[x].first; k;k=E[k].next){
        int tmp = E[k].v;
        if(tmp == V[x].father || tmp == V[x].son)
            continue;
        dfs2(tmp, tmp);
    }
}

int main()
{
    n = read();
    m = read();
    s = read();
    for (int i = 1; i <= n - 1;i++){
        int x = read();
        int y = read();
        add(x, y);
        add(y, x);
    }
    dfs1(s);
    dfs2(s, s);
    for (int i = 1; i <= m;i++){
        int x = read();
        int y = read();
        while(V[x].top != V[y].top){
            if(V[V[x].top].depth <= V[V[y].top].depth)
                y = V[V[y].top].father;
            else
                x = V[V[x].top].father;
        }
        cout << ((V[x].depth > V[y].depth) ? y : x) << endl;
    }
    return 0;
}
```

