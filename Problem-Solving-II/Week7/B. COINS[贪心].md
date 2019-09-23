#### 题目描述

你在地上看见 $n$ 组硬币, 第$i$组有两枚硬币, 价值分别是$a_i,b_i$。

时间紧迫, 你需要在这总共$2n$ 枚硬币中捡起来$k$枚, 使得捡起来的硬币的价值和最大.

对于第$i$组, 你只有捡起价值为$a_i$的那枚硬币之后, 才能去捡价值为$b_i$的那枚.

请输出最大价值和.

#### 输入格式

第一行有两个整数$n,k$, 保证$1 \le n \le 2k \le 10^6$。

接下来有$n$行, 第$i+1$行有俩整数$a_i,b_i$, 表示该组硬币的价值. 保证$1 \le a_i,b_i \le 1000$。

#### 输出格式

输出一个整数, 表示答案.

#### 样例输入

```plain
4 3
1 5
1 3
3 1 
3 1
```

#### 样例输出

```plain
9
```



贪心方法：当 $k> 1$时，每次取两枚，或取同一组中的两枚，或取不同组中两枚。每次取的两枚应该是所有可行取法中价值最大的。当 $k=1$时，选择当前可以取的最大的硬币

​	注意：若某组中的两枚恰好与不同组中最大的两枚面值和相等，应该取不同组中的两枚，这样会带来更多选择余地。另外，当两组硬币面值和相等时，应该按第一个硬币大小排序，第一个硬币更小的排在前面。这样是为了$k=1$时能取到更大的硬币。

```
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
int read() {
	int ans = 0; char c = getchar();
	while (c<'0' || c>'9') c = getchar();
	while (c >= '0'&&c <= '9') ans = ans * 10 + c - 48, c = getchar();
	return ans;
}
struct group {
	int index;
	int top;
	int bottom;
	int sum;
};
struct cmp_top {
	bool operator()  (const group& l, const group& r) const
	{
		if (l.top != r.top) return l.top > r.top;
		else return l.index < r.index;
	}
};
struct cmp_sum {
	bool operator()(const group& l, const group& r) const
	{
		if (l.sum != r.sum) return l.sum > r.sum;
		else if (l.top != r.top) return l.top < r.top;
		else return l.index < r.index;
	}
};
int main(void)
{
	int n, k;
	n = read(); k = read();
	set<group, cmp_top> s1;
	set<group, cmp_sum> s2;
	int t1, t2;
	for (int i = 1; i <= n; i++) {
		t1 = read(); t2 = read();
		group tem{ i,t1,t2,t1 + t2 };
		s1.insert(tem);
		s2.insert(tem);
	}
	int ans = 0;
	if (n == 1) {
		if (k == 1) cout << s1.begin()->top;
		else cout << s1.begin()->sum;
			return 0;
	}
	while (k > 1) {
		if ((s1.begin()->top + (++s1.begin())->top) > s2.begin()->sum) {
			auto t1 = *s1.begin(); s1.erase(s1.begin()); 
			auto t2 = *s1.begin(); s1.erase(s1.begin()); 
			ans += (t1.top + t2.top);
			s2.erase(s2.find(t1)); s2.erase(s2.find(t2));
			t1.sum -= t1.top; t1.top = t1.bottom; t1.bottom = 0;
			t2.sum -= t2.top; t2.top = t2.bottom; t2.bottom = 0;
			if (t1.sum != 0) {
				s1.insert(t1); s2.insert(t1);
			}
			if (t2.sum != 0) {
				s1.insert(t2); s2.insert(t2);
			}
		}
		else {
			ans += s2.begin()->sum;
			s1.erase(s1.find(*s2.begin()));
			s2.erase(s2.begin());
		}
		k -= 2;
	}
	if (k == 1) {
		ans += s1.begin()->top;
	}
	cout << ans;
	system("pause");
}
```

