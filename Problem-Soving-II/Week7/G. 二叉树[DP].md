#### 题目描述

给定$n$个数$a_1, a_2, \cdots, a_n$，你需要构建一棵二叉树，并将这$n$个数放于叶子节点上。

不妨假设数$a_i$所在的叶子结点深度为$d_i$(根节点的深度为$0$)。

请给出$\max \limits_{1 \leq i \leq n} d_i \leq k$的情况下，$\sum \limits_{i = 1}^n a_i \times d_i$的最小值。

#### 输入格式

第一行两个正整数$n, k$。

第二行$n$个正整数，代表$a_1, a_2, \cdots, a_n$。

#### 输出格式

一个正整数，表示所求的最小值。

#### Input

```
4 2
1 2 3 4
```

#### Output

```
20
```

先对所有元素排序。令$dp[i][j][h]$表示第i到第j个元素，在高度h的限制下，$\sum \limits_{i = 1}^n a_i \times d_i$的最小值。我们有
$$
dp[i][j][h]= \min_{i \le iter<j}(dp[i][iter][h-1]+dp[iter+1][j][h-1]+w[i][j])
$$
其中$w[i][j]$为$a[i]$到$a[j]$之和。理解：两棵子树在某处合并，产生一个新的根节点。于是每个元素的高度都$+1$。

这个动态规划实际是在贪心基础上的，因此需要升序排序。每次合并最小元素时，要考虑高度限制。

```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int w[55][55];
int dp[55][55][55];
int main(void)
{
	const int INFTY = 1e9;
	for (int i = 0; i < 55; i++) {
		for (int j = 0; j < 55; j++) {
			for (int k = 0; k < 55; k++) dp[i][j][k] = INFTY;
		}
	}
	ios::sync_with_stdio(false);
	int n, k; cin >> n >> k;
	vector<int> a; int t;
	for (int i = 1; i <= n; i++) {
		cin >> t;
		a.push_back(t);
	}
	sort(a.begin(), a.end());
	for (int i = 1; i <= n; i++) {
		w[i][i] = a[i-1];
		for (int j = 0; j <= k; j++) dp[i][i][j] = 0;
	}
	for (int length = 2; length <= n; length++) {
		for (int i = 1; i <= n - length + 1; i++) {
			int j = i + length - 1;
			w[i][j] = w[i][j - 1] + w[j][j];
			for (int h = 1; h <= k; h++) {
				for (int iter = i ; iter < j; iter++) {
					dp[i][j][h] = min(dp[i][j][h], dp[i][iter][h - 1] + dp[iter + 1][j][h - 1] + w[i][j]);
				}				
			}
		}
	}
	cout << dp[1][n][k];
	system("pause");
}
```

注意初始状态：对于只有一个节点的树，无论高度限制是多少，代价都为0.数组中的其他位全部置为$\infty$。