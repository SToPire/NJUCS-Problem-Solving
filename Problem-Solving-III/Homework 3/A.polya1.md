#### 题目描述

一个项链中，$n$个珠子成一个环，每个珠子可以有$m$种颜色选择。 我们认为两个项链是“相同的”，当且仅当一个项链通过旋转后，每个珠子颜色都可以和另一个项链的对应珠子相同。 求有多少种“不同的”可能的项链。要求答案对$10^9+7$取模后的结果。

#### 输入格式

一行两个正整数$n,m$。

#### 输出格式

一行一个正整数，表示答案。

#### 样例

##### Input

```
2 2
```

##### Output

```
3
```

#### 数据范围与提示

对于50%的数据，$n,m\leq 10^6$。

对于100%的数据，$n,m \leq 10^9$。



利用Polya定理，设一个permutation有k个cycle，每个cycle中的颜色必须一致，不同cycle的颜色互不影响。故方案数为
$$
\frac{\sum_{i=0}^{|F|}m^{k_i}}{|F|}
$$
对于旋转还有$k_i=gcd(m,i)$，其中$1\le i\le n$为转动幅度

可以用欧拉函数优化，避免对每个数单独求一次与$m$的最大公约数。

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

ll quickpow(ll x, ll y)
{
    ll ans = 1;
    while (y) {
        if (y & 1)
            ans = (ans * x) % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}

ll Euler(ll n)
{
    ll ret = n;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ret = ret / i * (i - 1);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1)
        ret = ret / n * (n - 1);
    return ret;
}

int main(void)
{
    int n, m;
    ll res = 0;
    cin >> n >> m;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res = (res + quickpow(m, i) * Euler(n / i)) % MOD;
            if (n != i * i) {
                res = (res + quickpow(m, n / i) * Euler(i)) % MOD;
            }
        }
    }
    res = res * quickpow(n, MOD - 2) % MOD; //逆元
    cout << res;
    return 0;
}

```

