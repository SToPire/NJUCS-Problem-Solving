#### 题目描述

在最新推出的爆款游戏《Acesrc的奇妙冒险》中，你需要协助我们机智帅气的主人公Acesrc,解决下面的问题:

在一个二维平面上，有NN*N*个红色的点和NN*N*个蓝色的点。其中第ii*i*个红色的点的坐标是$(a_i,b_i)$,第$i$个蓝色的点的坐标是$(c_i,d_i)$。

Acesrc每次可以选择平面上一个红色的点和一个蓝色的点，如果这两个点满足红色的点的$x$坐标小于蓝色的点的$x$坐标，且红色的点的$y$坐标小于蓝色的点的$y$坐标. 那么Acesrc就可以同时将这两个点从平面上移除，并发动一次秘技·波纹疾走。

现在Acesrc想要知道，对于给定的一共$2N$个点和它们各自的坐标，他最多可以发动几次秘技·波纹疾走?

#### 输入格式

第$1$行包含一个正整数$N$，表示红色的点和蓝色的点各自的数量。

接下来$N$行，每行包含两个非负整数$a_i,b_i$,表示第$i$个红色的点的坐标。

再接下来$N$行，每行包含两个非负整数$c_i,d_i$，表示第$i$个蓝色的点的坐标。

#### 输出格式

输出一行，包含一个整数，表示Acesrc最多能够发动秘技·波纹疾走的次数。

#### 样例

##### 样例输入1

```plain
3
2 0
3 1
1 3
4 2
0 4
5 5
```

##### 样例输出1

```plain
2
```

##### 样例输入2

```plain
5
0 0
7 3
2 2
4 8
1 6
8 5
6 9
5 4
9 1
3 7
```

##### 样例输出2

```plain
5
```

#### 数据范围与提示

对于$100\%$的数据，有$1\leq N\leq 100, 0\leq a_i,b_i,c_i,d_i\leq 2N$, 且保证$a_1,a_2,…,a_N,c_1,c_2,…,c_N$互不相同，$b_1,b_2,…,b_N,d_1,d_2,…,d_N$互不相同





使用匈牙利算法计算二部图的最大匹配。`find()`函数接收一个部$U$中的点$n$为参数，它优先匹配部$W$中下标小的点。一个点$i$可以被匹配的必要条件是有边相连，并且没有在这轮寻找中被访问过。`visit`数组表示部$W$中的点不能在这一轮`find()`中被改变归属。部$U$中下标大的点试图在下标小的点能找到新的匹配的情况下（通过改变`visited[i]`并递归使用`find()`来尝试），抢走它们的原有匹配。

总体来说，下标大的点容易满足第一志愿，但是可能失配；下标小的点满足的志愿优先级低，但是不易失配。这里志愿高指匹配到的部$W$中点的下标尽可能小。

注意每一轮`find()`都要重新置零`visit`数组。

```c
#include<iostream>
using namespace std;
#define maxn 105
inline int read()
{
	int x = 0, k = 1;
	char c = getchar();
	while (c <'0' || c>'9') { if (c == '-')k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + c - '0'; c = getchar(); }
	return x * k;
}
struct Node{
    int x, y;
} tmp1[maxn];
bool edge[maxn][maxn];
bool visit[maxn]; // 蓝点在某个find过程中被访问
int match[maxn]; // 蓝点匹配到的红点下标
int N;
bool find(int n)
{
    for (int i = 1; i <= N;i++){
        if(edge[n][i] && !visit[i]){
            visit[i] = true; //其他点不能在这一轮里抢走点i
            if(match[i]==0 || find(match[i])){
                match[i] = n;
                return true;
            }
        }
    }
    return false;
}
int main(void)
{
    N = read();
    for (int i = 1; i <= N;i++){
        tmp1[i].x = read();
        tmp1[i].y = read();
    }
    for (int i = 1; i <= N;i++){
        Node tmp2;
        tmp2.x = read();
        tmp2.y = read();
        for (int j = 1; j <= N;j++){
            if(tmp2.x>tmp1[j].x && tmp2.y>tmp1[j].y){
                edge[j][i] = true;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= N;i++){
        for (int j = 0; j < maxn;j++)
            visit[j] = false;
        if(find(i))
            ++ans;
    }
    cout << ans;
    system("pause");
    return 0;
}

```















