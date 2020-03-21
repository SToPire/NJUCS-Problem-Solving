#### 题目描述

给定$n$个物品，每个物品有体积$c_i$和价值$v_i$，现有一个容量为$V$的背包，要求选择一部分物品放入背包，每个物品最多放一次，并满足放入物品的体积和小于等于$V$，在这样的条件下使得价值和最大，问最终能获得的最大价值是多少。

#### 输入格式

第一行输入一行空格分隔的两个数$n, V$，代表物品数和背包容量。

接下来每行输入一个物品$c_i, v_i$，代表物品体积和物品价值。

#### 输出格式

输出一行一个整数，表示最终能获得的最大价值。

#### 样例

**样例1**

输入

```
3 3
1 2
2 5
3 6
```

输出

```
7
```

**样例2**

输入

```
3 4
1 2
2 5
3 6
```

输出

```
8
```





对于前半和后半部分分开进行dfs，先对前半部分搜索并对所有合法结果排序，原则是重量小的在前，若重量相等，价格高的在前。第68-71行保证对每种重量只保留最优价格。在对后半部分搜索时，每确定一种方案，就用二分查找确定当前剩余重量最大能取得多少价格，相加后维护最大值即可。

```c++
#include <algorithm>
#include <iostream>
#include <vector>
#define maxn 40
typedef unsigned long long ull;
using namespace std;

int w[maxn + 3], p[maxn + 3], n, V;
ull ans;

struct info {
    ull w, p;
} b_info[1100000];
int b_info_ptr = 0, b_eff_cnt = 1;
void dfs_b(int depth, ull W, ull P)
{
    if (W > V)
        return;
    if (depth > n / 2) {
        b_info[++b_info_ptr].w = W;
        b_info[b_info_ptr].p = P;
        return;
    }
    dfs_b(depth + 1, W, P);
    dfs_b(depth + 1, W + w[depth], P + p[depth]);
}
bool order(info& l, info& r)
{
    if (l.w == r.w)
        return l.p > r.p;
    else
        return l.w < r.w;
}

int binSearch(int x)
{
    int l = 1, r = b_eff_cnt + 1;
    while (l < r - 1) {
        int mid = (l + r) / 2;
        if (b_info[mid].w <= x)
            l = mid;
        else
            r = mid;
    }
    return l;
}

void dfs_e(int depth, ull W, ull P)
{
    if (W > V)
        return;
    if (depth > n) {
        ans = max(ans, b_info[binSearch(V - W)].p + P);
        return;
    }
    dfs_e(depth + 1, W, P);
    dfs_e(depth + 1, W + w[depth], P + p[depth]);
}

int main(void)
{
    cin >> n >> V;
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> p[i];

    dfs_b(1, 0, 0);
    sort(b_info + 1, b_info + 1 + b_info_ptr, order);
    for (int i = 2; i <= b_info_ptr; ++i) {
        if (b_info[b_eff_cnt].p < b_info[i].p)
            b_info[++b_eff_cnt] = b_info[i];
    }
    dfs_e(n / 2 + 1, 0, 0);
    cout << ans;
    return 0;
}

```

