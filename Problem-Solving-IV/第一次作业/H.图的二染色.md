#### 题目描述

给定一个$n$个点$m$个边的无向图，问是否存在一种给图上的点染色的方法，满足

- 每个点有且仅有一种颜色
- 只有两种颜色可选，即对所有点$v$, $\text{color}(v) \in \{\text{red}, \text{blue}\}$
- 相邻的点不能染相同颜色

#### 输入格式

每个测试数据，第一行输入两个数$n, m$，代表点数和边数

接下来$m$行，每行输入两个数$x, y (1 \le x, y \le n)$，代表点$x$和点$y$有边相连

输入保证$x \ne y$且同一条边只出现一次

#### 输出格式

若存在满足以上条件的方案，输出`yes`，并给出一种染色方案，即按照顺序第一行输出点$1$的颜色，第二行输出点$2$的颜色，以此类推。

若不存在，输出`no`。

#### 样例

**样例输入1**

```
2
2 1
1 2
3 3
1 2
2 3
3 1
```

**样例输出1**

```
yes
red
blue
no
```

#### 数据范围与提示

对100%的数据 $1 \le n \le 10^5, 1 \le m \le \min(\frac {n (n - 1)} 2, 10^5), 1 \le T \le 5$





遍历所有点，如果没有涂色就随便选一个颜色dfs即可，dfs返回`false`说明无法找到合法的涂色方案。之所以要遍历所有点是因为图里可能有多个连通分量。

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxm 200105
#define maxn 100005

inline ll read()
{
    ll x = 0, k = 1;
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
    int color;
    int first;
} V[maxn];
struct Edge {
    int u, v, next;
} E[maxm];
int n, m, cnt;
void add(int u, int v)
{
    E[++cnt].u = u;
    E[cnt].v = v;
    E[cnt].next = V[u].first;
    V[u].first = cnt;
}


enum {
    NONE,
    RED,
    BLUE
};


bool dfs(int num,int color)
{
    V[num].color = color;
    for (int it = V[num].first; it;it = E[it].next){
        if(V[E[it].v].color == NONE){
            if(dfs(E[it].v,3-color) == false)
                return false;
        }else if(V[E[it].v].color != 3 - color)
            return false;
    }
    return true;
}

void once()
{
    cnt = 0;
    n = read();
    m = read();
    memset(E, 0, sizeof(E));
    memset(V, 0, sizeof(V));
    for (int i = 1; i <= m;i++){
        int t1 = read(), t2 = read();
        add(t1, t2);
        add(t2, t1);
    }
    for (int i = 1; i <= n;i++){
        if(V[i].color==NONE){
            if(dfs(i,RED)==false){
                printf("no\n");
                return;
            }
        }
    }
    printf("yes\n");
    for (int i = 1; i <= n;i++)
        if(V[i].color==RED)
            printf("red\n");
        else if(V[i].color==BLUE)
            printf("blue\n");
}

int main()
{
    int t = read();
    while(t--)
        once();
    return 0;
}
```

