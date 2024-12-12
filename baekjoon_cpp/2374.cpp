#define ll long long
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
vector<ll> h;
int N;
ll maxHeight = 0;

void findMaxHeight();

int main() {
	cin >> N;
	h.push_back(0); // idx ¸ÂÃß±â
	for (int i = 0; i < N; i++) {
		ll input;
		cin >> input;
		h.push_back(input);
	}
	findMaxHeight();
	ll ans = 0;
	ll cur = 0;
	ll prev = 0;
	for (int i = 1; i < h.size(); i++) {
		cur = maxHeight - h[i];
		if (cur > prev) {
			ans += (cur - prev);
			prev = cur;
		}
		else {
			prev = cur;
		}
	}
	cout << ans << endl;
	return 0;
}

void findMaxHeight() {
	for (int i = 1; i < h.size(); i++) {
		maxHeight = max(maxHeight, h[i]);
	}
}