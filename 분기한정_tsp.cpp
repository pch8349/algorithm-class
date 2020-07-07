#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> v;
vector<int> lowest_bound; // 모든 선들 중 가장 낮은 애들
vector<vector<int>> route; // 경로, 비용을 저장할 배열
vector<int> recycle; // 경로 배열에 저장하기 위한 1차원배열
int lower = INT_MAX;
int point;

void Qsort(int st, int end) { // 퀵소트를 이용해 정렬. 2차원 배열이라 가중치에 따라 정렬할 때
	if (st >= end) return; // 직접 바꾸는 부분을 지정
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

void Fin(vector<bool> route_check) { // 리프 노드에서 나머지 계산
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
	vector<bool> route_check(n + 1, 0); // 방문을 했는지 안했는지 체크하는 배열
	recycle = route[come]; // 지금까지 갔던 루트 복사
	int x = route.size(); // x가 현재 형재노드들의 시작점이 된다.
	for (int i = 1; i < route[come].size(); i++) route_check[route[come][i]] = true; // 불필요하게 돈다. 고칠 수 있을듯?
	for (int i = 1; i <= n; i++) {
		if (route_check[i] == false) {
			recycle.push_back(i);
			recycle[0] = route[come][0] - lowest_bound[route[come].back()] + v[route[come].back()][i]; // 가중치값 갱신

			if (recycle[0] < lower) { // 가중치 값이 현재까지 나온 최소값보다 작을때만
				route_check[i] = true; // 방문했으니 경로체크
				if (recycle.size() == n) { // 만약 리프 노드 도달시
					Fin(route_check);
					route.push_back(recycle);
					for (int j = 0; j < 2; j++) recycle.pop_back(); // Fin 함수에서 recycle에 2개가 더 들어가니 지워주어야 한다. 안그러면 틀림.
					if (lower > recycle[0]) { // 최소값 비교
						point = route.size() - 1;
						lower = recycle[0];
					}
				}
				else route.push_back(recycle);
				route_check[i] = false; // 다음 노드로 갈거니 경로 해제
				recycle.pop_back();
			}
		}
	}
	int y = route.size();
	Qsort(x, y - 1); // 가중치선값 순서대로 정렬
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