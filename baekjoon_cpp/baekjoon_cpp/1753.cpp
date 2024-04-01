#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

const int MAX_V = 20001;
const int INF = numeric_limits<int>::max();

vector<pair<int, int>> adj[MAX_V]; // �� ����� ���� ����Ʈ (���, ����ġ)
int dist[MAX_V]; // ���� ���κ��� �� �������� �ִ� �Ÿ�
int V, E, K; // V: ����� ����, E: ������ ����, K: ���� ���

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // �ּ� ��
    fill(dist, dist + V + 1, INF); // ��� �Ÿ��� ���Ѵ�� �ʱ�ȭ
    dist[start] = 0; // ���� ����� �Ÿ��� 0
    pq.push({ 0, start }); // ���� ��带 ť�� ����

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // ���� �������� �Ÿ��� �̹� �˷��� �ִ� �Ÿ����� �� ��� ����
        if (dist[currentNode] < currentDist) continue;

        // ���� ��� Ž��
        for (auto& edge : adj[currentNode]) {
            int nextNode = edge.first;
            int weight = edge.second;
            int nextDist = currentDist + weight;

            // �� ª�� ��� �߰� �� ������Ʈ
            if (nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                pq.push({ nextDist, nextNode });
            }
        }
    }
}

int main() {
    cin >> V >> E >> K;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w }); // ��� u���� v�� ���� ����ġ w
    }

    dijkstra(K);

    // ��� ���
    for (int i = 1; i <= V; i++) {
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }

    return 0;
}
