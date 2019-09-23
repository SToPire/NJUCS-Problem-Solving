#### 题目描述

给定一个字符串s*，你每次可以删除其中一个**回文子串**，删除完毕后两边的字符串会重新拼接成新的。

求最少的删除次数，使得字符串变为空串。

#### 输入格式

第一行包含一个整数*n*，表示字符串的长度。

第二行包含一个仅含小写字母的字符串*s*（*s*的长度为*n*），如题所述。

#### 输出格式

一个数，表示最少的删除次数。

#### 样例

##### Input

```
7
abbcdca
```

##### Output

```
2
```



区间dp，令*dp(i,j)*表示从i到j子串的最少次数。

则转移方程分两种情况考虑。

1. s[i]==s[j],此时dp(i,j)就等于dp(i-1,j+1)

2. dp(i,j)=$\min_{i \le k < j}(dp(i,j),dp(i,k)+dp(k+1,j))$。即便s[i]==s[j]，我们也要进行这一步，因为两边往里缩一个得到的结果可能还不如切两端来得小。



```
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int dp[305][305];

int main(void)
{
	const int INF = 1e9 + 7;
	int n; cin >> n;
	string s; cin >> s;
	for (int i = 0; i <= 304; i++) for (int j = 0; j <= 304; j++) dp[i][j] = INF;
	for (int i = 1; i <= n-1; i++) {
		dp[i][i] = 1; 
		dp[i + 1][i] = 1; //这是为了if(s[i-1]==s[j-1]) dp[i][i+1]=1能被包容在转移式中
	}
	dp[n][n] = 1;
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n + 1 - l; i++) {
			int j = l + i - 1;
			if (s[i-1] == s[j-1]) dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
			for (int k = i; k < j; k++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}
		}
	}
	cout << dp[1][n];
	system("pause");
}
```



