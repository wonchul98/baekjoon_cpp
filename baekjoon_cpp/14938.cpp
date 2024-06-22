
#include<bits/stdc++.h>

using namespace std;
int n, m, r;
int item[101];
int point[101];
int dist[101][101];
int main() {
	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) fill_n(dist[i], n+1, 987654321);
	for (int i = 1; i <= n; i++) {
		dist[i][i] = 0;
		cin >> item[i];
	}
	for (int i = 0; i < r; i++) {
		int from, to, distance;
		cin >> from >> to >> distance;
		dist[from][to] = distance;
		dist[to][from] = distance;
	}
	for (int mid = 1; mid <= n; mid++) {
		for (int from = 1; from <= n;from++) {
			if (from == mid) continue;
			for (int to = 1; to <= n; to++) {
				if (mid == to || from == to) continue;
				dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);
			}
		}
	}
	for (int from = 1; from <= n; from++) {
		for (int to = 1; to <= n; to++) {
			//cout << dist[from][to] << " ";
			if (from == to) continue;
			if (dist[from][to] <= m) {
				//cout << "!";
				point[from] += item[to];
			}
		}
		//cout << "\n";
	}
	int maxi = 0;
	for (int i = 1; i <= n; i++) {
		//cout << point[i] << " ";
		maxi = max(maxi, point[i]+item[i]);
	}
	//cout << "\n";
	cout << maxi << endl;
	return 0;
}