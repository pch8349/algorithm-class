#include <iostream>
#include <vector>
using namespace std;

vector<int> v;

void quick(int st, int end) {
	if (st >= end) return;
	int pivot = st, a = pivot + 1, b = end;

	while (a <= b) {
		while (a <= end && v[a] < v[pivot]) a++;
		while (b > st && v[b] >= v[pivot]) b--;
		if (a > b) swap(v[b], v[pivot]);
		else swap(v[a], v[b]);
	}
	quick(st, b - 1);
	quick(b + 1, end);
}

int main() {
	int n;
	cin >> n;
	v.resize(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	quick(0, n - 1);
	for (int i = 0; i < n; i++) cout << v[i] << " ";
}