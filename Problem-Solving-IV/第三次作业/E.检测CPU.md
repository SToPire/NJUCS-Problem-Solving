#### 题目描述

GPU常被用来进行矩阵运算，为了检测GPU运算的正确性，小明选择了两个$N \times N$的01矩阵$A$和$B$输入GPU中，而GPU会输出$A \times B$的结果。小明想要验证得到的结果是否正确，然而GPU马上就要发布了，小明希望尽快知道结果，假设题目给的GPU有50%的可能性会输出正确结果，有50%的可能性会存在若干个位置被一个$[0,N]$之间的均匀采样的随机值代替，请你设计一个算法，较快地验证该结果是否正确。

#### 输入格式

第一行输入一个数$T$，代表样例个数，接下来每一个样例第一行输入一个数$N$，接下来$N$行每行输入$N$个数代表矩阵$A$，接下来$N$行每行输入$N$个数代表矩阵$B$，接下来$N$行每行输入$N$个数代表GPU的输出矩阵$C$。

#### 输出格式

对每个样例，若$C = A \times B$，输出`true`，否则输出`false`。

#### 样例

**输入样例**

```
2
3
1 1 1
0 1 0
1 1 1
1 0 0
0 1 0
0 0 1
1 1 1
0 1 0
1 1 1
3
1 1 1
0 1 0
1 1 1
1 0 0
0 1 0
0 0 1
1 1 1
0 0 0
1 1 1
```

**样例输出**

```
true
false
```

#### 数据范围与提示

对100%的样例，$1 \le N \le 500, A_{ij}, B_{ij} \in \{ 0,1 \}, 0 \le C_{ij} \le N, 1 \le T \le 10$



直接做乘法是来不及的，方法是随机生成一个01向量d，计算并比较(A\*B\*d)和(C\*d)的值是否相同。这两个值不同，当且仅当(C-A\*B)\*d==0向量。因此C与A\*B中若有k位不同，误判概率就是$\frac1{2^k}$，重复若干次之后误判概率更低。

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
int a[505][505], b[505][505], c[505][505];
int r[505], t1[505], t2[505], t3[505];
int N;
bool chk()
{
    memset(t1, 0, sizeof(t1));
    memset(t2, 0, sizeof(t2));
    memset(t3, 0, sizeof(t3));

    for (int i = 1; i <= N; i++)
        r[i] = rand() % 2;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            t1[i] += b[i][j] * r[j];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            t2[i] += a[i][j] * t1[j];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            t3[i] += c[i][j] * r[j];
    for (int i = 1; i <= N; i++)
        if (t2[i] != t3[i])
            return false;
    return true;
}

void once()
{
    N = read();
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            a[i][j] = read();
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            b[i][j] = read();
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            c[i][j] = read();
    for (int i = 1; i <= 3; i++) {
        if (!chk()) {
            cout << "false\n";
            return;
        }
    }
    cout << "true\n";
}
int main(void)
{
    int T = read();
    while (T--)
        once();
    return 0;
}
```

