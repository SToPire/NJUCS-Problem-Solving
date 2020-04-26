#### 题目描述

给定一个长为$N$的严格递增数列($M_i < M_{i+1}$)，数列中第$i$个元素大小为$M_i$，你需要向数列中加入至多$K$个整数，使得加入后这些数数列仍满足$M_i < M_{i+1}$且$M_{i+1} - M_{i}$的最大值最小，问这个值是多少。

#### 输入格式

第一行为两个整数$N, K$，第二行$N$个数，代表该数列每个元素的值$M_i$。

#### 输出格式

输出一个数，为题目所求的值。

#### 样例

**样例输入1**

```
3 1
100 200 230
```

**样例输出1**

```
50
```

**样例输入2**

```
5 2
10 13 15 16 17
```

**样例输出2**

```
2
```

**样例输入3**

```
5 6
9 10 20 26 30
```

**样例输出3**

```
3
```

**样例输入4**

```
8 3
1 2 3 4 5 6 7 10
```

**样例输出4**

```
1
```

#### 数据范围与提示

对100%的数据，$1 \le K \le 10^5, 2 \le N \le 10^5, 1 \le M_i \le 10^9$





二分确定满足条件的最小值。注意不能用堆来维护每个区间，每次把最长的区间切成两半再放回去。一个反例是将长为9的区间切3次，二分切会得到4,3,2，而最优解是3,3,3.

```c++
#include <bits/stdc++.h>
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
int N, K;
int a[100005];

bool enough(int n)
{
    int sum = 0;
    for (int i = 1; i < N;i++){
        int t1 = a[i + 1] - a[i];
        sum += (t1 / n) - 1 + (t1 % n == 0 ? 0 : 1);
    }
    return sum <= K;
}
int main(void)
{
    N = read(), K = read();
    for(int i=1;i<=N;i++)
        a[i] = read();
    int l = 0, r = INT_MAX;
    while(r-l>=2){
        int tmp = (l + r) / 2;
        if(enough(tmp))
            r = tmp;
        else
            l = tmp;
    }
    cout << r;
    return 0;
}
```

