/*
题目描述：	给定一个集合S，初始为空，现在你要处理以下3种操作：
			+x:向集合中添加一个数x<=1e9,保证对于任何y∈S都有y<x
			-:删掉集合S中最小的数
			?:询问集合S中所有数的最大公约数
输入格式：	第一行是一个数n,表示询问的组数。接下来n行，每行包含一组询问，询问格式已在题目描述中给出。
			输入数据保证当出现第二种和第三种询问的时候集合SSS中至少包含一个数。
输出格式：	对于所有第三种询问,输出一个数表示答案。
样例输入
10
+ 8
+ 20
?
-
?
+ 30
+ 90
?
-
?
样例输出
4
20
10
30
*/
/*
	使用线段树完成。
*/
#include<iostream>
#include<vector>
using namespace std;
vector<int> vi;
vector<pair<int, int>> vp;
int GCD(int a, int b)
{
	if (a == -1 or b == -1) return -a * b;  //使用-1来填充线段树中空位，使其成为完美二叉树
	else if (b) while ((a %= b) && (b %= a));
	return a + b;
}
void init(vector<int>& segTree) //线段树的初始化
{
	if (segTree.size() == 1) { segTree[0] = vi[0]; return; }
	for (int i = (segTree.size() - 1) / 2, j = 0; j < vi.size(); i++, j++) { //先填充叶子结点，不足部分用-1补全
		segTree[i] = vi[j];
	}
	for (int i = (segTree.size() - 3) / 2; i >= 0; i--) {      //非叶子结点为两个孩子的GCD
		segTree[i] = GCD(segTree[2 * i + 1], segTree[2 * i + 2]);
	}
}
int query(vector<int>& segTree, int a, int b, int k, int l, int r) //[a,b)为所查找区间，[l,r)为当前结点对应区间，k为该区间对应结点的下标。均使用左闭右开表示法
{
	
	if (r <= a or b <= l) return -1;
	else if (l >= a and r <= b) return segTree[k];
	else {
		return GCD(query(segTree, a, b, 2 * k + 1, l, (l + r) / 2), query(segTree, a, b, 2 * k + 2, (l + r) / 2, r));
	}
}
int main() {
	int n; cin >> n;
	int left = 0, right = -1;
	char tc; int ti;
	for (int i = 1; i <= n; i++) {
		cin >> tc;
		switch (tc) {
		case '+':
			cin >> ti;
			vi.push_back(ti);
			right++;
			break;
		case '-':
			left++;
			break;
		case '?':
			vp.push_back({ left,right });
			break;
		}
	}
	int tmp = 1;
	while (tmp < vi.size()) tmp <<= 1;
	tmp <<= 1; tmp--; 
	vector<int> segTree(tmp, -1);     //tmp的目的是使其形成完美二叉树
	init(segTree);
	for (auto a : vp) {
		cout << query(segTree, a.first, a.second+1, 0, 0, (tmp+1)/2) << endl; //a.second+1,是为了配合左闭右开区间表示法
	}
	system("pause");
}