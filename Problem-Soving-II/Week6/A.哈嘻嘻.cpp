/*
题目描述：给定以下哈希函数
	unsigned int f(std::string s, unsigned int base, unsigned int mod) {
    unsigned int rt = 0;
    for (auto i = 0; i < s.size(); i++) 
        rt = ((unsigned long long)rt * base + s[i] - 'a') % mod;
    return rt;
	
	读入base,mod,k,试构造一个字符串s使得f(s,base,mod)=k.保证0<=k<mod,0<=base<=200,0<=mod<=100000,mod是质数并与base互质
	要求输出的字符串只含有小写字母，长度不超过500000.
	若有多个合法解只需要输出一个.
	
样例输入：10 3 2
样例输出：ac
}
*/
/*
	本题要求将pm+k（p为自然数）写成base进制形式，而每一位上的数必须在[0,25]之间。遍历所有p直到找到为止即可。
*/
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
vector<long long> deci2base(long long k, long long base)
{
	vector<long long> tmp;
	while (k) {
		tmp.push_back(k%base);
		k /= base;
	}
	return tmp;
}
int main() {
	long long base, mod, k;
	cin >> base >> mod >> k;
	if (base == 0) {
		cout << char('a' + (k % 26));
		return 0;
	}
	for (long long i = 0;; i++) {
		long long sum = i * mod + k;
		vector<long long> tmp = deci2base(sum, base);
		bool flag = true;
		for (auto a : tmp) if (a > 25) flag = false;
		if (flag) {
			for (auto rit = tmp.rbegin(); rit != tmp.rend(); rit++) {
				cout << (char)(*rit + 'a');
			}
			break;
		}
	}
	system("pause");
}