/*
��Ŀ����
���� n, �����(i��1~n)��(j��0~i) (C(i,j) % 2) 
�����ʽ
����1<=n<=10^7
��������
10
�������
36
*/
/*
�����Ƕ������µ���������Σ���ͼ�ҹ��ɡ�
fun(n)=fun(m)+2f(n-m)
mΪ������n��,����2�����ɴ��ݡ�
�ݹ��չ����ʽ��
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
