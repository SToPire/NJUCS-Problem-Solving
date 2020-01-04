#### 题目描述

现在有一个这样的加密算法，将原文数字$w$加密为密文$c$：

Step 1：在$[10^5,10^9]$随机的选择一个正整数$x$。

Step 2：找到最大质数$p$，满足$p\leq x$。

Step 3：找到最小质数$q$，满足$q > x$。

Step 4：令$n=p\cdot q$。

Step 5：计算 $w^{2^{30}+3} \mod n$，得到$c$。

现在给你密文$c$，以及上述算法过程中的$n$，你需要还原原文$w$的值。保证$0\leq w < n$。

#### 输入格式

第一行一个正整数$T$，表示测试组数。

接下来$T$行，每行两个正整数$n,c$，保证$10^{10} \leq n \leq 10^{18}, 1\leq c <n$。

#### 输出格式

共$T$行，第$i$行一个正整数，表示第$i$组测试的答案。

#### 样例

#### Input

```
3
181857896263 167005790444
218128229323 156323229335
352308724847 218566715941
```

#### Output

```
175267324024
209603568635
282077284785
```

#### 数据范围与提示

对于50%的数据， $1\leq T \leq 10$。

对于100%的数据，$1 \leq T \leq 10^5$。



其实类似RSA算法，只要找到p和q然后求$2^{30}+3$模$\varphi(n)=(p-1)(q-1)$意义下的逆元e，计算$c^{e}$即可。

因为p和q是离$\sqrt n$最近的两个质数，找到它们并不困难。

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
    ll x = 0, k = 1;
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

//ax+by=gcd(a,b)
void exgcd(ll a, ll b, ll& x, ll& y, ll& c)
{
    if (!b) {
        y = 0;
        x = 1;
        c = a;
        return;
    }
    exgcd(b, a % b, y, x, c);
    y -= a / b * x;
}

ll quickpow(ll x, ll y, ll MOD)
{
    __int128_t ans = 1;
    while (y) {
        if (y & 1)
            ans = (ans * x) % MOD;
        x = (__int128_t)x * x % MOD;
        y >>= 1;
    }
    return (ll)ans;
}

int main(void)
{
    int T = read();
    ll n, c;
    while(T--){
        n = read();
        c = read();
        ll p = sqrt(n), q = n / p;
        while(p*q!=n){
            --p;
            q = n / p;
        }
        ll euler = (p - 1) * (q - 1);
        ll x, y, t;
        exgcd(1073741827, euler, x, y, t);
        x += euler;
        x %= euler;
        cout << quickpow(c, x, n) << endl;
    }
    return 0;
}
```

