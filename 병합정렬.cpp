#include<iostream>
#include<vector>
using namespace std;

vector<int> v;
vector<int> list;

void merge(int st, int mid, int end) {
	int a = st, b = mid + 1, c = st;
	while (a <= mid && b <= end) {
		if (v[a] <= v[b]) list[c++] = v[a++];
		else list[c++] = v[b++];
	}
	if (a > mid) {
		for (int i = b; i <= end; i++) list[c++] = v[i];
	}
	else {
		for (int i = a; i <= mid; i++) list[c++] = v[i];
	}
	for (int i = st; i <= end; i++) v[i] = list[i];
}

void merges(int st, int end) {
	if (st < end) {
		int mid = (st + end) / 2;
		merges(st, mid);
		merges(mid + 1, end);
		merge(st, mid, end);
	}
}

int main() {
	int n;
	cin >> n;
	v.resize(n);
	list.resize(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	merges(0, n - 1);
	for (int i = 0; i < n; i++) cout << list[i] << " ";
}