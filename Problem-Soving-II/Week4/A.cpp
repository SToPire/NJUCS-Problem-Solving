/*
	求解Σ(i从0到min(x,y))(C(x,i)*C(y,i)) mod 1e9+7
	输入格式：第一行读入一个t，表示有t组数据
	接下来t行，每行两个整数x，y表示一组询问
	1<=x,y,t<=1000000
*/
#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
//逆元求组合数
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
		cout << C(a + b, min(a, b))<<endl;//直接使用组合数的实际意义，摸球模型
	}
	system("pause");
}