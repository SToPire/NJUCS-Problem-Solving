#### 题目描述

将$k$根非常纤细（就是说可以忽略它们的直径）的长度不等的细木棒一根一根地依次抛在桌面上，判断哪些会在“顶上”的位置，即没有任何其它木棒压住它们。**规定若存在任何一个点同时存在于两个木棒上，那么后一根木棒就压住了前一根木棒**。

用一个四元组的序列表示木棒被抛下的过程，每个四元组含四个数值，分别表示该木棒落下后两个端点在桌面上的坐标（为了简单假设均为整数值），当然这也就确定了该木棒的长度。每个四元组在序列中的顺序就是该木棒抛下的顺序。写一个程序输出顶上木棒的个数。

#### 输入格式

第一行输入一个数$n$，代表木棒的个数。

接下来$n$行**按木棒落下的顺序**输入空格分割的四个数$x_1, y_1, x_2, y_2$，代表木棒两个端点的坐标$(x_1, y_1), (x_2, y_2)$。

#### 输出格式

输出一个数，代表没有被遮住的木棒的个数。

#### 样例

**样例输入1**

```
5
1 1 4 2
2 3 3 1
1 -2 8 4
3 3 6 -2
1 4 8 2
```

**样例输出1**

```
3
```

#### 数据范围与提示

对60%的数据，$-10^3 \le x_1, y_1, x_2, y_2 \le 10^3$

对100%的数据，$-10^9 \le x_1, y_1, x_2, y_2 \le 10^9, 1 \le n \le 10^3$

数据保证$x_1 = x_2, y_1 = y_2$不同时成立





可以用向量积判断两条线段是否相交。方法是看b线段两个端点是否在a线段同一侧，即以a线段一个端点为原点，看a线段往b线段两个端点与原点形成向量旋转的角度是否异号。

当然向量是针对直线而言的，即使两个端点异侧也不能说明线段相交，还要用横纵坐标的最大最小值加以判断。



```c++
#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
};
struct stick {
    point p1, p2;
} sticks[1005];

double crossProduct(int x1, int y1, int x2, int y2)
{
    return ((long long)x1 * y2) - ((long long)x2 * y1);
}

bool intersect(stick s1, stick s2)
{
    if (max(s1.p1.x, s1.p2.x) < min(s2.p1.x, s2.p2.x))
        return false;
    if (max(s1.p1.y, s1.p2.y) < min(s2.p1.y, s2.p2.y))
        return false;
    if (max(s2.p1.x, s2.p2.x) < min(s1.p1.x, s1.p2.x))
        return false;
    if (max(s2.p1.y, s2.p2.y) < min(s1.p1.y, s1.p2.y))
        return false;
    if (crossProduct(s2.p1.x - s1.p1.x, s2.p1.y - s1.p1.y, s1.p2.x - s1.p1.x, s1.p2.y - s1.p1.y) * crossProduct(s1.p2.x - s1.p1.x, s1.p2.y - s1.p1.y, s2.p2.x - s1.p1.x, s2.p2.y - s1.p1.y) < 0)
        return false;
    if (crossProduct(s1.p1.x - s2.p1.x, s1.p1.y - s2.p1.y, s2.p2.x - s2.p1.x, s2.p2.y - s2.p1.y) * crossProduct(s2.p2.x - s2.p1.x, s2.p2.y - s2.p1.y, s1.p2.x - s2.p1.x, s1.p2.y - s2.p1.y) < 0)
        return false;
    return true;
}
int boom[1001];
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    int ans = n;
    for (int i = 1; i <= n; i++) {
        cin >> sticks[i].p1.x
            >> sticks[i].p1.y
            >> sticks[i].p2.x
            >> sticks[i].p2.y;
    }
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++)
            if (intersect(sticks[i], sticks[j])) {
                ans--;
                break;
            }
    cout << ans;
    return 0;
}
```

