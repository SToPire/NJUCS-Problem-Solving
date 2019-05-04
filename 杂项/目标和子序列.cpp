/*
输入target和n, target为目标数，n为数组长度。
输出数组中所有和为target的子序列
样例输入1：	10 6
			1 8 4 3 5 2
样例输出1：	1 4 3 2
			1 4 5
			8 2
			3 5 2

样例输入2：	5 3
			1 5 2
样例输出2：	5
*/
#include <iostream>
#include<vector>
#include <stack>
using namespace std;
stack<int> bag;
stack<int> tmp;
int sum = 0;
void method_bag(vector<int>& obj, int target, int num) {
		for (int i = num; i < obj.size(); i++) {
			bag.push(obj[i]);
			sum += obj[i];
			if (sum > target) {
				bag.pop();
				sum -= obj[i];
				continue;
			}
			else if (sum == target) {
				while (!bag.empty()) {
					tmp.push(bag.top());
					bag.pop();
				}
				while (tmp.size() != 1) {
					cout << tmp.top() << ' ';
					bag.push(tmp.top());
					tmp.pop();
				}
				cout << tmp.top() << endl;
				sum -= tmp.top();
				tmp.pop();
				continue;
			}
			method_bag(obj, target, i+1); //前i个数的取舍已确定，从i+1开始往后递归进行此过程
		}
		if (!bag.empty()) {
			sum -= bag.top();
			bag.pop();
		}
}
int main() {
	int max, n;
	cin >> max >> n;
	vector<int> obj(n);
	for (int i = 0; i < n; i++) {
		cin >> obj[i];
	}
	method_bag(obj, max, 0);
	system("pause");
}