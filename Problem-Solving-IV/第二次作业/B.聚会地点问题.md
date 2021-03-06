#### 题目描述

一个规划的很完美的城市如图中的示例，城市中的街道构成完美的方格阵，假设每个相邻街口的距离恰好是1。一群朋友定期聚会的地点总是安排在某个街口，而且要求与每个人住处的距离（即该点与住处的曼哈顿距离）之和为最小。每次聚会参与的人可能变化。编写一个程序，对于每次确定的聚会参加人（输入为各人的住处坐标）选定合适的聚会地点。如果多于一个街口满足上述条件，则选择其中编号和为最小的那个。

#### 输入格式

第一行输入一个数$n$，代表聚会人的个数。

接下来$n$行输入空格分割的两个数$x, y$，代表每个人住处的坐标。

#### 输出格式

输出两个数$x, y$，代表聚会地点的坐标。

#### 样例

**样例输入1**

```
11
1 2
1 7
2 2
2 3
2 5
3 4
4 2
4 5
4 6
5 3
6 5
```

**样例输出1**

```
3 4
```

#### 数据范围与提示

对20%的数据，$1 \le x, y \le 10$

对100%的数据，$1 \le x, y \le 10^9, 1 \le n \le 10^5$



首先，由曼哈顿距离的定义，可以把横纵坐标分开考虑求最优。

考虑这样一个事实：对于一维数轴，假设已经找到了一个答案点，如果把它右移一格，它左边的点到新答案点的距离和+=左边点个数，右边同理。因此寻找最优的过程就是找到一个两边点数尽可能平均的点，即中位数。

```c++
#include<bits/stdc++.h>
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
int x[100005], y[100005];
int main(){
    int n = read();
    for (int i = 1; i <= n;i++)
        x[i] = read(), y[i] = read();
    sort(x + 1, x + n + 1);
    sort(y + 1, y + n + 1);
    if(n%2==0)
        cout << x[n / 2] << ' ' << y[n / 2] << endl;
    else
        cout << x[(n + 1) / 2] << ' ' << y[(n + 1) / 2] << endl;
    return 0;
}
```

