#### 题目描述

给定正整数$n$，求四元组$(a,b,c,d)$，满足方程$ab+cd=n$的正整数解个数。

#### 输入格式

第一行输入一个正整数$T$，表示测试组数。

接下来$T$行，每次输入一个正整数$n$。

#### 输出格式

共$T$行，第$i$行输出一个正整数，表示方程的正整数解个数。

#### 样例

##### 样例输入 1

```plain
3
1 
2
3
```

##### 样例输出 1

```plain
0
1
4
```

#### 数据范围与提示

输入保证$T\leq 10000,1 \leq n \leq 500000$。

对于50%的数据，保证$1\leq n \leq 5000$。



首先求出数列$a_{maxn}$，其中$a_i$表示$ab=i$解的组数，这可以简单地暴力完成，复杂度是调和级数$\theta(logn)$

对于$n$，我们要求的结果可以看做$a_{n-1}+a_1$,$a_{n-2}+a_2 \cdots$的结果之和，这就相当于$a_{maxn}$和自己做了一次多项式乘法后的系数，使用FFT加速此过程。



模板来源： https://blog.csdn.net/enjoy_pascal/article/details/81478582 

```c++
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
using namespace std;
#define ull unsigned long long
#define cnum complex<double>
#define maxn 500000
#define maxlen 1048576 //必须是2的幂次，且应超过n的两倍 
#define pi 3.14159265358979323846
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
int T, n;
int rev[maxlen];
vector<cnum> preproc(maxlen,cnum(0,0));
int res[maxlen];
void fft(vector<cnum>& a, int n, int inv)
{
    int bit = 0;
    while ((1 << bit) < n)
        bit++;
    for (int i = 0; i <= n - 1; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(a[i], a[rev[i]]); //不加这条if会交换两次（就是没交换）
    }
    for (int mid = 1; mid < n; mid *= 2) //mid是准备合并序列的长度的二分之一
    {
        cnum temp(cos(pi / mid), inv * sin(pi / mid)); //单位根，pi的系数2已经约掉了
        for (int i = 0; i < n; i += mid * 2) //mid*2是准备合并序列的长度，i是合并到了哪一位
        {
            cnum omega(1, 0);
            for (int j = 0; j < mid; j++, omega *= temp) //只扫左半部分，得到右半部分的答案
            {
                cnum x = a[i + j], y = omega * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y; //这个就是蝴蝶变换什么的
            }
        }
    }
}
int main(void)
{
    for (int a = 1; a <= maxn; ++a) {
        for (int b = 1;; ++b) {
            int c = a * b;
            if (c > maxn)
                break;
            preproc[c] = preproc[c] + cnum(1, 0);
        }
    }

    fft(preproc, maxlen, 1); //1代表DFT
    for (int i = 0; i < maxlen; i++)
        preproc[i] *= preproc[i];
    fft(preproc, maxlen, -1);
    for (int i = 0; i < maxlen; i++) //-1代表逆DFT，注意需要对每项除以n
        res[i] = (int)(preproc[i].real() / maxlen + 0.5); //注意除以n后再四舍五入
    T = read();
    while (T--) {
        n = read();
        cout << res[n] << endl;
    }
    system("pause");
    return 0;
}

```