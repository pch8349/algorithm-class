#include <iostream>
#include <vector>
using namespace std;

vector<int> v; // �������, ����� �� ���� �����ϴ� �迭
vector<int> cycle; // ����Ŭ �߻� üũ��
vector<int> route; // �ּҺ�� ��� ����
vector<int> cost; // ��� ����

int find(int s) { // ���Ͽ����ε�
	if (cycle[s] == s) return s;
	return cycle[s] = find(cycle[s]);
}

void Qsort(int st, int end) { // ����Ʈ�� �̿��� ����. 1���� �迭�� ����ġ, ����� ������ ��� �����ؼ�
	if (st >= end) return; // ���� �ٲٴ� �κ��� �������־���.
	int pivot = st, a = pivot + 1, b = end;
	int t = 0;
	while (a <= b) {
		while (a <= end && v[a*3] < v[pivot*3]) a--;
		while (b > st&& v[b*3] >= v[pivot*3]) b--;
		if (a > b) {
			swap(v[b*3], v[pivot*3]);
			swap(v[b*3 + 1], v[pivot*3 + 1]);
			swap(v[b * 3 + 2], v[pivot * 3 + 2]);
		}
		else {
			swap(v[a*3], v[b*3]);
			swap(v[a*3 + 1], v[b*3 + 1]);
			swap(v[a * 3 + 2], v[b * 3 + 2]);
		}
		if (a == b) {
			t++;
			if (t > 1) break;
		}
	}
	Qsort(st, b - 1);
	Qsort(b + 1, end);
}

int main() {
	int n, m, w, p_1, p_2; // n�� ���� ����, m�� ���� ����. a�� �������, p_�� ����� �� ������ �Է¹���.
	int score = 0;
	cin >> n >> m;
	v.resize(m * 3);
	cycle.resize(n + 1);
	for (int i = 0; i <= n; i++) cycle[i] = i;
	for (int i = 0; i < m; i++) { // ����ġ��, ����� �� ����
		cin >> w >> p_1 >> p_2;
		v[i * 3] = w;
		v[i * 3 + 1] = p_1;
		v[i * 3 + 2] = p_2;
	}
	Qsort(0, m - 1); // ����ġ�� ���� ������ ����
	int x = 0, a, b;
	while (true) {
		if (x == m) break; // ������ Ž�� �� ����
		if (cycle[v[x * 3 + 1]] != cycle[v[x * 3 + 2]]) { // ����Ŭ�� �߻����� ���� ��
			route.push_back(x); // ��ο� �߰�
			a = find(v[x * 3 + 1]);
			b = find(v[x * 3 + 2]);
			if (cycle[a] > cycle[b]) cycle[a] = b; // ���� �ֵ��� �������� ���Ͽ����ε�
			else cycle[b] = a;
			score += v[x * 3];
		}
		x++;
	}
	cout << score << endl;
}