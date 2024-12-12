#include<bits/stdc++.h>

using namespace std;

int T, n, m;
int a[1001], b[1001];
vector<int> av, bv;

void input();
void solve();
vector<int> getSum(int arr[1001], int size);

int main() {
	input();
	solve();
	return 0;
}

void input() {
	cin >> T;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> b[i];
	}
}

void solve() {
	av = getSum(a, n);
	bv = getSum(b, m);

	sort(av.begin(), av.end());
	sort(bv.begin(), bv.end());

	long long count = 0;
	for (int i = 0; i < av.size(); i++) {
		int target = T - av[i];
		count += upper_bound(bv.begin(), bv.end(), target) - lower_bound(bv.begin(), bv.end(), target);
	}
	cout << count << "\n";
}

vector<int> getSum(int arr[1001], int size) {
	vector<int> sums;
	for (int i = 0; i < size; i++) {
		int sum = 0;
		for (int j = i; j < size; j++) {
			sum += arr[j];
			sums.push_back(sum);
		}
	}
	return sums;
}