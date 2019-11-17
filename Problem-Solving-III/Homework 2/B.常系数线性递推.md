#### 题目描述

我们定义常系数线性递推数列$a_n = x_0 + \sum_{i = 1}^k x_ia_{n-i}, n \geq k$

给定$a_0, \cdots, a_{k-1}$以及$x_0, \cdots, x_k，$请求出$a_p$对$10^9 + 7$取模之后的结果

#### 输入格式

第一行两个数$k, p$

第二行$k + 1$个数$x_0, \cdots, x_k$

第三行$k$个数$a_0, \cdots, a_{k-1}$

输出一个数，表示答案

#### 样例

##### Input

```
2 6
0 1 1
0 1
```

##### Output

```
8
```

#### 数据范围与提示

$1 \leq k \leq 60, 10^9 \leq p \leq 2 * 10^9$

$0 \leq x_i, a_i \leq 500$



构造转移矩阵
$$
A=
\left\{
 \begin{matrix}
   x_1 & x_2 & \cdots & x_{k-1}& x_k & x_0\\
   1 & 0 & \cdots & 0 & 0 & 0 \\
   0 & 1 & \cdots & 0 & 0 & 0 \\
   \vdots & \vdots & \ddots & \vdots \\
   0 & 0 & \cdots & 1 & 0 & 0 \\    0 & 0 & \cdots & 0 & 0 & 1 \\
  \end{matrix} 
\right\}
$$
令
$$
X_0=
\left\{
 \begin{matrix}
   a_{k-1}\\
   a_{k-2}\\
   \vdots \\
   a_0 \\
   1
  \end{matrix} 
\right\}

X_1=
\left\{
 \begin{matrix}
   a_{k}\\
   a_{k-1}\\
   \vdots \\
   a_1\\
   1
  \end{matrix} 
\right\}

X_{p-k+1}=
\left\{
 \begin{matrix}
   a_{p}\\
   a_{p-1}\\
   \vdots \\
   a_{p-k+1}\\
   1
  \end{matrix} 
\right\}
$$
则有$AX_i=X_{i+1}$，因此要计算$a_p$我们只要计算$A^{p-k+1}$并与$X_0$相乘即可，可用快速幂加速运算。

```c++
#include<iostream>
using namespace std;
#define maxk 65
#define maxp 2000000005
#define MOD 1000000007
#define ull unsigned long long
inline int read()
{
	int x = 0, k = 1;
	char c = getchar();
	while (c <'0' || c>'9') { if (c == '-')k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + c - '0'; c = getchar(); }
	return x * k;
}
struct matrix{
    ull a[maxk][maxk];
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
        for (int i = 0; i < maxk;i++)
            for (int j = 0; j < maxk;j++)
                a[i][j] %= MOD;
        return *this;
    }
};
matrix operator*(const matrix& l,const matrix& r)
{
    matrix result;
    for (int i = 0; i < maxk;i++){
        for (int j = 0; j < maxk;j++){
            for (int k = 0; k < maxk;k++){
                result.a[i][j] += (l.a[i][k] * r.a[k][j]) % MOD;
                result.a[i][j] %= MOD;
            }
        }
    }
    return result;
}
matrix bitpower(matrix M,int n)
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
int k, p;
int A[maxk];
int main(void)
{
    k = read(), p = read();
    matrix M;
    M.a[1][k + 1] = read();
    for (int i = 1; i <= k;i++)
        M.a[1][i] = read();
    for (int i = k; i >= 1;i--)
        A[i] = read();
    A[k + 1] = 1;
    for (int i = 1; i <= k - 1;i++)
        M.a[i + 1][i] = 1;
    M.a[k + 1][k + 1] = 1;
    matrix powM=bitpower(M, p - k + 1);
    ull res = 0;
    for (int i = 1; i <= k + 1;i++){
        res += (powM.a[1][i] * A[i]) % MOD;
        res %= MOD;
    }
    cout << res;
    system("pause");
    return 0;
}

```

