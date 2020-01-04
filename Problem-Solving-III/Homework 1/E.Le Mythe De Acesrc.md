#### 题目描述

作为NJU的红太阳，有一天,Acesrc想出了这样一个问题:

给定一个包含$n$个数的集合$A={a_1,a_2,…,a_n}(0<a_1<a_2<⋯<a_n)$以及$q$次询问，每次询问一个数$x$是否能表示成集合$A$中一系列数字的和。例如$A={2,5,7}$，那么可以被表示成集合$A$中一系列数字的和的数字包括但不限于:$0$（可以表示成$0$个数字之和），$4=2+2$和$12=5+7=7+5=2+2+2+2+2+2$. 不可以被表示成集合$A$中一系列数字的和的数字包括但不限于:$1$和$3$.

显然，这个题目对于Acesrc来说太简单了，因此他并没有给出解法。请问你可以解决这个问题吗?

#### 输入格式

第一行包含一个正整数$n$,表示集合内数的个数。 第二行包含$n$个正整数$a_1,a_2,…,a_n$，表示集合内的数。 第三行包含一个正整数$q$，表示询问的次数。 第四行包含$q$个正整数$x_1,x_2,…,x_q$其中$x_i$表示第$i$次询问的值。 输入数据保证$0<a_1<a_2<⋯<a_n$

#### 输出格式

输出应当包含$q$行。对于第$i$个询问，如果$x_i$能表示成集合$A$中一系列数字的和，在一行内输出"Acesrc!"(不包含引号)，否则在一行内输出"Acesrc?"(不包含引号)

#### 样例

##### 样例输入 1

```plain
3
2 5 7
6
0 1 4 12 3 2
```

##### 样例输出 1

```plain
Acesrc!
Acesrc?
Acesrc!
Acesrc!
Acesrc?
Acesrc!
```

#### 数据范围与提示

对于$20\%$的测试数据，满足$1\leq n\leq 20,1\leq a_i\leq 100,1\leq q\leq 100,0\leq x_i\leq 1000$

对于$50\%$的测试数据，满足$1\leq n\leq 100,1\leq a_i\leq 500,1\leq q\leq 10000,0\leq x_i\leq 1000$

对于$100\%$的测试数据，满足$1\leq n\leq 10000,1\leq a_i\leq 20000,1\leq q\leq 100000,0\leq x_i\leq 10^9$





建模：图中点$v_0,v_1,...,v_{a_1-1}$的下标是$\mod a_1$的余数，每个点$v_i$有$n-1$条出边$e_2,e_3...e_n$，权值分别为$a_2,a_3,...,a_n$，边$e_k$指向点$v_j$，其中$j$满足$(i+a_k) \mod n =j$

计算图中以点$v_0$为源点的最短路，$v_0到v_i$的最短路长度代表了用$a_2,a_3,...,a_n$所能表示的，$\mod a_1$余$i$的数的最小值，这条最短路则代表了从$a_2,a_3,...,a_n$中选数的方式。

对于每次查询，先对$x_i$取模，并与该余数对应的最短路长度比较。若$x_i \ge 最短路长度$，说明可以在该选数方式的基础上增加若干个$a_1$来实现题意。否则说明$x_i$无法被表示。



1. 实现中点的标号整体移动了1，为$1,2,...,a_1$
2. 存边的话总数为$2*10^8$条，无法存下。但因为每条边的目标结点和权值我们可以立刻求出，可以在dij时现场枚举当前结点的后继。

```
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
#define maxm 20000005
#define maxn 20005
#define INF 1e18
#define ull unsigned long long
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
    bool done;
    int first;
    ull d;
    int no;
    friend bool operator<(const Node& l, const Node& r)
    {
        return l.d > r.d;
    }
} V[maxn];
priority_queue<Node> heap;
int n, q, A[20005], X[100005];
void dijkstra()
{
    for (int i = 1; i <= A[1]; i++) {
        V[i].done = false;
        V[i].d = INF;
        V[i].no = i;
    }
    V[1].d = 0;
    heap.push(V[1]);
    while (!heap.empty()) {
        auto tmp = heap.top();
        heap.pop();
        for (int i = 2; i <= n;i++){
            int y = (tmp.no - 1 + A[i]) % A[1] + 1; //相邻节点
            if(V[y].d>tmp.d+A[i]){
                V[y].d = tmp.d + A[i];
                heap.push(V[y]);
            }
        }
        tmp.done = true;
    }
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++) {
        A[i] = read();
    }
    q = read();
    for (int j = 1; j <= q; j++) {
        X[j] = read();
    }
    dijkstra();
    for (int j = 1; j <= q; j++) {
        if (V[X[j] % A[1] + 1].d > X[j])
            printf("Acesrc?\n");
        else
            printf("Acesrc!\n");
    }
    system("pause");
    return 0;
}
```

