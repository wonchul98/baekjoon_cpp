#define _CRT_SECURE_NO_WARNINGS
#define INF 987654321
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

void setting();
void dijkstra();
void solution();
void answer();

bool print = false;
int n, m, k;
vector<vector<int>> dist(1001,vector<int>(1001,INF));
vector<priority_queue<int, vector<int> , less<int>>> town_dist(1001); //��������

struct cmp {
	bool operator() (pair<int, int>& a, pair<int, int>& b) {
		return a.second > b.second;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solution();

	return 0;
}

void setting() {
	if (print) cout << "setting" << endl;
	//freopen("input/1854_input.txt", "r", stdin);
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		dist[a][b] = c;
	} 

	town_dist[1].push(0); //������->�������� �ּҰ��� 0
}

void solution() {
	setting();
	dijkstra();
	answer();
}
	
void dijkstra() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq; //second���� ��������
	pq.push(make_pair(1, 0));

	while (!pq.empty()) {
		int current = pq.top().first; //���� ��� ��ȣ
		int distance = pq.top().second; //�Ÿ�
		pq.pop();
		//if (min_dist[current] < distance) continue; //�ּҰ� �ƴѰ�� continue
		if (print)printf("���� ���: (%d, %d)\n", current, distance);

		for (int i = 1; i <= n; i++) {
			int next, next_dist;
			//���� ���
			if (dist[current][i] == INF) continue; //������ ���� ���
			else {
				next = i; //���� ��� ��ȣ
				next_dist = distance + dist[current][next];
			}
			if (print)printf("next: %d, next_dist:%d, size: %d\n", next, next_dist, town_dist.at(next).size());
			if (town_dist.at(next).size() < k) { //k��ŭ ���� ��ä�� ���
				town_dist.at(next).push(next_dist);
				pq.push(make_pair(next, next_dist));//pq�� ����
			}
			else if (town_dist.at(next).top() > next_dist) { //k��ŭ ä���µ� ����
				if (print) cout << " top ���� " << endl;
				town_dist.at(next).pop();
				town_dist.at(next).push(next_dist);
				pq.push(make_pair(next, next_dist));//pq�� ����
			}
			// k��ŭ ä������ ������ ���ϴ� ��쿡�� pq�� �ٽ� ���� �ʴ´�. 
		}
	}
}

void answer() {
	for (int i = 1; i <= n; i++) {
		if(print)cout << "i: " << i << endl;
		if (k > town_dist[i].size()) cout << "-1" << endl;
		else cout << town_dist[i].top() << endl;
	}
}


