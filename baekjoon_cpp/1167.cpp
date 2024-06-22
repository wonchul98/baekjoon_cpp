#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

class Node; // Node Ŭ������ ����

class Info {
public:
	int dist;
	Node* n; // Node ��ü�� ������
	Info(int d, Node* n) : dist(d), n(n) {} // ������
};

class Node {
public:
	int num;
	vector<Info> con; // Info ��ü���� ����
	Node() : num(0) {} // �⺻ ������
	Node(int num) : num(num) {} // �Ű������� �ִ� ������
	void addConnection(int dist, Node* node) {
		con.push_back(Info(dist, node));
	}
};

vector<Node> nodes; // Node ��ü���� �����ϴ� ����
int N;
int maxDepth = 0;
int maxNodeNum = 0;

int recur(Node* n, int from) {
	//printf("recur(%d, %d)\n", n->num, from);
	if (n->con.size() == 1 && n->con[0].n->num == from) return 0;
	int maxi = 0;
	for (int i = 0; i < n->con.size(); i++) {
		if (n->con[i].n->num != from) { // ���� ���� �ǵ��ư��� �ʵ��� üũ
			maxi = max(recur(n->con[i].n, n->num) + n->con[i].dist, maxi);
		}
	}
	return maxi;
}

int getAns(Node* n) {
	//printf("getAns(%d)\n", n->num);
	priority_queue<int> pq;
	int num = 0;
	for (int i = 0; i < n->con.size(); i++) {
		pq.push(recur(n->con[i].n, n->num) + n->con[i].dist);
	}
	if (!pq.empty()) {
		//cout << "num1: " << pq.top() << endl;
		num += pq.top();
		pq.pop();
	}
	if (!pq.empty()) {
		//cout << "num2: " << pq.top() << endl;
		num += pq.top();
		pq.pop();
	}
	return num;
}

void dfs(Node* n, int from, int cnt) {
	//printf("dfs(%d, %d, %d)\n", n->num, from, cnt);
	if (n->con.size() == 1 && n->con[0].n->num == from) {
		if (maxDepth < cnt) {
			maxDepth = cnt;
			maxNodeNum = n->num;
		}
	}
	int maxi = 0;
	for (int i = 0; i < n->con.size(); i++) {
		if (n->con[i].n->num != from) { // ���� ���� �ǵ��ư��� �ʵ��� üũ
			dfs(n->con[i].n, n->num, cnt + n->con[i].dist);
		}
	}
	return;
}

int main() {
	cin >> N;
	nodes.push_back(Node()); // ���� ��� �߰� (�ε��� 0�� �ش�)
	for (int i = 1; i <= N; i++) {
		nodes.push_back(Node(i));
	}
	for (int i = 0; i < N; i++) {
		int cur, next, dist;
		cin >> cur;
		Node* curNode = &nodes[cur];
		while (true) {
			cin >> next;
			if (next == -1) break;
			cin >> dist;
			curNode->addConnection(dist, &nodes[next]);
		}
	}
	dfs(&nodes[1], 0, 0);
	cout << getAns(&nodes[maxNodeNum]) << endl;
	return 0;
}