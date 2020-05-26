#include <iostream>
#include <vector>
using namespace std;

vector<int> v;

void quick(int st, int end) {
	if (st >= ed) return;
	int pivot = st, a = pivot + 1, b = end;

	while (a <= j) {
		while (a <= end && v[a] < v[pivot]) a++;
		while (b > st && v[b] >= v[pivot]) b--;
		if (a > b) swap(v[b], v[pivot]);
		else swap(v[a], v[b]);
	}
	quick(st, b - 1);
	quick(a + 1, end);
}

int main() {
	int n;
	cin >> n;
	v.resize(n);
	list.resize(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	quick(0, n - 1);
	for (int i = 0; i < n; i++) cout << v[i] << " ";
}