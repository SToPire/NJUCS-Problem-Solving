/*
	F(n)=(F(n-1)+W1+1)%n
	先进行第一次传旗，W1被踢出，W1+1是新的起点。此时再传旗(n-1)次就得到n时被淘汰的人
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