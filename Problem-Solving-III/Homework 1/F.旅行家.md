#### 题目描述

`AceSrc` 是著名的旅行家，他决定从$1$号城市出发，前往全国各地旅行。

全国一共有$n$座城市，有$m$条双向道路相连，每条道路有一个权值$1\leq w \leq 10^9$。

当 `AceSrc` 走完一段路径后，他会把他经过的边的权值拼接起来，得到一个新的数字。例如当 `AceSrc` 经过的边权依次为$5,15,30$，他会得到$51530$。

`AceSrc` 想知道，对于每个$2\leq i\leq n$，从$1$号城市走到$i$号城市的所有路径中，按照上述方法所能得到的拼接后的最小值是多少。

由于答案可能很大，请输出答案对$10^9+7$取模的答案。

（注意：求的是最小值模$10^9+7$，不是模$10^9+7$后的最小值）。

#### 输入格式

第一行2个正整数$n,m$，表示城市的个数以及公路的条数。

接下来$m$行，每行$3$个正整数$u,v,w$，表示第$i$条公路连接城市$u$和城市$v$，权值为$w$，保证$1≤u,v≤n,u≠v$，$1≤w≤10^9$。

#### 输出格式

共$n-1$行，第$i$行表示城市$1$到城市$i+1$的答案。

若城市$1$无法到达城市$i+1$，则第$i$行输出$-1$。

#### 样例

##### 样例输入 1

```plain
5 4
1 2 6
2 3 54
1 4 32
4 3 1
```

##### 样例输出 1

```plain
6
321
32
-1
```

#### 数据范围与提示

对于前30%的数据，$1≤n≤200 $，$1≤m≤1000$。

对于额外40%的数据，$1\leq w \leq 9$。

对于100%的数据，$1\leq n,m \leq 100000, 1\leq w \leq 10^9$。

数据可能有重边，保证没有自环。



仍然做dij求最短路，每个点存当前拼接出的最短字符串，以及当前字符串$\mod 10^9+7$后的值。模运算的性质保证了，每次拼接时先对当前结果取模再拼接取模，和对一直拼接得到的长串取模的结果是一样的。

注意字符串的序需要重新定义。

```
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
using namespace std;
#define maxm 200005
#define maxn 100005
#define INF 1e19
#define mmoodd 1000000007
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
bool operator>(const string& a, const string& b)
{
    if (a.size() > b.size())
        return true;
    else if (a.size() < b.size())
        return false;
    else {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] > b[i])
                return true;
            else if (a[i] < b[i])
                return false;
        }
    }
    return false;
}
struct Node {
    int no;
    int first;
    string str;
    ull val;
    bool done;

    friend bool operator<(const Node& l, const Node& r)
    {
        if (l.str == "")
            return true;
        if (l.str.size() > r.str.size())
            return true;
        else if (l.str.size() < r.str.size())
            return false;
        else
            return l.str > r.str;
    }
} V[maxn];
struct Edge {
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
ull mypow(int di, int zhi)
{
    ull ans = 1;
    for (int i = 1; i <= zhi; i++) {
        ans *= di;
    }
    return ans;
}
void dijkstra()
{
    for (int i = 1; i <= n; i++) {
        V[i].str = "";
        V[i].no = i;
    }
    heap.push(V[1]);
    while (!heap.empty()) {
        auto tmp = heap.top();
        heap.pop();
        V[tmp.no].done = true;

        
        for (int k = tmp.first; k; k = E[k].next) {
            if (!V[V[E[k].v].no].done && (V[E[k].v].str == "" || V[E[k].v].str > tmp.str + to_string(E[k].w))) { //这里必须把std:string的大于号重载掉，否则不是需要的行为
                V[E[k].v].str = tmp.str + to_string(E[k].w);
                V[E[k].v].val = ((tmp.val * (long long)mypow(10, to_string(E[k].w).size())) % mmoodd + E[k].w) % mmoodd;
                heap.push(V[E[k].v]);
            }
        }
    }
}
int main()
{
    n = read(), m = read();
    for (int i = 1, t1, t2, t3; i <= m; i++) {
        t1 = read();
        t2 = read();
        t3 = read();
        add(t1, t2, t3);
        add(t2, t1, t3);
    }
    dijkstra();
    for (int i = 2; i <= n; i++) {
        if (V[i].str == "")
            printf("%d\n", -1);
        else
            printf("%lld\n", V[i].val);
    }
    system("pause");
    return 0;
}
```



