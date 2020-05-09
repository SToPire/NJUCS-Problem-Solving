#### 题目描述

给定一个$n$个正整数的数组，给定一个数$k$，问有多少对数组中的数$a_i, a_j$满足$1 \le i < j \le n$，使得$a_i \cdot a_j = x^k$

#### 输入格式

第一行输入两个数$n,k$

第二行输入$n$个数，代表数组中的数

#### 输出格式

输出一个数，表示有多少个这样的数对满足条件

#### 样例

**样例输入**

```
6 3
1 3 9 8 24 1
```

**样例输出**

```
5
```

#### 数据范围与提示

对100%的数据，$2 \le n \le 10^5, 2 \le k \le 100, 1 \le a_i \le 10^5$





对于每个$a_i=p_1^{q_1}p_2^{q_2}\cdots p_m^{q_m}$，找到一个$a_j = p_1^{nk-q_1}p_2^{nk-q_2}\cdots p_m^{nk-q_m}$即可。可以把每个数$a_i$Hash到$a_i^{'}= p_1^{q_1 \% k}p_2^{q_2\% k}\cdots p_m^{q_m\% k}$，再寻找互补的$a_j$的方案数即可。注意应该先找互补方案，再递增当前$a_i$的方案数，因为可能出现自己和自己互补的情况。

```c++
#include <bits/stdc++.h>
using namespace std;
int answers[100005];
int factors[20], times[20];
int main(void)
{
    int n, k;
    scanf("%d %d", &n, &k);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        int limit = sqrt(x);
        int fcnt = 0;
        memset(times, 0, sizeof(times));
        for (int j = 2; j <= limit; j++) {
            if (x % j == 0) {
                factors[++fcnt] = j;
                while (x % j == 0) {
                    ++times[fcnt];
                    x /= j;
                }
                times[fcnt] %= k;
            }
        }
        if (x != 1) // x is a prime
            factors[++fcnt] = x, times[fcnt] = 1;
        int tmp = 1;
        for (int j = 1; j <= fcnt; j++) {
            //若某个质因子次数为k的倍数，该因子不需要在互补数中出现
            tmp *= (int)pow(factors[j], (k - times[j]) % k); 
            if (tmp > 100000 || tmp < 0) // out of range
                goto ctnue;
        }
        ans += answers[tmp];
        tmp = 1;
        for (int j = 1; j <= fcnt; j++)
            tmp *= (int)pow(factors[j], times[j]);
        ++answers[tmp];
    ctnue:;
    }
    cout << ans;
    return 0;
}
```

