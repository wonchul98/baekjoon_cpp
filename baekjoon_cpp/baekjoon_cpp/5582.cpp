#include<bits/stdc++.h>

using namespace std;
string source, target;
int arr[4001][4001];
int ans = 0;
int main() {
	cin >> source >> target;
	for (int i = 0; i <= source.length(); i++) {
		arr[i][0] = 0;
	}
	for (int j = 0; j < target.length(); j++) {
		arr[0][j] = 0;
	}
	for (int i = 1; i <= source.length(); i++) {
		for (int j = 1; j <= target.length(); j++) {
			if (source.at(i-1) == target.at(j-1)) {
				arr[i][j] = arr[i - 1][j - 1] + 1;
				ans = max(ans, arr[i][j]);
			}
		}
	}
	cout << ans << "\n";
	return 0;
}