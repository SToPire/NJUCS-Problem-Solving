#### 题目描述

给一个正整数$n$，求在所有（大于$0$的）$n$的倍数中，二进制表示下最少有几个$1$。

例如$n=11$时，取$11$的倍数$33$，其二进制表示为$100001$，有$2$个1。可以证明所有$11$的倍数二进制下至少有$2$个1，故答案为$2$。

#### 输入格式

第一行1个正整数$T$，表示测试组数。

接下来$T$行，第$i+1$行一个正整数$n$，表示第$i$组数据。

#### 输出格式

共$T$行，第$i$行一个正整数，表示第$i$组数据的答案。

#### 样例

##### 样例输入 1

```plain
3
4
7
11
```

##### 样例输出 1

```plain
1
3
2
```

#### 数据范围与提示

对于前30%的数据，$1\leq n \leq 20$。

对于前70%的数据，$1\leq n \leq 1000$。

对于100%的数据，$1≤n≤1000000$，$1≤T≤3$。

Hint：本周学习的是最短路问题，建模是本题的关键。



图中顶点是$0,1,2...n-1$，表示$\mod n$的余数。每个点有两条出边，分别为$(i,2i\mod n,0)$和$(i,2i+1 \mod n,1)$，分别代表在二进制表示后添一个0和添一个1.目标是寻找一条从点1（至少有1个1）到点0（代表n的倍数）的最短路。

```
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
#define maxm 2000005
#define maxn 1000005
#define INF 1e9
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
struct Edge
{
    int u, v, w, next;
} e[maxm];
int n, m, t, cnt, done[maxn], first[maxn];
//{节点编号，d值}
vector<pair<int, int>> d(maxn, {0, INF});
bool cmp(const pair<int, int> &i, pair<int, int> &j)
{
    return i.second > j.second;
}
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp) *> heap(cmp);
void add(int u, int v, int w)
{
    e[++cnt].u = u;
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = first[u];
    first[u] = cnt;
}
void dijkstra()
{
    for (int i = 1; i <= n; i++)
        d[i].first = i;
    d[1].second = 0;
    heap.push(d[1]);
    while (!heap.empty())
    {
        auto tmp = heap.top();
        heap.pop();
        if (done[tmp.first])
            continue;
        done[tmp.first] = 1;
        for (int k = first[tmp.first]; k; k = e[k].next)
        {
            d[e[k].v].second = min(d[e[k].v].second, tmp.second + e[k].w);
            heap.push(d[e[k].v]);
        }
    }
}
void clear()
{
    cnt = 0;
    for (int i = 0; i < maxn; i++)
    {
        done[i] = first[i] = 0;
        d[i].second = INF;
    }
    for (int i = 0; i < maxm; i++)
    {
        e[i] = {0, 0, 0, 0};
    }
}
int main()
{
    t = read();
    vector<int> ans;
    for (int index = 1; index <= t; index++)
    {
        n = read();
        if(n==1){
            ans.push_back(1);
            continue;
        }
        for (int i = 1; i <= n - 1;i++){ //把0号点作为n号点
            int t1 = (2 * i) % n;
            if(!t1)
                t1 = n;
            int t2 = (2 * i + 1) % n;
            if (!t2)
                t2 = n;
            add(i, t1, 0);
            add(i, t2, 1);
        }
        dijkstra();
        ans.push_back(d[n].second + 1);
        clear();
    }
    for (auto e : ans)
        cout << e << endl;
    system("pause");
    return 0;
}
```

