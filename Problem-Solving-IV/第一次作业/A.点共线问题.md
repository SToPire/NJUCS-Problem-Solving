#### 题目描述

任给平面上的$n$个点$(x_i, y_i)$，点与点之间**可能重合**，判断位于同一直线上的点的最大个数。

#### 输入格式

第一行输入一个数$n$，代表点的个数。

之后$n$行，每行输入用空格分隔的两个**整数**$x_i, y_i$，代表点$i$的坐标。

#### 输出格式

一个整数，代表位于同一直线上的点的最大个数。

#### 样例

**样例1**

输入

```
9
0 0
1 0
1 1
0 1
-1 1
-1 0
-1 -1
0 -1
1 -1
```

输出

```
3
```

**样例2**

输入

```
3
0 0
1 1
0 1
```

输出

```
2
```

#### 数据范围与提示

对于20%的数据，$1 \le n \le 20, -10 \le x_i, y_i \le 10$。

对于50%的数据，$1 \le n \le 100, -10^5 \le x_i, y_i \le 10^5$。

对于100%的数据，$1 \le n \le 1000, -10^9 \le x_i, y_i \le 10^9$。



对于每个点，计算其他点到它的斜率并排序。因为直接使用斜率会带来斜率不存在和除以0的问题，可以使用一个二元组来代表横坐标和纵坐标的差值，以此表示斜率。

```c++
#include <bits/stdc++.h>
using namespace std;

struct data {
    int x, y;
} A[1005];
bool order(data& A, data& B)
{
    if (A.x == B.x)
        return A.y < B.y;
    else
        return A.x < B.x;
}

int main()
{
    int ans = 0;
    int n;
    cin >> n;
    int x[1005], y[1005];
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n && j != i; j++) {
            int dx = x[j] - x[i];
            int dy = y[j] - y[i];
            int g = __gcd(abs(dx), abs(dy)); // 注意：gcd(0,x)==x
            if (g) { //i.e. (dx==dy==0)
                dx /= g;
                dy /= g;
            }
            if (dx < 0) {
                dx = -dx;
                dy = -dy;
            }
            if (dx == 0) {
                dy = abs(dy);
            }
            A[++cnt].x = dx;
            A[cnt].y = dy;
        }
        sort(A + 1, A + cnt + 1, order);
        A[0].x = A[1].x + 2333;
        A[0].y = A[1].y + 2333; //unequal
        int self = 1, sameline = 0, max1 = 0;
        for (int j = 1; j <= cnt; j++) {
            if (A[j].x != A[j - 1].x || A[j].y != A[j - 1].y)
                sameline = 0;
            if (A[j].x == 0 && A[j].y == 0)
                ++self;
            else
                ++sameline;
            max1 = max(max1, sameline);
        }
        ans = max(ans, max1 + self);
    }
    cout << ans;
    return 0;
}
```

