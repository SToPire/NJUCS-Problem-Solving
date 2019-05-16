#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct ele {
	unsigned long long min;
	unsigned long long max;
	unsigned long long OR;
	ele* left;
	ele* right;
	unsigned long long length;
	double ans;
};
struct order {
	long long value;
	int loc;
};
bool cmp(const order& a, const order& b) {
	if (a.value == b.value) return a.loc > b.loc;
	else return a.value > b.value;
}
ele* findleft(ele e) {
	ele* tmp = &e;
	while (tmp->left != tmp) tmp = tmp->left;
	return tmp;
}
ele* findright(ele e) {
	ele* tmp = &e;
	while (tmp->right != tmp) tmp = tmp->right;
	return tmp;
}
int main() {
	const int mod = 1000000007;
	int T; cin >> T;
	for (int index = 1; index <= T; index++) {
		int n; cin >> n;
		int p, q, x, y, z; cin >> p >> q >> x >> y >> z;
		vector<order> a(n + 1);
		a[1] = { p,1 }; a[2] = { q,2 };
		for (int j = 3; j <= n; j++) {
			a[j].value = ((x*a[j - 2].value + y * a[j - 1].value + z) % 1000000) + 1;
			a[j].loc = j;
		}
		sort(a.begin(), a.end(), cmp);
		a.erase(--a.end());
		vector<unsigned long long> d(n + 1);
		vector<unsigned long long> b(n + 1);
		vector<int> fuzhu(1000010);
		vector<int> left(n + 1);
		vector<int> right(n + 1);
		unsigned long long ans1 = 1, ans2 = 0, t1, t2;
		int i = n;
		for (auto e : a) {
			int ind = e.loc;
			b[i] = e.value;
			d[i] = e.value;
			if (fuzhu[ind - 1]) {
				left[i] = left[fuzhu[ind - 1]];
				b[i] = max(b[i], b[fuzhu[ind - 1]]);
				d[i] |= d[fuzhu[ind - 1]];
			}
			else left[i] = ind;
			if (fuzhu[ind + 1]) {
				right[i] = right[fuzhu[ind + 1]];
				b[i] = max(b[i], b[fuzhu[ind + 1]]);
				d[i] |= d[fuzhu[ind + 1]];
			}
			else right[i] = ind;
			fuzhu[left[i]] = i;
			fuzhu[right[i]] = i;
			t1 = (unsigned long long)b[i] * e.value - (unsigned long long)e.value * (unsigned long long)e.value;
			t2 = (unsigned long long)d[i] * (right[i] - left[i] + 1);
			if (((double)t1 / (double)ans1) > ((double)ans2 / (double)t2)) {
				ans1 = t1;
				ans2 = t2;
			}
			i--;
		}
		cout << ((ans1%mod)*(ans2%mod)) % mod << endl;
	}
	system("pause");
}