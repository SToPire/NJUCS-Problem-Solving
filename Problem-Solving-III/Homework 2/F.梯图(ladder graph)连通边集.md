#### 题目描述

在最新推出的爆款游戏《Acesrc的奇妙冒险》中，你需要协助我们机智帅气的主人公Acesrc解决下面的问题:

一个梯图(ladder graph)$L(n)$是一个由$2N$个顶点以及$3N-2$条边组成的平面图。它和如下$2\times N$的格点图是同构的。

![http://roundgod.com/resources/wcy-2.png](http://roundgod.com/resources/wcy-2.png)

你希望删掉$L(n)$中一些边的集合(可能为空)，并保证剩下的图仍然是联通的。计算你有多少种合法的删除的方案。请输出答案对$10^9+7$取模后的结果。

#### 输入格式

输入仅包含一行，一个正整数$N$。

#### 输出格式

输出仅包含一行，合法的删除的方案数对$10^9+7$取模后的结果。

#### 样例

##### 样例输入1

```plain
2
```

##### 样例输出1

```plain
5
```

##### 样例输入2

```plain
1024
```

##### 样例输出2

```plain
399356307
```

#### 数据范围与提示

对于$50\%$的数据，有$1\leq N\leq 10^7$。

对于$100\%$的数据，有$1\leq N\leq 10^{18}$。





令$A_n$表示由$2N$个点组成的梯图的删除方案数，令$B_n$表示$2N$个点组成的梯图的删除方案数，但是满足限制条件：边$(N,2N)$不能被删去。

对于$A_n$，如果删去$(N,2N)$，$(N-1,N)$和$(2N-1,2N)$都不能删，其余边的删除方案数即$A_{n-1}$。如果不删去$(N,2N)$，删除方案数即$B_n$。

对于$B_n$，$(N-1,N)$和$(2N-1,2N)$可以删去一条($C_2^1$)，剩余部分的删除方案数是$A_{n-1}$。如果$(N-1,N)$和$(2N-1,2N)$都不删去，$N-1,N,2N-1,2N$已经连通，边$(N-1,2N-1)$可有可无($C_2^1$)，剩余部分的删除方案数是$B_{n-1}$。

因此有：
$$
A_n=A_{n-1}+B_n \\
B_n=2A_{n-1}+2B_{n-1}
$$
消去$B_n$得：
$$
A_n=5A_{n-1}-2A_{n-2}
$$

初始值是$A_1=1,A_2=5$，使用常系数齐次线性递推求出$A_n$。



注意负数取模要加模数再取模。

```c++
#include<iostream>
using namespace std;
#define maxk 4
#define MOD 1000000007
#define ll  long long
#define ull unsigned long long

inline ll read()
{
	ll x = 0, k = 1;
	char c = getchar();
	while (c <'0' || c>'9') { if (c == '-')k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + c - '0'; c = getchar(); }
	return x * k;
}
struct matrix{
    ll a[maxk][maxk];
    matrix(){
        for (int i = 0; i < maxk;i++)
            for (int j = 0; j < maxk;j++)
                a[i][j] = 0;
    }
    matrix(int n):matrix(){
        for (int i = 0; i < maxk;i++)
            a[i][i] = n;
    }
    matrix operator%(int n){
        for (int i = 0; i < maxk;i++){
            for (int j = 0; j < maxk;j++){
                a[i][j] += MOD;
                a[i][j] %= MOD;
            }
        }
        return *this;
    }
};
matrix operator*( matrix& l, matrix& r)
{
    matrix result;
    for (int i = 0; i < maxk;i++){
        for (int j = 0; j < maxk;j++){
            for (int k = 0; k < maxk;k++){
                result.a[i][j] += (l.a[i][k] * r.a[k][j]) % MOD;
            }
            result.a[i][j] += MOD;
            result.a[i][j] %= MOD;
        }
    }
    return result;
}
matrix bitpower(matrix M,ull n)
{
    matrix res = matrix(1);
    matrix base = M;
    while(n){
        if(n&1){
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        n >>= 1;
    }
    return res;
}
matrix M;
int k;
ull p;
int A[maxk];
int main(void)
{
    k = 2, p = read();
    matrix M; 
    M.a[1][k + 1] = 0;
    M.a[1][1] = 5;
    M.a[1][2] = -2;
    A[2] = 1;
    A[1] = 5;
    A[k + 1] = 1;
    for (int i = 1; i <= k - 1;i++)
        M.a[i + 1][i] = 1;
    M.a[k + 1][k + 1] = 1;
    matrix powM = bitpower(M, p - k) % MOD;
    ll res=0;
    for (int i = 1; i <= k + 1;i++){
        res += (powM.a[1][i] * A[i]) % MOD;
        res += MOD;
        res %= MOD;
    }
    if(p!=1)
        cout << res;
    else
        cout << 1;
    system("pause");
    return 0;
}

```

