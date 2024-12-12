#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int map[10][10];
int N, M;
void find_island();
void find_dfs(int x, int y);
void make_bridge(int x);
int choose_bridge();
int bridge_dfs(int x);

bool visited[10][10] = { false, };
bool bridge_visited[7] = { false, };
int island_idx = 1;
bool print= false;

struct INFO {
	int start;
	int end;
	int length;
};

int island_map[10][10]; //���� ��ǥ ���� ����
vector<pair<int, int>> island[6];
vector<int> con[7];
int bridge[7][7] = { 0, };
vector<INFO> bridge_v;
priority_queue<INFO> pq;

struct comp {
	bool operator()(INFO &a, INFO &b) {
		return a.length < b.length;
	}
};

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	find_island(); //���� ��ġ �ľ�, island_idx - 1��ŭ ���� ���� 
	if (print) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << island_map[i][j] << " ";
			}
			cout << "\n";
		}
	}
	for (int i = 0; i < island_idx-1; i++) {
		make_bridge(i); //2���� �迭 bridge �ϼ� 
	}
	if (print) {
		for (int i = 0; i < island_idx; i++) {
			for (int j = 0; j < island_idx; j++) {
				cout << bridge[i][j] << " ";
			}
			cout << "\n";
		}
	}
	for (int i = 1; i < island_idx; i++) {
		for (int j = i; j < island_idx; j++) {
			if (bridge[i][j] != 0) {
				INFO push;
				push.start = i;
				push.end = j;
				push.length = bridge[i][j];
				bridge_v.push_back(push);
			}
		}
	}
	cout << choose_bridge() << endl;

	return 0;
}
void find_island() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1 && !visited[i][j]) {
				find_dfs(i, j);
				island_idx++;
			}
		}
	}
}

void find_dfs(int x, int y) {
	visited[x][y] = true;
	island_map[x][y] = island_idx;
	if (island_idx < 6) {  // �迭�� ũ�⿡ ���� ����
		island[island_idx].push_back(make_pair(x, y));
	}
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
			if (map[nx][ny] == 1 && !visited[nx][ny]) {
				find_dfs(nx, ny);
			}
		}
	}
}

void make_bridge(int x) {
	for (int i = 0; i < island[x].size(); i++) {
		for (int j = 0; j < 4; j++) {
			int nx = island[x][i].first + dx[j];
			int ny = island[x][i].second + dy[j];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M || map[nx][ny] == 1) continue;
			int length = 0;
			while (1) {
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) break;
				else if (map[nx][ny] == 1) {
					/*�ٸ� ���� ������ ���*/
					int dest = island_map[nx][ny];
					if (length >= 2) {
						if (bridge[x][dest] == 0) {
							bridge[x][dest] = length; //������ length
							bridge[dest][x] = length;
						}
						else {
							if (x >= 0 && x < island_idx && dest >= 0 && dest < island_idx) {
								bridge[x][dest] = min(bridge[x][dest], length); //������ �� �� ����
								bridge[dest][x] = min(bridge[dest][x], length);
							}
						}
					}
					break;
				}
				else {
					nx += dx[j];
					ny += dy[j];
					length += 1;
				}
			}
		}
	}
}

int parent[7];

int find_set(int x) {
	if (parent[x] == x) return x;
	return parent[x] = find_set(parent[x]);
}

void union_set(int x, int y) {
	x = find_set(x);
	y = find_set(y); 
	//x�� �θ�� y�� �θ� �ٸ� ���� cycle�� ���� ��
	if (x != y) parent[y] = x; //y�� �θ� x�� �Ѵ� => x�� y����
}

int choose_bridge() {
	// �ʱ�ȭ: �� ���� �ڱ� �ڽ��� �θ�� ����
	for (int i = 1; i < island_idx; i++) {
		parent[i] = i;
	}

	// bridge_v�� ���̸� �������� ����
	sort(bridge_v.begin(), bridge_v.end(), comp());

	int cost = 0;  // �� ���
	int selected_edges = 0;  // ���õ� ������ ����

	for (const INFO& info : bridge_v) {
		// �� ���� �̹� ����Ǿ� ���� �ʴٸ�
		if (find_set(info.start) != find_set(info.end)) { //�θ� �ٸ��� -> ������ �ȵǾ��ִ�
			cost += info.length;
			union_set(info.start, info.end);
			selected_edges++;
		}
		// ��� ���� ����Ǿ��� ���
		if (selected_edges == island_idx - 2) break;
	}

	// ��� ���� ������� �ʾҴٸ� �Ұ���
	if (selected_edges != island_idx - 2) return -1;

	return cost;
} 

int bridge_dfs(int x) {
	if (print) printf("bridge_dfs(%d)\n", x);
	int cost = 0;
	bridge_visited[x] = true;
	if (x >= 0 && x < 7) {  // �迭�� ũ�⿡ ���� ����
		for (int i = 0; i < con[x].size(); i++) {
			int next_island = con[x][i];
			if (!bridge_visited[next_island]) {
				cost += bridge[x][next_island];
				cost += bridge_dfs(next_island);
			}
		}
	}
	return cost;
}