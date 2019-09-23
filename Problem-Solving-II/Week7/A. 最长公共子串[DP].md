题目描述：给定两个只包含字符0和1的字符串$A, B$，对于$A$的每个前缀求其与$B$的最长公共子串的长度。

输入格式：两行，第一行为$A$，第二行为$B$。

输出格式：$|A|$个整数，第$i$个数表示$A$长度为$i$的前缀与$B$的最长公共子串的长度。

样例输入：$01101$

​					$11110$

样例输出：$1 1 2 3 3$

```
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int main(void)
{
	string A, B;
	cin >> A >> B;
	int a = A.size(), b = B.size();
	vector<vector<int>> c(a+1, vector<int>(b+1, 0));
	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			if (A[i - 1] == B[j - 1]) c[i][j] = c[i - 1][j - 1] + 1;
			else c[i][j] = 0;
		}
	}
	vector<int> max(a+1, 0);
	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			if (c[i][j] > max[i])
				max[i] = c[i][j];
		}
	}
	for (int i = 1; i <= a; i++) {
		if (max[i] < max[i - 1]) max[i] = max[i - 1];
		cout << max[i] << ' ';
	}
	system("pause");
}
```

**注意：公共子串和公共子序列是不同的概念。**

令$c[i][j]$表示**以$A[i]$和$B[j]$结尾**的最长公共子串的长度，显然当$A[i+1] \ne B[j+1]$时，$c[i+1][j+1]=c[i][j]+1$，否则$c[i+1][j+1]=0$。

要求对于给定的$i$，以$A[i]$结尾的最长公共子串，只要遍历寻找所有$j$，找出最大值。

要求对于给定的i，$A$长度为$i$的前缀的最长公共子串，只要遍历max数组，输出前$i$个数中的最大值。