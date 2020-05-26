#include<iostream>
#include<vector>
using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--) {
			if (v[j] < v[j - 1]) swap(v[j], v[j + 1]);
		}
	}
}