#### 题目描述

现有$k$个逻辑变量$x_1,…,x_k$，给出$n$个三元组$(a_i, b_i, c_i)$，其中$a_i, b_i, c_i$可以取任意一个逻辑变量或其否定，每个三元组表示三个逻辑式至少两个为真，问是否能找到一种赋值法，满足所有$n$个三元组。

#### 输入格式

第一行输入一个数$T$，代表测试样例组数。

在每组测试样例中，第一行输入用空格分隔的两个数$k, n$，代表逻辑变量的个数和三元组的个数。

之后$n$行，每行输入用空格分隔的三个非零整数$a_i, b_i, c_i$，代表每个三元组的三个元素。这三个数中，以$a_i$为例，若为正数，代表逻辑式$x_{a_i}$；若为负数，代表逻辑式$\overline x_{a_i}$

#### 输出格式

输出$T$行，每行一个样例，若可满足，输出yes，否则输出no。

#### 样例

**样例1**

输入

```
4
3 2
1 2 3
-1 -2 3
3 2
1 2 3
-1 -2 -3
6 5
1 2 3
-2 -3 -4
3 4 5
-4 -5 -6
5 6 1
1 2
1 -1 1
-1 1 -1
```

输出

```
yes
no
yes
no
```

#### **数据范围**

对于20%的数据，$1 \le k \le 10, 1 \le n \le 100$。

对于50%的数据，$1 \le k \le 100, 1 \le n \le 100$。

对于100%的数据，$1 \le k \le 10^4, 1 \le n \le 10^4, 1 \le T \le 10, 1 \le |a_i|, |b_i|, |c_i| \le k$*k*。





因为对于每个三元组，要求至少有两个逻辑式为真。我们可以断言，对于$A  B  C$ ，一旦$\overline A$，立刻可以推导出$B \and C$。可以通过有向图来表示这样的推导关系：图中顶点数是逻辑变量个数的2倍，分别代表取True和取False.对于每个三元组，我们得到6条推理，也就是在图中加入6条边。完成建图后求强连通分量，如果一个逻辑变量和它的反位于同一强连通分量中，说明它们可以互相推导，这显然是错误的。

```
#include <bits/stdc++.h>
#define maxn 20105
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
    int visit, scc;
    int first, rfirst;
} V[maxn];
struct Edge {
    int u, v, next;
} E[maxm];
int cnt_in_add;
void add(int u, int v)
{
    E[++cnt_in_add].u = u;
    E[cnt_in_add].v = v;
    E[cnt_in_add].next = V[u].first;
    V[u].first = cnt_in_add;

    E[++cnt_in_add].u = v;
    E[cnt_in_add].v = u;
    E[cnt_in_add].next = V[v].rfirst;
    V[v].rfirst = cnt_in_add;
}

int order[maxn];
int cnt_in_order, cnt_in_scc;
int n;

void dfs(int x)
{
    V[x].visit = 1;
    for (int i = V[x].first; i; i = E[i].next)
        if (V[E[i].v].visit == 0)
            dfs(E[i].v);
    order[++cnt_in_order] = x;
}

void rdfs(int x)
{
    V[x].scc = cnt_in_scc;
    V[x].visit = 1;
    for (int i = V[x].rfirst; i; i = E[i].next)
        if (V[E[i].v].visit == 0)
            rdfs(E[i].v);
}

void scc()
{
    for (int i = 1; i <= n; i++)
        if (V[i].visit == 0)
            dfs(i);
    for (int i = 1; i <= n; i++)
        V[i].visit = 0;
    for (int i = n; i >= 1; i--)
        if (V[order[i]].visit == 0)
            cnt_in_scc++, rdfs(order[i]);
}

void once()
{
    int t1 = read(), t2 = read();
    cnt_in_add = 0;
    cnt_in_scc = 0;
    cnt_in_order = 0;
    memset(E, 0, sizeof(E));
    memset(V, 0, sizeof(V));
    n = 2 * t1;
    for (int i = 1; i <= t2; i++) {
        int a = read(), b = read(), c = read();
        int absa = abs(a), absb = abs(b), absc = abs(c);
        int sa = (a >= 0), sb = (b >= 0), sc = (c >= 0);
        add(absa + t1 * sa, absb + t1 * (1 - sb));
        add(absb + t1 * sb, absa + t1 * (1 - sa));
        add(absa + t1 * sa, absc + t1 * (1 - sc));
        add(absc + t1 * sc, absa + t1 * (1 - sa));
        add(absb + t1 * sb, absc + t1 * (1 - sc));
        add(absc + t1 * sc, absb + t1 * (1 - sb));
    }
    scc();
    for (int i = 1; i <= t1; i++) {
        if (V[i].scc == V[i + t1].scc) {
            printf("no\n");
            return;
        }
    }
    printf("yes\n");
}
int main()
{
    int t = read();
    while (t--)
        once();
    return 0;
}
```

