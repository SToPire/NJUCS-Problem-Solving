/*
题目描述
读入 n≤1e6,再读入n个小于等于1e6的数字, 要求输出这些数字里面出现次数最多的两个数. 保证这两个数的出现次数分别>Ceiling(n/3)
从小到大输出结果, 中间用空格分割.
请留意一下本题的内存限制和以前的题不一样(1MiB).
样例输入
12
1 1 1 1 1 2 2 2 2 2 3 3
样例输出
2 3
*/
/*
关键在于最多的两个数都超过1/3的总数这一条件，这就使得这两个数以外的数不会多于这两个数中任意一个的个数，使以下的做法可行。
维护最多的两个数的个数。如果新读入的数与它们都不一样，两者的个数都-1，如果有任何一个数的个数被减到0，用新都入的数取代他。
正是因为最多的两个数都超过总数的1/3，他们都可以凭借一己之力上位，保证了此法的正确性。
*/
#include<iostream>
#include<algorithm>
using namespace std;
int main(void)
{
	int n; scanf("%d",&n); 
	pair<int, int> a{ 1e7,1 }, b{ 1e7,0 };
	scanf("%d",&a.first);
	int temp;
	for (int i = 2; i <= n; i++) {
		scanf("%d",&temp);
		if (temp == a.first) a.second++;
		else if (temp == b.first) b.second++;
		else if (0 == a.second) {
			a = { temp,1 };continue;
		}
		else if (0 == b.second) {
			b = { temp,1 };continue;
		}
		else {
			a.second--; b.second--;
		}
	}
	cout << min(a.first, b.first) << ' ' << max(a.first, b.first);
	system("pause");
}