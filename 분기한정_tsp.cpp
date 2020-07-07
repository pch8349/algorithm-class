#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> v;
vector<int> lowest_bound; // ��� ���� �� ���� ���� �ֵ�
vector<vector<int>> route; // ���, ����� ������ �迭
vector<int> recycle; // ��� �迭�� �����ϱ� ���� 1�����迭
int lower = INT_MAX;
int point;

void Qsort(int st, int end) { // ����Ʈ�� �̿��� ����. 2���� �迭�̶� ����ġ�� ���� ������ ��
	if (st >= end) return; // ���� �ٲٴ� �κ��� ����
	int pivot = st, a = pivot + 1, b = end;
	int t = 0;
	while (a <= b) {
		while (a <= end && route[a][0] < route[pivot][0]) a--;
		while (b > st && route[b][0] >= route[pivot][0]) b--;
		if (a > b) {
			for (int i = 0; i < route[b].size(); i++) swap(route[b][i], route[pivot][i]);
		}
		else {
			for (int i = 0; i < route[a].size(); i++) swap(route[a][i], route[b][i]);
		}
		if (a == b) {
			t++;
			if (t > 1) break;
		}
	}
	Qsort(st, b - 1);
	Qsort(b + 1, end);
}

void Fin(vector<bool> route_check) { // ���� ��忡�� ������ ���
	for (int i = 1; i <= n; i++) {
		if (route_check[i] == false) {
			recycle[0] = recycle[0] - lowest_bound[recycle.back()] - lowest_bound[i] + v[recycle.back()][i] + v[i][1];
			recycle.push_back(i);
			recycle.push_back(1);
			return;
		}
	}
}

void BaB(int come) {
	vector<bool> route_check(n + 1, 0); // �湮�� �ߴ��� ���ߴ��� üũ�ϴ� �迭
	recycle = route[come]; // ���ݱ��� ���� ��Ʈ ����
	int x = route.size(); // x�� ���� ��������� �������� �ȴ�.
	for (int i = 1; i < route[come].size(); i++) route_check[route[come][i]] = true; // ���ʿ��ϰ� ����. ��ĥ �� ������?
	for (int i = 1; i <= n; i++) {
		if (route_check[i] == false) {
			recycle.push_back(i);
			recycle[0] = route[come][0] - lowest_bound[route[come].back()] + v[route[come].back()][i]; // ����ġ�� ����

			if (recycle[0] < lower) { // ����ġ ���� ������� ���� �ּҰ����� ��������
				route_check[i] = true; // �湮������ ���üũ
				if (recycle.size() == n) { // ���� ���� ��� ���޽�
					Fin(route_check);
					route.push_back(recycle);
					for (int j = 0; j < 2; j++) recycle.pop_back(); // Fin �Լ����� recycle�� 2���� �� ���� �����־�� �Ѵ�. �ȱ׷��� Ʋ��.
					if (lower > recycle[0]) { // �ּҰ� ��
						point = route.size() - 1;
						lower = recycle[0];
					}
				}
				else route.push_back(recycle);
				route_check[i] = false; // ���� ���� ���Ŵ� ��� ����
				recycle.pop_back();
			}
		}
	}
	int y = route.size();
	Qsort(x, y - 1); // ����ġ���� ������� ����
	for (int i = x; i < y; i++) {
		BaB(i);
	}
}

int main() {
	int m, x, cost = 0;
	cin >> n >> m;
	v.resize(n + 1);
	for (int i = 0; i <= n; i++)v[i].resize(n + 1, 0);
	lowest_bound.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		x = INT_MAX;
		for (int j = 1; j <= n; j++) {
			cin >> v[i][j];
			if (x > v[i][j] && v[i][j] != 0) x = v[i][j];
		}
		lowest_bound[i] = x;
		cost += x;
	}
	route.push_back({ cost, m });
	BaB(0);
	cout << endl;
	for (int i = 0; i <= n + 1; i++) cout << route[point][i] << " ";
	cout << "\n" << lower << endl;
}