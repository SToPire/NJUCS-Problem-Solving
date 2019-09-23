#### 题目描述

给你一篇仅由汉字组成的文章中所有不同汉字出现的次数。

现在要求你对所有汉字进行编码，满足如下要求 :

- 相同汉字的编码必须相同
- 所有汉字的编码必须形如$\overline{a_0 a_1 a_2 \cdots a_n}$，其中$a_i$表示一个任意的字符
- 所有汉字的所有编码中出现的不同的字符总数不能超过$k$
- 任意汉字的编码不能是另一个不同的汉字的编码的前缀

请问，利用满足以上要求的编码将原文中的汉字进行替换后，原文最少的字符数是多少。

#### 输入格式

第一行两个数$n,k$，表示共有$n$个不同的汉字需要编码，编码所有的不同字符数不能超过$k$。

第二行$n$个数$a_1, \cdots, a_n$，表示$n$个不同的汉字分别在原文中出现了多少次。

#### 输出格式

输出一个正整数，表示原文编码所需的最少字符数。

#### 样例

##### 样例1

###### Input

```
3 2
1 2 3
```

###### Output

```
9
```

##### 样例2

###### Input

```
4 3
1 2 3 4
```

###### Output

```
13
```

#### 数据范围与提示

$1 \leq n \leq 200000$

$2\leq k \leq 9$

$1\leq a_i \leq 200000$

对于$80\%$的数据，满足$k=2$





k=2时就是赫夫曼编码，k>2时我们可以想见编码树是k叉树，而且只有最下面一层可能没有填满。否则我们就可以把这部分提到上面去得到一棵更优的编码树。所以在合并的过程中，除了第一次可能不是合并k个元素，其余每次都取k个元素合并，再把结果放回堆中。



为了解决这个问题我们可以换一种思路，只要在堆中加入一些0，就可以把编码树补完整，即每一个节点都形成k叉树，这样第一次也归为取出k个元素合并。怎么确定要加入的0的个数呢？我们注意到每次取出k个元素合并并放回一个后，堆中元素个数减少$k-1$。算法结束的时候，堆中应该剩余一个元素。因此我们要让填入0之后的堆中的元素个数 $mod (k-1)=1$。



```
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n, k; cin >> n >> k;
	vector<int> a(n);
	for (int i = 1; i <= n; i++) {
		cin >> a[i - 1];
	}
	multiset<unsigned long long> heap(a.begin(), a.end());
	if (k != 2) {
		int t = (n - 1) % (k - 1);
		for (int i = 1; i <= k - 1 - t; i++) heap.insert(0);
	}
	unsigned long long ans = 0;
	while (heap.size() > 1) {
		unsigned long long  r = 0;
		for (int i = 1; i <= k; i++) {
			unsigned long long tmp = *heap.begin(); heap.erase(heap.begin());
			ans += tmp; r += tmp;
		}
		heap.insert(r);
	}
	cout << ans;
	system("pause");
}
```

