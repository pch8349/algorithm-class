#include <iostream>
#include <vector>
using namespace std;

vector<int> v; // 간선비용, 연결된 두 정점 저장하는 배열
vector<int> cycle; // 사이클 발생 체크용
vector<int> route; // 최소비용 경로 저장
vector<int> cost; // 비용 저장

int find(int s) { // 유니온파인드
	if (cycle[s] == s) return s;
	return cycle[s] = find(cycle[s]);
}

void Qsort(int st, int end) { // 퀵소트를 이용해 정렬. 1차원 배열에 가중치, 연결된 정점을 모두 저장해서
	if (st >= end) return; // 직접 바꾸는 부분을 지정해주었다.
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
	int n, m, w, p_1, p_2; // n은 정점 개수, m은 간선 개수. a는 간선비용, p_는 연결된 두 정점을 입력받음.
	int score = 0;
	cin >> n >> m;
	v.resize(m * 3);
	cycle.resize(n + 1);
	for (int i = 0; i <= n; i++) cycle[i] = i;
	for (int i = 0; i < m; i++) { // 가중치값, 연결된 선 저장
		cin >> w >> p_1 >> p_2;
		v[i * 3] = w;
		v[i * 3 + 1] = p_1;
		v[i * 3 + 2] = p_2;
	}
	Qsort(0, m - 1); // 가중치선 작은 순으로 정렬
	int x = 0, a, b;
	while (true) {
		if (x == m) break; // 끝까지 탐색 시 종료
		if (cycle[v[x * 3 + 1]] != cycle[v[x * 3 + 2]]) { // 사이클이 발생하지 않을 때
			route.push_back(x); // 경로에 추가
			a = find(v[x * 3 + 1]);
			b = find(v[x * 3 + 2]);
			if (cycle[a] > cycle[b]) cycle[a] = b; // 작은 애들을 기준으로 유니온파인드
			else cycle[b] = a;
			score += v[x * 3];
		}
		x++;
	}
	cout << score << endl;
}