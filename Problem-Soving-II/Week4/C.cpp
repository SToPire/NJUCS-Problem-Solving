/*
题目描述
	给定一个数列a1,a2,...,an,对每个二元组(l,r),1<=l<=r<=n,按以下方法定义一个偏序关系.
	记S(l,r)=Σ(i从l到r)ai
	对于(l1,r1),(l2,r2)
		a.若S(l1,r1)<S(l2,r2),则(l1,r1)<(l2,r2)
		b.若S(l1,r1)=S(l2,r2),且l1>l2,则(l1,r1)<(l2,r2)
		c.若S(l1,r1)=S(l2,r2),且l1=l2,且r1>r2,则(l1,r1)<(l2,r2)
	把每个二元组按以上定义从大到小排序,询问其中第k大的二元组(从1开始数，第1大的就是最大的)
	n∈[5,1e5],k∈[1,10],ai∈[-1e5,1e5]
	
输入格式
	第一行读入n,k
	第二行读入n个整数表示ai

样例输入
	5 10
	0 1 0 1 0
	
样例输出
	3 5
	
解法：如果知道了r==i的前k大的二元对，以及r<=i的前k大的二元对，就能求出r==i+1的前k大的二元对，以及r<=i+1的前k大的二元对
	  方法是
			1.通过对r==i的前k大的二元对进行sum+=vi[i+1],r++,再加上二元对((i+1,i+1),v[i+1]),这k+1个元素排序取前k个，便得到r==i+1的前k大的二元对
			2.通过对r==i+1的前k大的二元对，以及r<=i的前k大的二元对，这2k个元素排序取前k个，便得到r<=i+1的前k大的二元对
	  循环这一过程即可
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct p {
	int l, r;
	int sum;
};
bool cmp(const p& a, const p& b)
{
	if (a.sum != b.sum) return a.sum > b.sum;
	else if (a.l != b.l)return a.l < b.l;
	else return a.r < b.r;
}
int main()
{
	int n, k; cin >> n >> k;
	vector<int> vi(n);
	for (int i = 0; i < n; i++) {
		cin >> vi[i];
	}
	vector<p> end_with_i;  //r==i的前k大的二元对
	vector<p> end_nomore_i;//r<=i的前k大的二元对
	int sum = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = i ; j < 5; j++) {
			sum += vi[j];
			end_nomore_i.push_back({ i,j,sum });
		}
		sum = 0;
	}
	sort(end_nomore_i.begin(), end_nomore_i.end(), cmp);
	for (auto it = end_nomore_i.begin() + k; it != end_nomore_i.end();) {
		it = end_nomore_i.erase(it);
	}
	sum = 0;
	for (int i = 4; i >= 0; i--) {
		sum += vi[i];
		end_with_i.push_back({ i,4,sum });
	}
	sort(end_with_i.begin(), end_with_i.end(), cmp);
	if (k < 5) {
		for (auto it = end_with_i.begin() + k; it != end_with_i.end();) {
			it = end_with_i.erase(it);
		}
	}
	for (int i = 5; i < n; i++) {
		for (auto &e : end_with_i) {
			e.sum += vi[i];
			e.r = i;
			end_nomore_i.push_back(e);
		}
		end_with_i.push_back({ i,i,vi[i] });
		end_nomore_i.push_back({ i,i,vi[i] });
		sort(end_nomore_i.begin(), end_nomore_i.end(), cmp);
		for (auto it = end_nomore_i.begin() + k; it != end_nomore_i.end();) {
			it = end_nomore_i.erase(it);
		}
		sort(end_with_i.begin(), end_with_i.end(), cmp);
		if (k < end_with_i.size()) {
			for (auto it = end_with_i.begin() + k; it != end_with_i.end();) {
				it = end_with_i.erase(it);
			}
		}
	}
	cout << end_nomore_i[k - 1].l + 1 << ' ' << end_nomore_i[k - 1].r + 1;
	system("pause");
}