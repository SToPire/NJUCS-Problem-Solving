#### 题目描述

小明的房间是对称的，可以看做是一个$N$行$M$列($M$和$N$中至少有一个是偶数)的格子，扫地机器人开始处于$(X,Y)$的格子中，机器人每次只能先打扫完当前所在的格子，然后才能朝上下左右某一个方向移动到下一个格子中。怎么样才能使得机器人不管初始位置在哪里，都能找到一条路径，可以在不重复经过任何一个格子的情况下将房间所有的格子都打扫一遍呢？

#### 输入格式

一行四个整数，$N,M,X,Y$。 $N,M$分别代表要扫地的区域的长和宽，$X,Y$代表扫地机器人的格子的位置，其中$0 \le X < N, 0 \le Y < M$。

#### 输出格式

输出$N \times M$行，每一行两个整数坐标$x_i,y_i$，代表第$i$步时的位置，以空格隔开。 其中$0 \le x_i < N, 0 \le y_i < M$. 第一行即为初始位置$X,Y$。

#### 数据范围与提示

$2 \le N,M \le 500$，且$N,M$中至少有一个是偶数。



大矩形总可以被划分成3个小矩形，以S形绕完3个矩形即可。分割线是过(X,Y)平行于偶数长度边的直线及其垂线。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M, X, Y;
bool SWAP;
void Print(int i, int j)
{
    if (SWAP)
        printf("%d %d\n", j, i);
    else
        printf("%d %d\n", i, j);
}
int main()
{
    cin >> N >> M >> X >> Y;
    if (M % 2 == 1) {
        SWAP = true;
        swap(M, N);
        swap(X, Y);
    }
    if (X == N - 1) {
        int i = X, j = Y;
        for (; j >= 0; j--) {
            Print(i, j);
        }
        i--;
        j++;
        int dir = -1;
        for (; j < M; j++) {
            if (N == 2) {
                Print(i, j);
            } else {
                while (1) {
                    Print(i, j);
                    i += dir;
                    if (i == 0 || i == N - 2) {
                        Print(i, j);
                        if (j != M - 1)
                            dir = -dir;
                        else
                            ++i;
                        break;
                    }
                }
            }
        }
        j--;
        for (; j > Y; j--)
            Print(i, j);
    } else if (Y % 2 == 0) {
        int i = X, j = Y, dir = -1;
        for (; j < M; j++) {
            if (0 == X) {
                Print(i, j);
                if (j == M - 1) {
                    i++;
                    dir = 1;
                }
            } else {
                while (1) {
                    Print(i, j);
                    i += dir;
                    if (i == 0 || i == X) {
                        Print(i, j);
                        if (j != M - 1)
                            dir = -dir;
                        else
                            ++i;
                        break;
                    }
                }
            }
        }
        --j;
        for (; j >= 0; j--) {
            if (X + 1 == N - 1) {
                Print(i, j);
                if (j == 0) {
                    i--;
                    dir = -1;
                }
            } else {
                while (1) {
                    Print(i, j);
                    i += dir;
                    if (i == X + 1 || i == N - 1) {
                        Print(i, j);
                        if (j != 0)
                            dir = -dir;
                        else
                            --i;
                        break;
                    }
                }
            }
        }
        ++j;
        for (; j < Y; j++) {
            if (0 == X) {
                Print(i, j);
            } else {
                while (1) {
                    Print(i, j);
                    i += dir;
                    if (i == 0 || i == X) {
                        Print(i, j);
                        dir = -dir;
                        break;
                    }
                }
            }
        }
    } else {
        int i = X, j = Y, dir = -1;
        for (; j >= 0; j--) {
            if (0 == X) {
                Print(i, j);
                if (j == 0) {
                    i++;
                    dir = 1;
                }
            } else {
                while (1) {
                    Print(i, j);
                    i += dir;
                    if (i == 0 || i == X) {
                        Print(i, j);
                        if (j != 0)
                            dir = -dir;
                        else
                            ++i;
                        break;
                    }
                }
            }
        }
        ++j;
        for (; j < M; j++) {
            if (X + 1 == N - 1) {
                Print(i, j);
                if (j == M - 1) {
                    i--;
                    dir = -1;
                }
            } else {
                while (1) {
                    Print(i, j);
                    i += dir;
                    if (i == X + 1 || i == N - 1) {
                        Print(i, j);
                        if (j != M - 1)
                            dir = -dir;
                        else
                            --i;
                        break;
                    }
                }
            }
        }
        --j;
        for (; j > Y; j--) {
            if (0 == X) {
                Print(i, j);
            } else {
                while (1) {
                    Print(i, j);
                    i += dir;
                    if (i == 0 || i == X) {
                        Print(i, j);
                        dir = -dir;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
```

