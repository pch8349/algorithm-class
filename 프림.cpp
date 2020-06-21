#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int n, m, a, b, w;
	cin >> n >> m;
	vector<vector<int>> v(n + 1, vector<int> (n+1, 0)); // 각 노드마다 연결된 가중치 선 저장
	vector<int> inf(n + 1, 2147483647); // 노드에 가중치값 저장할 배열
	vector<bool> check(n + 1); // 방문했는지 확인
	queue<int> bfs; // queue
	for (int i = 0; i < m; i++) {
		cin >> w >> a >> b; // 연결된노드1, 연결된노드2, 가중치값 순으로 입력받는다.
		v[a][b] = w;
		v[b][a] = w;
	}
	int x; // 시작으로 삼을 정점 입력받기
	cin >> x;
	bfs.push(x);
	check[x] = true;
	inf[x] = 0;
	while (!bfs.empty()) {
		for (int i = 1; i <= n; i++) {
			if (v[bfs.front()][i] != 0) { // queue에 첫번째로 들어가있는 번호와 연결된 애는
				if (check[i] != true) { // 탐색을 한 적이 없다면
					if (inf[i] > v[bfs.front()][i]) { // 가중치 값이 더 작다면
						bfs.push(i);
						inf[i] = v[bfs.front()][i]; // queue에 넣고, 가중치값 갱신
					}
				}
			}
		}
		check[bfs.front()] = true;
		bfs.pop();
	}
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += inf[i];
	cout << sum << endl;
}