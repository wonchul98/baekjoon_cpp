#include<iostream>

using namespace std;

void make_dp(int N);

int dp[102][102];

int main() {
	dp[2][1] = 2;
	int N;
	cin >> N;
	make_dp(N);
	int ans = 0;
	for (int i = 1; i < N; i++) {
		ans += dp[N][i];
	}

	cout << ans % 10007 << endl;

	return 0;
}

void make_dp(int N) {
	for (int i = 3; i <= N; i++) { // 층
		for (int j = 1; j < i; j++) { // 차이
			dp[i][j] += (dp[i - 1][j] * 2) % 10007; // 차이가 그대로
			dp[i][j] += dp[i - 1][j - 1] % 10007; // 차이가 늘어난 경우
			dp[i][j] += dp[i - 1][j + 1] % 10007; // 차이가 줄어든 경우
			dp[i][j] %= 10007;
		}
	}
}