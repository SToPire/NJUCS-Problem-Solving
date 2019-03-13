#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<bitset>
#include<map>
using namespace std;
int nvariable;
struct implicant {
	bitset<8> num; //�̺���Ķ����Ʊ�ʾ
	bitset<8> mask; //����б�ܴ������
	bool choose; //�Ƿ������̺���
	set<int> si;//���̺������������������

	implicant() = default;
	implicant(int n) :num(n), mask(0), choose(true) { si.insert(n); }
	implicant(bitset<8> a, bitset<8> b, bool c, set<int> s) :num(a), mask(b), choose(c) { si.insert(s.begin(), s.end()); }

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
	os << "  set:";
	for (auto i : a.si) os << i << ' ';
	os << "  ��Ӧ��:";
	for (int k = 0, j = nvariable - 1; j != -1; --j, ++k) {
		if (a.mask[j] == 1) continue;
		if (a.num[j] == 1) os << static_cast<char>('A' + k);
		if (a.num[j] == 0)os << static_cast<char>('A' + k) << '\'';
	}
	return os;
}
bool findSubset(set<int>& l, set<int>& r) //�ж�l�Ƿ�Ϊr�����Ӽ�
{
	int count = 0;
	for (auto a : l) {
		if (r.find(a) != r.end()) ++count;
	}
	return count == l.size() && l.size()<r.size();
}
bool equalSet(set<int>& a, set<int>& b)  //�ж����������Ƿ����
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
set<int>& setMinus(set<int>& a, set<int>& b) //���㼯��a������b,����a������
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
	if (s.empty()) return;                 //����������ǵ���������Ϊ�գ��ݹ������������
	map<int, int> mp;
	for (auto a : v)
		for (auto n : a.si)
			++mp[n];      //���ĳ��ֻ������һ�����̺����У������̺���Ϊʵ���̺���
	set<int> selected;
	for (auto n : s)
		if (mp[n] == 1) {
			for (auto &a : v) {
				if (a.si.find(n) != a.si.end()) {
					a.choose = true;          //ʵ���̺��ѡ��
					selected.insert(a.si.begin(), a.si.end());
				}
			}
		}
	for (auto &a : v) {
		if (a.choose) {
			res.push_back(a);      //��ʵ���̺���ѡ��res
			continue;
		}
		setMinus(a.si, selected);   //��ÿ�����̺������������м�ȥ�ѱ�ʵ���̺���ǵ���
	}
	vector<implicant> v2;
	for (auto a : v) {
		if (a.choose) continue;
		bool flag = true;
		for (auto b : v) {
			if (b.choose) continue;
			if (findSubset(a.si, b.si)) flag = false; //�������һ�����̺������������������һ�����̺��������������(�ѿ۳���ʵ���̺���ǵĲ���)
		}											  //����һ���̺�����ܱ�ѡΪ��������޳�
		for (auto c : v2) {
			if (equalSet(a.si, c.si)) flag = false;   //������������̺��������������(�۳���ʵ���̺���ǵĲ���)��ͬ������ȡ��һ
		}
		if (flag) v2.push_back(a);
	}
	setMinus(s, selected);                            //�ݹ�ؽ�����һ����
	QuineMcCluskey(v2, s);
}
int main(void)
{
	cout << "�������߼�������������:";
	cin >> nvariable;
	int n, m, temp;
	cout << "��������С�����:";
	cin >> n;
	set<int> minT, dcT;
	vector<list<implicant>> vec(33);   //vec[i]�Ƕ���������i��1���̺�ʽ���ɵ�list
	cout << "��������С����:";
	for (int i = 1; i <= n; ++i) {
		cin >> temp;
		minT.insert(temp);    //min��ֻ������С��
		vec[bitset<9>(temp).count()].push_back(implicant(temp));
	}
	cout << "�������޹������:";
	cin >> m;
	if (m) cout << "�������޹�����:";
	for (int i = 1; i <= m; ++i) {
		cin >> temp;
		dcT.insert(temp);	  //dcT��ֻ�����޹���
		vec[bitset<9>(temp).count()].push_back(implicant(temp));
	}
	for (int i = 0; i <= 7; ++i) {
		for (auto &a : vec[i]) {
			if (vec[i + 1].empty()) break;   //����ķ�Χ�������ݵ�list�����һ�����⣬��Ϊÿһ��Ҫ����һ�����Ƚ�
			for (auto &b : vec[i + 1]) {
				if (a.mask == b.mask) {      //���'-'�ķֲ�һ��
					auto temp = (a.num | a.mask) ^ (b.num | b.mask); //�����̺�ʽ(��б�ܲ���)���
					if (temp.count() == 1) {	//��������ֻ��һ��1��˵�������̺�ʽֻ��һλ��ͬ
						a.choose = b.choose = false;
						set<int> temps(a.si.begin(), a.si.end());
						temps.insert(b.si.begin(), b.si.end());
						vec[i + 1].push_back({ a.num | b.num,temp | a.mask,true,temps });
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
					setMinus(m.si, dcT);           //�����̺����������������м�ȥ�޹���
					v.push_back(m);
				}
			}
	}
	QuineMcCluskey(v, minT);
	for (auto a : res) cout << a << endl;
	system("pause");
}