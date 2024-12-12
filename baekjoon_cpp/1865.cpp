#include<bits/stdc++.h>
using namespace std;
int dist[501][501];
int main() {
	int T;
	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++) {
		int N, M, W;
		cin >> N >> M >> W;
		//거리 초기화
		for (int i = 1; i <= N; i++) {
			fill_n(dist[i], N + 1, 987654321);
			dist[i][i] = 0;
		}
		for (int i = 0; i < M; i++) {
			int S, E, T;
			cin >> S >> E >> T;
			dist[S][E] = min(T, dist[S][E]);
			dist[E][S] = min(T, dist[S][E]);
		}
		for (int i = 0; i < W; i++) {
			int S, E, T;
			cin >> S >> E >> T;
			dist[S][E] = min(-T, dist[S][E]);
		}
		//floyd-warshall
		bool flag = false;
		for (int mid = 1; mid <= N; mid++) {
			for (int from = 1; from <= N; from++) {
				if (mid == from) continue;
				for (int to = 1; to <= N; to++) {
					if (mid == to || from == to) continue;
					dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);
					if (dist[from][from] < 0) flag = true;
				}
				if (flag) break;
			}
			if (flag) break;
		}
		
		if (flag) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}