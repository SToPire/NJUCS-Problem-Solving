/*
	F(n)=(F(n-1)+W1+1)%n
	�Ƚ��е�һ�δ��죬W1���߳���W1+1���µ���㡣��ʱ�ٴ���(n-1)�ξ͵õ�nʱ����̭����
*/
#include<iostream>
using namespace std;
int main(void)
{
	int n; cin >> n;
	int *arr = new int[n - 1];
	for (int i = 0; i < n-1; i++) {
		cin >> arr[i];
	}
	long long res = 0;
	for (int i = 0; i <= n - 2; i++) {
		res = (res + arr[i] + 1) % (i + 2);
	}
	cout << res;
	system("pause");
}