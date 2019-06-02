#### 题目描述

给定两个仅由小写字母组成的字符串$A$和$B$，求他们**最长公共子序列**的长度。

#### 输入格式

输入两行，第一行为长为$n$*的字符串*$A$，第二行为长为$m$的字符串$B$

#### 输出格式

输出一个数，代表两个字符串最长公共子序列的长度。

#### 样例

##### Input

```
aabbccddee
abcde
```

##### Output

```
5
```

#### 数据范围与提示

$1 \le n \le 10^6$

$1 \le m \le 10^3$



## 1.动态规划$(O(n \lg n))$

首先需要将LCS问题转变为LIS问题。方法是对B串中所有字符，找出其在A串中出现的位置。每个字符的位置都按降序排列，之后将B中字符替换为其位置序号，对结果数列求LIS。降序排列的目的是消除B中特定字母与A中多个位置上的同一字母匹配的可能。

LIS：令$dp[i]$为长度为i+1的递增子序列中末尾元素的最小值，初始状况$dp[i]$初始为$\infty$。对每个$a_j$，如果$i==0$或者$dp[i-1]<a_j$，$dp[i]=\min(dp[i],a_j)$，最终结果就是满足$dp[i] \ne \infty$的最大的$i+1$。这本身是$O(n^2)$的过程，然而可以进一步优化。注意到$dp$是单调递增的，也就是对于每个给定的$a_j$，$dp$中只有一个数需要被更新，也就是满足$dp[i-1] < a_j < dp[i]$的那个$dp[i]$。所以可以二分搜索找出这个位置进行更新，从而将复杂度降为$O( n\lg n)$。

```
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
using namespace std;
int main(void)
{
	string a, b;
	cin >> a >> b;

	map<char, vector<int>> mp;
	vector<int> vi;
	for (int i = a.size() - 1; i >= 0;i--) {
		mp[a[i]].push_back(i);
	}
	for (int i = 0; i <= b.size() - 1; i++) {
		for (auto e : mp[b[i]]) {
			vi.push_back(e);
		}
	}
	int n = vi.size();
	vector<int> dp(n, 1e9);
	for (int i = 0; i < n; i++) {
		*lower_bound(dp.begin(), dp.end(), vi[i]) = vi[i];
	}
	int i;
	for (i = n - 1; i >= 0 && dp[i] == 1e9; i--);
	cout << i + 1;

	system("pause");
}
```



## 2.滚动数组对空间的优化

在传统的$O(n^2)$算法中，不使用$n*n$的二维数组，而是开上下两排数组。这是因为动态规划只需要当前格子上、左和左上三个位置的值。

```
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
using namespace std;
int main(void)
{
	string a, b;
	cin >> a >> b;
	int szb = b.size();
	vector<int>odd(szb + 1, 0);
	vector<int>even(szb + 1, 0);
	for (int i = 1; i <= sza; ++i) {
		for (int j = 1; j <= szb; ++j) {
			if (i & 1) {
				if (a[i - 1] == b[j - 1]) odd[j] = even[j - 1] + 1;
				else if (odd[j - 1]<even[j]) odd[j] = even[j];
				else odd[j] = odd[j - 1];
			}
			else {
				if (a[i - 1] == b[j - 1]) even[j] = odd[j - 1] + 1;
				else if (even[j - 1]<odd[j]) even[j] = odd[j];
				else even[j] = even[j - 1];
			}
		}
	}
	(sza % 2 == 1) ? cout << odd[szb] << endl : cout << even[szb] << endl;

	system("pause");
}
```

甚至可以把上一排数组也优化掉，只保存两个临时值。

```
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int main(void)
{
	std::ios::sync_with_stdio(false);
	string a, b;
	cin >> a >> b;
	int sza = a.size(), szb = b.size();
	vector<int> dp(szb + 1, 0);
	int tmp1 = 0, tmp2 = 0;
	for (int i = 1; i <= sza; i++) {
		int j;
		for (j = 1; j < szb; j++) {
				if (a[i - 1] == b[j - 1]) dp[j] = tmp1 + 1;
				else dp[j] = max(dp[j - 1], tmp2);
				tmp1 = tmp2; tmp2 = dp[j + 1];
		}
		if (a[i - 1] == b[j - 1]) dp[j] = tmp1 + 1;
		else dp[j] = max(dp[j - 1], tmp2);
		tmp1 = 0; tmp2 = dp[1];
	}
	cout << dp[szb];
	system("pause");
}
```

## 3.$O(|S|n+m^2)$算法

此处$|S|$为字符集的大小，$n$和$m$分别为长字符串和短字符串的长度。

令$dp[i][j]$表示短字符串中，以第$i$个字符结尾的子串，在与长串有$j$位公共序列的前提下，第$i$个字符匹配到的（即与之相同的）第一个长串中字符的位置。

预处理得出两个串中，对于每个字符，下一个字符集中任意字符的位置。

通过枚举字符集中每个元素来动态规划，这样就只需要遍历一次长串，消除了原先的$O(mn)$因素。

```
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int main(void)
{
	string a, b;
	cin >> a >> b;
	int n = a.size(), m = b.size();
	vector<vector<int>> a_next(n+1, vector<int>(26, 0));
	vector<vector<int>> b_next(m+1, vector<int>(26, 0));
	vector<int> now(26, n+1);
	for (int i = n; i >= 0; i--) {
		for (int j = 0; j < 26; j++) {
			a_next[i][j] = now[j];
		}
		if(i)	now[a[i-1] - 'a'] = i;
	}
	for (auto &e : now) e = m+1;
	for (int i = m; i >= 0; i--) {
		for (int j = 0; j < 26; j++) {
			b_next[i][j] = now[j];
		}
		if(i)	now[b[i-1] - 'a'] = i;
	}
	int ans = 0;
	vector<vector<int>> dp(m+1, vector<int>(m+1, n+1));
	dp[0][0] = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j <= i; j++) {
			if (dp[i][j] == n+1) continue;
			for (int k = 0; k < 26; k++) {
				if (b_next[i][k] <= m) {
					dp[b_next[i][k]][j + 1] = min(dp[b_next[i][k]][j + 1], a_next[dp[i][j]][k]);
					if (a_next[dp[i][j]][k]<=n) ans = max(ans, j + 1);
				}
			}
		}
	}
	cout << ans;
	system("pause");
}
```