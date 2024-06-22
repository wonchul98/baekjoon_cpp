#include<iostream>
#include<vector>

using namespace std;
int N;
vector<int> v[100001];
bool visited[100001];
int dp[100001][2]; // 0 은 미설치 1은 설치

void dfs(int n);

int main() {
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs(1);
	cout << min(dp[1][0], dp[1][1]) << "\n";
	return 0;
}

void dfs(int num) {
	if (visited[num]) return;
	visited[num] = true;
	// leaf 노드일 경우 여기서 끝
	dp[num][0] = 0;
	dp[num][1] = 1;
	for (auto next : v[num]) {
		if (visited[next]) continue;
		dfs(next);
		dp[num][0] = dp[num][0] + dp[next][1]; //설치x -> 무조건 설치
		dp[num][1] = dp[num][1] + min(dp[next][0], dp[next][1]); // 설치o -> 더 이득인 것
	}

}