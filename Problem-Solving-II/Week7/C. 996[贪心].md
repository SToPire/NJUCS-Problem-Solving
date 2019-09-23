#### 题目描述

给定$n$项工作的开始时间和完成时间$( S_1, E_1 ), ( S_2, E_2 ), \cdots, ( S_n, E_n )$ 一个工作只能由一个人完成, 两个工作 $(S_i, E_i), (S_j, E_j)$如果由同一个员工来完成, 必须有$E_i \le S_j$。

现在问最少需要多少员工才能完成所有任务.

#### 输入格式

第一行一个整数$n$，$(1 \le n \le 10^5)$，表示工作的数目。

接下来$n$行, 第$i+1$行有俩整数$S_i, E_i$,$0 \le S_i \le E_i \le 10^9$。

#### 输出格式

输出一个整数，表示最少需要的员工(进 `ICU` 的人数).

#### 样例输入

```plain
5
1 10
2 7
6 9
3 4
7 10
```

#### 样例输出

```plain
3
```

按照时间先后，对所有开始或结束的时间点排序。如果时间相同，把结束排在开始的前面。

从前往后遍历，每遇到一个结束时间count-1，每遇到一个开始时间count+1.这样一来，count就是某一时刻需要同时工作的员工数目，count达到过的最大值即为答案。

```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct task{
	int time;
	int tag;
	bool operator <(const task& r) {
		if (this->time == r.time) return this->tag < r.tag;
		else return this->time < r.time;
	}
};
int main(void)
{
	int n;
	cin >> n;
	vector<task> vp;
	int t1, t2;
	for (int i = 1; i <= n; i++) {
		cin >> t1 >> t2;
		vp.push_back({ t1,1 });
		vp.push_back({ t2,-1 });
	}
	sort(vp.begin(), vp.end());
	int count = 0, max = 0;
	for (auto e : vp) {
		count += e.tag;
		max = std::max(max, count);
	}
	cout << max;
	system("pause");
}
```

