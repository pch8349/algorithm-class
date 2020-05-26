#include<iostream>
#include<vector>
using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

int main() {
	int n, max, m;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = n - 1; i <= 0; i--) {
		max = 0;
		for (int j = 0; j < i; j++) {
			if (max < v[j]) {
				max = v[j];
				m = j;
			}
		}
		swap(v[n], v[m]);
	}
}