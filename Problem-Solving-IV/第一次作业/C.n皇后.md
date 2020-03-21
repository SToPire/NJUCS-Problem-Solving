#### 题目描述

国际象棋中的皇后棋子可以向上、下、左、右、左上、右上、左下、右下八个方向走任意步，给定$n \times n$的棋盘和$n$个皇后棋子，将这些棋子**全部**摆放在棋盘上，问有多少种摆放方法，在横纵坐标为$(x, y)$的格子里有棋子的情况下，使得任意棋子一步之内不能到达其他棋子的位置（不能互相攻击）。

![img](data:image/png;base64,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)

#### 输入格式

输入一行空格分隔的三个数$n, x, y$，分别代表棋盘大小（棋子个数）、必须有棋子的位置的坐标，可以视为$x$表示行（即1-8表示图中的1-8），$y$表示列（即1-8表示图中的a-h）。

#### 输出格式

输出一行一个整数，表示可行的方案数，两个方案不同当且仅当存在一个位置在一个方案中有棋子，在另一个方案中没有棋子。

#### 样例

**样例1**

输入

```
7 1 1
```

输出

```
4
```

**样例2**

输入

```
1 1 1
```

输出

```
1
```

#### 数据范围与提示

对于50%的数据，$1 \le n \le 8$。

对于100%的数据，$1 \le n \le 14, 1 \le x, y \le n$。



将行作为回溯法的深度指标，使用A,B,C三个数组分别记录列和两条对角线上的可行与否。

```c++
#include <bits/stdc++.h>
using namespace std;
#define maxn 14

int n, x, y;
int A[maxn + 1], B[2 * maxn + 1], C[2 * maxn + 1];
int cnt;

void search(int depth)
{
    if (depth > n) {
        ++cnt;
        return;
    } else if (depth == x) {
        search(depth + 1);
    } else {
        for (int i = 1; i <= n; i++) {
            if (!A[i] && !B[depth + i] && !C[(depth - i) + maxn]) {
                A[i] = B[depth + i] = C[(depth - i) + maxn] = 1;
                search(depth + 1);
                A[i] = B[depth + i] = C[(depth - i) + maxn] = 0;
            }
        }
    }
}

int main(void)
{
    scanf("%d %d %d", &n, &x, &y);
    A[y] = B[x + y] = C[(x - y) + maxn] = 1;
    search(1);
    printf("%d", cnt);
    return 0;
}
```

