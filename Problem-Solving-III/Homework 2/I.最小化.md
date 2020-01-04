#### 题目描述

现在有 $n$ 个取值只能为 $-W$ 或  $W$的变量 $w_1, w_2, \cdots, w_n$. 你现在需要给这 $n$ 个变量赋予值, 这些值需要满足一定限制, 使目标函数最小.

##### 目标函数

现在有 $p$ 个九元组 $(x_i, y_i, z_i, a_i, b_i, c_i, d_i, e_i, f_i)$, 定义第$i$个 **部分代价函数** $H_i$为:

$\begin{aligned} H_i=a_i|w_{x_i}-w_{y_i}|+b_i|w_{y_i}-w_{z_i}|+c_i|w_{z_i}-w_{x_i}|+ \\ d_i(w_{x_i}-w_{y_i})+e_i(w_{y_i}-w_{z_i})+f_i(w_{z_i}-w_{x_i}) \end{aligned}$

目标函数为$\mathcal{O}(w_1, w_2, \cdots, w_n)=\sum_{i=1}^n w_i + \sum_{i=1}^p H_i$, 请最小化该目标函数.

##### 限制

一共有$q$ 个限制, 以三元组 $(x_i, y_i, r_i)$ 的形式给出.

- 若 $r_i=0$, 则限制 $w_{x_i} \le w_{y_i}$
- 若 $r_i=1$, 则限制 $w_{x_i} = w_{y_i}$
- 若 $r_i=2$, 则限制 $w_{x_i} < w_{y_i}$

第一行包括一个整数 $T$, 表示测试组数.

对于每个测试组, 第一行包括 $4$ 个整数 $n, W, p, q,$ 分别表示变量个数, $w_i$ 取值绝对值, 部分代价函数个数, 以及限制个数.

接下来 $p$ 行, 第 $i$ 行包括 $9$ 个整数 $x_i, y_i, z_i, a_i, b_i, c_i, d_i, e_i, f_i$, 表示第 $i$ 个部分代价函数的参数, 这些数字都是非负整数.

接下来 $q$ 行, 第 $i$ 行包括 $3$个整数 $x_i, y_i, r_i$, 表示第 $i$个限制.

#### 输出格式

对每个测试组, 输出一个整数表示答案.

#### 样例

##### 样例输入

```plain
1
3 1 1 1
1 2 3 1 1 1 1 1 1 
1 2 2
```

##### 样例输出

```plain
3
```

#### 数据范围与提示

题目保证有解，一共  $5$ 个数据点

| 编号 | $n$        | $W$           | $p,q$      | $a,b,c$    | $d,e,f$    |
| ---- | ---------- | ------------- | ---------- | ---------- | ---------- |
| 1    | $\le 10$   | $\le 10$      | $\le 10$   | $\le 10$   | $\le 10$   |
| 2    | $\le 1000$ | $\le 1000000$ | $\le 3000$ | $\le 1000$ | $=0$       |
| 3    | $\le 1000$ | $\le 1000000$ | $\le 3000$ | $=0$       | $\le 1000$ |
| 4, 5 | $\le 1000$ | $\le 1000000$ | $\le 3000$ | $\le 1000$ | $\le 1000$ |







每个点有一条从s出发的入边，指向t的出边，分别代表选择$-W$和$W$，这条边的权值还表示了$H$中的后三项。

对于$H$中的前三项，当且仅当两个选取同样的值是为$0$，否则为$2W$，可以通过在这两个点之间加双向权值为$2W$的边描述这一条件。

此外对于每个限制条件，可以通过添加权值为无穷的边来描述。

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef unsigned long long ull;
typedef long long ll;
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

/*最大流模板---------------------------------*/
/*add(x,y,v,w):添加权值为v的边(x,y)和权值为w的边(y,x)*/
/* s和t分别是源和漏*/
#define inf 1e18
#define N 1005
#define M 40005
int s, t, et = 1,  cur[M], q[M], L, R;
int la[N], d[N];
struct E {
    int to;
    ll flow;
    int nxt;
} e[M];
void add(int x, int y, ll v, ll w)
{
    e[++et] = (E){ y, v, la[x] }, la[x] = et;
    e[++et] = (E){ x, w, la[y] }, la[y] = et;
}
int bfs()
{
    memset(d, 0, sizeof(d));
    for (q[L = R = 0] = t, d[t] = 1; L <= R; L++)
        for (int i = la[q[L]]; i; i = e[i].nxt)
            if (e[i ^ 1].flow && !d[e[i].to])
                d[q[++R] = e[i].to] = d[q[L]] + 1;
    return d[s];
}
ll dfs(int x, ll ret)
{
    if (x == t || ret == 0)
        return ret;
    ll tmp, flow = 0;
    for (int& i = cur[x]; i; i = e[i].nxt)
        if (d[x] == d[e[i].to] + 1) {
            tmp = dfs(e[i].to, e[i].flow < ret - flow ? e[i].flow : ret - flow);
            e[i].flow -= tmp, e[i ^ 1].flow += tmp, flow += tmp;
            if (ret == flow)
                return flow;
        }
    return flow;
}
ll maxflow()
{
    ll flow = 0;
    while (bfs())
        memcpy(cur, la, sizeof(la)), flow += dfs(s, inf);
    return flow;
}
/*--------------------------------------*/
ll in[N], out[N];
void init()
{
    et = 1;
    memset(la, 0, sizeof(la));
    memset(cur, 0, sizeof(cur));
    memset(d, 0, sizeof(d));
    memset(q, 0, sizeof(q));
}
void work()
{
    const ll BIG = 1e15; //负数偏移量
    int n = read(), W = read(), P = read(), Q = read();
    s = n + 1, t = n + 2;
    for (int i = 1; i <= n;i++)
        in[i] = -W, out[i] = W;
    for (int i = 1; i <= P;i++){
        int X = read(), Y = read(), Z = read(), A = read(), B = read(), C = read(), D = read(), E = read(), F = read();

        //对应H中前三项，如果同时割去(s,x)(s,y)或(x,t)(y,t)就不需要割边(x,y)
        //否则需要割去(x,y)，且该边的值是2W*A
        add(X, Y, 2 * W * A, 2 * W * A);
        add(Y, Z, 2 * W * B, 2 * W * B);
        add(X, Z, 2 * W * C, 2 * W * C);

        //对应H中后三项
        in[X] += (D - F) * (ll)(-W);
        in[Y] += (-D + E) * (ll)(-W);
        in[Z] += (-E + F) * (ll)(-W);
        out[X] += (D - F) * (ll)W;
        out[Y] += (-D + E) * (ll)W;
        out[Z] += (-E + F) * (ll)W;
    }
    for (int i = 1; i <= Q;i++){
        int xx = read(), yy = read(), rr = read();
        switch(rr){
            case 0:
                add(xx, yy, inf, 0);
                break;
            case 1:
                add(xx, yy, inf, inf); //两个点必须取同样的值
                break;
            case 2:
                out[xx] = in[yy] = (ll)inf; //x只能取负，y只能取正
                break;
        }
    }
    for (int i = 1; i <= n;i++){
        add(s, i, in[i] + BIG, 0);
        add(i, t, out[i] + BIG, 0);
    }
    cout << maxflow() - n * BIG << endl;
}
int main(void)
{
    int T = read();
    while(T--){
        init();
        work();
    }
    system("pause");
    return 0;
}
```

