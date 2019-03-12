#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<bitset>
#include<map>
using namespace std;
struct implicant {
	bitset<32> num; //�̺���Ķ����Ʊ�ʾ
	bitset<32> mask; //����б�ܴ������
	bool choose; //�Ƿ������̺���
	set<int> si;//���̺������������������

	implicant() = default;
	implicant(int n) :num(n), mask(0), choose(true) { si.insert(n); }
	implicant(bitset<32> a, bitset<32> b, bool c, set<int> s) :num(a), mask(b), choose(c) { si.insert(s.begin(), s.end()); }

	bool operator==(const implicant& rhs) 
	{
		if (num == rhs.num && mask == rhs.mask) return true;
		else return false;
	}
};
vector<implicant> res; //�洢�����
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
	os << "     set:";
	for (auto i : a.si) os << i << ' ';
	return os;
}
bool findSubset(set<int>& l, set<int>& r) //�ж�l�Ƿ�Ϊr�����Ӽ�
{
	int count = 0;
	for (auto a : l) {
		if (r.find(a) != r.end()) ++count;
	}
	return count==l.size() && l.size()<r.size();
}
template<typename T>
set<T>& setMinus(set<T>& a, set<T>& b) //���㼯��a������b,����a������
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
		if (a.choose) continue;
		setMinus(a.si, selected);
	}
	vector<implicant> v2;
	for (auto a : v) {
		if (a.choose) {
			res.push_back(a);
			continue;
		}
		bool flag = true;
		for (auto b : v) {
			if (b.choose) continue;
			if (findSubset(a.si, b.si)) flag = false;
		}
		if (flag) v2.push_back(a);
	}
	setMinus(s, selected);
	QuineMcCluskey(v2,s);
}
int main(void)
{
	int n,temp;
	cin >> n;
	set<int> input;        
	vector<list<implicant>> vec(33);   //vec[i]�Ƕ���������i��1���̺�ʽ���ɵ�list
	for (int i = 1; i <= n; ++i) {
		cin >> temp;
		input.insert(temp);
		vec[bitset<33>(temp).count()].push_back(implicant(temp));
	}

	for (int i = 0; i <= 31; ++i) {
		for (auto &a : vec[i]) {
			if (vec[i + 1].empty()) break;   //����ķ�Χ�������ݵ�list�����һ�����⣬��Ϊÿһ��Ҫ����һ�����Ƚ�
			for (auto &b : vec[i + 1]) {
				if (a.mask == b.mask) {      //���'-'�ķֲ�һ��
					auto temp = (a.num | a.mask) ^ (b.num | b.mask); //�����̺�ʽ(��б�ܲ���)���
					if (temp.count()==1) {	//��������ֻ��һ��1��˵�������̺�ʽֻ��һλ��ͬ
						a.choose = b.choose = false;
						set<int> temps(a.si.begin(), a.si.end());
						temps.insert(b.si.begin(), b.si.end());
						vec[i + 1].push_back({ a.num | b.num,temp | a.mask,true,temps});
					}
				}
			}
		}	
	}
	vector<implicant> v;  //����õ����̺���ȥ��
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
