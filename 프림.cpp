#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int n, m, a, b, w;
	cin >> n >> m;
	vector<vector<int>> v(n + 1, vector<int> (n+1, 0)); // �� ��帶�� ����� ����ġ �� ����
	vector<int> inf(n + 1, 2147483647); // ��忡 ����ġ�� ������ �迭
	vector<bool> check(n + 1); // �湮�ߴ��� Ȯ��
	queue<int> bfs; // queue
	for (int i = 0; i < m; i++) {
		cin >> w >> a >> b; // ����ȳ��1, ����ȳ��2, ����ġ�� ������ �Է¹޴´�.
		v[a][b] = w;
		v[b][a] = w;
	}
	int x; // �������� ���� ���� �Է¹ޱ�
	cin >> x;
	bfs.push(x);
	check[x] = true;
	inf[x] = 0;
	while (!bfs.empty()) {
		for (int i = 1; i <= n; i++) {
			if (v[bfs.front()][i] != 0) { // queue�� ù��°�� ���ִ� ��ȣ�� ����� �ִ�
				if (check[i] != true) { // Ž���� �� ���� ���ٸ�
					if (inf[i] > v[bfs.front()][i]) { // ����ġ ���� �� �۴ٸ�
						bfs.push(i);
						inf[i] = v[bfs.front()][i]; // queue�� �ְ�, ����ġ�� ����
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