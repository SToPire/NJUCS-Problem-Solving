#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<bitset>
#include<map>
using namespace std;
int nvariable;
struct implicant {
	bitset<8> num; //蕴含项的二进制表示
	bitset<8> mask; //被用斜杠代替的数
	bool choose; //是否是质蕴涵项
	set<int> si;//该蕴含项所代表的整数集合

	implicant() = default;
	implicant(int n) :num(n), mask(0), choose(true) { si.insert(n); }
	implicant(bitset<8> a, bitset<8> b, bool c, set<int> s) :num(a), mask(b), choose(c) { si.insert(s.begin(), s.end()); }

	bool operator==(const implicant& rhs) 
	{
		if (num == rhs.num && mask == rhs.mask) return true;
		else return false;
	}
};
vector<implicant> res; //存储最后结果
ostream& operator<<(ostream& os, implicant a)
{
	auto i = a.num.size(); --i;
	while (i != -1) {
		if (a.mask[i] == 1)
			os << '-';
		else
			os << (int)a.num[i];
		--i;
	}
	os << "  set:";
	for (auto i : a.si) os << i << ' ';
	os << "  对应项:";
	for (int k=0,j=nvariable-1; j != -1; --j,++k) {
		if (a.mask[j] == 1) continue;
		if (a.num[j] == 1) os << static_cast<char>('A' + k);
		if (a.num[j] == 0)os << static_cast<char>('A' + k) << '\'';
	}
	return os;
}
bool findSubset(set<int>& l, set<int>& r) //判断l是否为r的真子集
{
	int count = 0;
	for (auto a : l) {
		if (r.find(a) != r.end()) ++count;
	}
	return count==l.size() && l.size()<r.size();
}
bool equalSet(set<int>& a, set<int>& b)
{
	bool flag = true;
	for (auto n : a) {
		if (b.find(n) == b.end()) flag = false;
	}
	for (auto n : b) {
		if (a.find(n) == a.end()) flag = false;
	}
	return flag;
}
template<typename T>
set<T>& setMinus(set<T>& a, set<T>& b) //计算集合a减集合b,返回a的引用
{
	for (auto it = a.begin(); it != a.end();) {
		if (b.find(*it) != b.end())
			it = a.erase(it);
		else
			++it;
	}
	return a;
}
void QuineMcCluskey(vector<implicant>& v, set<int> s)
{
	if (s.empty()) return;
	map<int, int> mp;
	for (auto a : v)
		for (auto n : a.si)
			++mp[n];
	set<int> selected;
	for (auto n : s)
		if (mp[n] == 1) {
			for (auto &a : v) {
				if (a.si.find(n) != a.si.end()) {
					a.choose = true;
					selected.insert(a.si.begin(), a.si.end());
				}
			}
		}
	for (auto &a : v) {
		if (a.choose) {
			res.push_back(a);
			continue;
		}
		setMinus(a.si, selected);
	}
	vector<implicant> v2;
	for (auto a : v) {
		if (a.choose) continue;
		bool flag = true;
		for (auto b : v) {
			if (b.choose) continue;
			if (findSubset(a.si, b.si)) flag = false;
		}
		for (auto c : v2) {
			if (equalSet(a.si,c.si)) flag = false;
		}
		if (flag) v2.push_back(a);
	}
	setMinus(s, selected);
	QuineMcCluskey(v2,s);
}
int main(void)
{
	cout << "请输入逻辑函数变量个数:";
	cin >> nvariable;
	int n,temp;
	cout << "请输入最小项个数:";
	cin >> n;
	set<int> input;        
	vector<list<implicant>> vec(33);   //vec[i]是二进制中有i个1的蕴涵式构成的list
	cout << "请输入最小项编号:";
	for (int i = 1; i <= n; ++i) {
		cin >> temp;
		input.insert(temp);
		vec[bitset<9>(temp).count()].push_back(implicant(temp));
	}

	for (int i = 0; i <= 7; ++i) {
		for (auto &a : vec[i]) {
			if (vec[i + 1].empty()) break;   //处理的范围是有数据的list，最后一个除外，因为每一组要跟下一组作比较
			for (auto &b : vec[i + 1]) {
				if (a.mask == b.mask) {      //如果'-'的分布一样
					auto temp = (a.num | a.mask) ^ (b.num | b.mask); //两个蕴涵式(除斜杠部分)异或
					if (temp.count()==1) {	//如果结果中只有一个1，说明两个蕴涵式只有一位不同
						a.choose = b.choose = false;
						set<int> temps(a.si.begin(), a.si.end());
						temps.insert(b.si.begin(), b.si.end());
						vec[i + 1].push_back({ a.num | b.num,temp | a.mask,true,temps});
					}
				}
			}
		}	
	}
	vector<implicant> v;  //将获得的质蕴涵项去重
	for (auto l : vec) {
		for (auto m : l)
			if (m.choose) {
				bool flag = true;
				for (auto a : v) {
					if (a == m) flag = false;
				}
				if (flag) {
					m.choose = false;
					v.push_back(m);
				}
			}
	}
	QuineMcCluskey(v, input);
	for (auto a : res) cout << a << endl;
	system("pause");
}