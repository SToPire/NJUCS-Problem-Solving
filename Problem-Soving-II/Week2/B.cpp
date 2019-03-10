/*
题目描述
读入 n, 输出Σ(i从1~n)Σ(j从0~i) (C(i,j) % 2) 
输入格式
读入1<=n<=10^7
样例输入
10
样例输出
36
*/
/*
本质是二进制下的杨辉三角形，画图找规律。
fun(n)=fun(m)+2f(n-m)
m为不大于n的,最大的2的若干次幂。
递归地展开上式。
*/
#include<iostream>
#include<bitset>
#include<cmath>
using namespace std;
int main() 
{
	int m;
	cin >> m;
	bitset<24> bs(++m);
	long long sum = -1;
	int times = 1;
	for (int i = 23; i >= 0; --i) {
		if (bs[i]) {
			sum += times * pow(3, i);
			times *= 2;
		}
	}
	cout << sum;
}
