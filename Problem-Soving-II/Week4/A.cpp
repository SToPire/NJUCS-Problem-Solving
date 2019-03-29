/*
	��⦲(i��0��min(x,y))(C(x,i)*C(y,i)) mod 1e9+7
	�����ʽ����һ�ж���һ��t����ʾ��t������
	������t�У�ÿ����������x��y��ʾһ��ѯ��
	1<=x,y,t<=1000000
*/
#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
//��Ԫ�������
class BinomialCoefficient {
public:	vector<int> factorial;
	vector<int> factorial_inverse;
	int n, mod;

public:
	BinomialCoefficient() {}
	BinomialCoefficient(int _n, int _mod) : n(_n), mod(_mod) {
		factorial = vector<int>(n + 1, 1);
		factorial_inverse = vector<int>(n + 1, 1);
		for (int i = 1; i <= n; i++)
			factorial[i] = (long long)factorial[i - 1] * i % mod;
		for (int i = 2; i <= n; i++)
			factorial_inverse[i] = mod - (long long)factorial_inverse[mod % i] * (mod / i) % mod;
		for (int i = 1; i <= n; i++) {
			factorial_inverse[i] = (long long)factorial_inverse[i - 1] * factorial_inverse[i] % mod;		
		}
	}

	int operator ()(const int n, const int m) const {
		return (long long)factorial[n] * factorial_inverse[m] % mod * factorial_inverse[n - m] % mod;
	}
} C(2000000, 1000000007);

int main(int argc, char **argv) {
	int t,a,b; cin >> t;
	for (int i = 1; i <= t; i++) {
		cin >> a >> b;
		cout << C(a + b, min(a, b))<<endl;//ֱ��ʹ���������ʵ�����壬����ģ��
	}
	system("pause");
}