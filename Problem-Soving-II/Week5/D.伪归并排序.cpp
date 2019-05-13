/*
题目描述：	一个伪归并排序如图，给出以下列随机函数生成的1~n的全排列a，输出调用mergesort(a,1,n,h)后，从左往右能看到的楼房个数。
			楼房按照下列模型建立：从左到右第i栋楼房的高度是bi
			随机函数：	mt19937_64 gen(seed);
						for (int i = 1; i <= n; i++) a[i] = i;
						for (int i = 1; i <= n; i++) {
							int u = gen() % (n - i + 1) + i;
							swap(a[u], a[i])
						}				
输入：随机数种子seed,n,h
输出：看到的楼房个数
样例1：	5972396 5 1
		2
样例2：	5972396 5 2
		3
样例3：	5972396 5 3
		4
样例4：	5972396 5 4
		5
		
注：随机种子5972396,n=5会生成a{4,2,1,3,5}
*/
/*
	只要考虑归并排序终止的那一层，在那一层被遮挡住的，归并之后仍然被遮挡。在那一层没被挡住的，归并之后也不被遮挡。
*/
#include<iostream>
#include<vector>
#include<random>
using namespace std;
int fun(vector<int>& a, int l, int r, int h)
{
	if (l == r) return 0;
	else if (h == 1) {
		int nowmax = a[l];
		int count = 0;
		for (int i = l + 1; i <= r; i++) {
			if (nowmax < a[i]) nowmax = a[i];
			else count++;
		}
		return count;
	}
	else {
		int m = (l + r) / 2;
		return fun(a, l, m, h - 1) + fun(a, m + 1, r, h - 1);
	}
}
int main() {
	unsigned long long seed;
	int n, h; cin >> seed >> n >> h;
	vector<int> a(n+1);
	mt19937_64 gen(seed);
	for (int i = 1; i <= n; i++) a[i] = i;
	for (int i = 1; i <= n; i++) {
		int u = gen() % (n - i + 1) + i;
		swap(a[u], a[i]);
	}
	cout<<n-fun(a, 1, n, h);
	system("pause");
}