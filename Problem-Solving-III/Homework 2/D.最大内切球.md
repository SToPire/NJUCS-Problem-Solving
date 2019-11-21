#### 题目描述

在三维空间中，线性方程$ax+by+cz\leq d$构成一个“半空间”。

现在给出$n$个这样的线性方程，第ii*i*个线性方程用$(a_i,b_i,c_i,d_i)$表示.

求在这$n$个线性方程与限制$\{x\geq 0,y\geq 0, z\geq 0\}$构成的”半空间交“中，内切球的最大半径是多少。

若这个“半空间交"为空（即上述线性方程组无解），则输出4位小数0.0000。

如果这个球的半径可以为无穷大，则输出"Infinity"，否则输出一个4位小数，表示最大内切球的半径。

#### 输入格式

第一行一个正整数$T$，表示测试组数。

每组测试中，第一行输入一个正整数$n$，表示线性方程的个数，接下来$n$行，每行4个整数$a,b,c,d$，表示线性方程$ax+by+cz\leq d$。

保证对每一组线性方程，$a,b,c$不同时为0。

#### 输出格式

共$T$行，每行输出一个保留4位小数的答案，或者“Infinity”。

#### 样例

##### 样例输入 1

```plain
5
3
1 0 0 1
0 1 0 1
0 0 1 1
1
1 1 1 1
2
-1 -1 -1 -2
1 2 3 7
2
1 0 0 1
0 0 1 1
1
1 -1 0 0
```

##### 样例输出 1

```plain
0.5000
0.2113
0.5901
0.5000
Infinity
```

#### 数据范围与提示

保证$1\leq T \leq 150, 1\leq n \leq 100, -100\leq a,b,c,d \leq 100, \sum n \leq 2500$。

保证对于所有答案不为”Infinity“的答案，答案都$\leq 10^9$。





因为$10^9$是球半径的上界，我们可以二分寻找最大半径。

一个半径是合法的，当且仅当存在一个点到所有平面的距离都大于等于半径。

对于平面$ax+by+cz+d \ge 0$，点到平面的距离是$\frac{ax+by+cz+d}{\sqrt{a^2+b^2+c^2}}$，因此对于每个平面会多出一个附加约束条件，即

$ax+by+cz+d-r\sqrt{a^2+b^2+c^2} \ge 0$

对于每次二分查找只需要在$2m+3$个约束条件上寻求解的存在性即可。（板子自带3个约束，因此是$2*(m+3)-3=2m+3）$

```c++
// m个约束，n个变量
// 第i个约束，sum(a[i][j]*x[j])+a[i][0]>=0
// solve函数返回约束是否有解
// 若有解，则使得目标函数 sum(a[0][j]*x[j]) 最大化
// 默认约束：每个变量>=0
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define REP(i, n) FOR(i, 1, n)
#define REP_0N(i, n) FOR(i, 0, n)
using namespace std;
typedef long double ld;
typedef unsigned long long ull;
typedef long long ll;
#define maxn 505
#define N 505

inline ll read()
{
    ll x = 0, k = 1;
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

ld a[N][N];
ld x[N];
int n, m, id[N], tp[N], nn;
const ld eps = 1e-9;
const ld inf = 1e12;
int T;
void pivot(int r, int c)
{
    swap(id[r + n], id[c]);
    ld t = -a[r][c];
    a[r][c] = -1;
    REP_0N(i, n)
    a[r][i] /= t;
    REP_0N(i, m)
    if (a[i][c] && r != i) {
        t = a[i][c];
        a[i][c] = 0;
        REP_0N(j, n)
        a[i][j] += t * a[r][j];
    }
}
bool solve()
{
    ld t;
    REP(i, n)
    id[i] = i;
    while (true) {
        int i = 0, j = 0;
        ld w = -eps;
        REP(k, m)
        if (a[k][0] < w) w = a[i = k][0];
        if (!i)
            break;
        REP(k, n)
        if (a[i][k] > eps)
        {
            j = k;
            break;
        }
        if (!j)
            return false;
        pivot(i, j);
    }
    while (true) {
        int i = 0, j = 0;
        ld w = eps;
        REP(k, n)
        if (a[0][k] > w) w = a[0][j = k];
        if (!j)
            break;
        w = inf;
        REP(k, m)
        if (a[k][j] < -eps && (t = -a[k][0] / a[k][j]) < w) w = t,
                                                            i = k;
        if (!i)
            return true;
        pivot(i, j);
    }
    FOR(i, n + 1, n + m)
    tp[id[i]] = i - n;
    REP(i, n)
    x[i] = tp[i] ? a[tp[i]][0] : 0;
    return true;
}
ld ori[N][N]; //原有的m个约束
int main(void)
{
    T = read();
    while(T--){
        m = read();
        n = 3;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                a[i][j] = ori[i][j] = -read();
            }
            a[i][0] = ori[i][0] = read();
        }
        if (!solve()) {
            printf("0.0000\n");
        } else {
            ld l = 0.0, r = 1e9+1;
            while (r - l >= eps) {
                for (int i = 1; i <= m;i++)
                    for (int j = 0;j<=n;j++)
                        a[i][j] = ori[i][j];
                ld mid = (l + r) / 2;
                for (int i = 1; i <= m;i++){
                    ld tmp = sqrt(a[i][1] * a[i][1] + a[i][2] * a[i][2] + a[i][3] * a[i][3]);
                    for (int j = 1; j <= n;j++)
                        a[m + i][j] = a[i][j];
                    a[m + i][0] = a[i][0] - mid * tmp;
                }
                
                //x,y,z>=0带来的附加约束
                for (int i = 1; i <= 3;i++){
                    a[2 * m + i][0] = -mid;
                    for (int j = 1; j <= 3;j++)
                        a[2 * m + i][j] = (j == i) ? 1 : 0;
                }
                m = 2 * m + 3; //共2m+3个约束
                if(solve())
                    l = mid;
                else
                    r = mid;
                m = (m - 3) / 2;
            }
            if(l>1e9)
                printf("Infinity\n");
            else
                printf("%.4Lf\n",l);
        }
    }
    system("pause");
    return 0;
}
```

