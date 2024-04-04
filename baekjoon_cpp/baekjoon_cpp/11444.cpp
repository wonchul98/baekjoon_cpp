#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define p 1000000007L
vector<vector<ll>> mul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
	ll a1 = ((a[0][0] % p * b[0][0] % p) % p + (a[0][1] % p * b[1][0] % p) % p) % p;
	ll a2 = ((a[0][0] % p * b[0][1] % p) % p + (a[0][1] % p * b[1][1] % p) % p) % p;
	ll b1 = ((a[1][0] % p * b[0][0] % p) % p + (a[1][1] % p * b[1][0] % p) % p) % p;
	ll b2 = ((a[1][0] % p * b[0][1] % p) % p + (a[1][1] % p * b[1][1] % p) % p) % p;


	return { {a1, a2}, {b1, b2} };
}

vector<vector<ll>> myPow(ll n) {
	vector<vector<ll>> cur = { {1, 0}, {0, 1} }; // Identity matrix
	vector<vector<ll>> mult = { {1, 1}, {1, 0} };
	while (n > 0) {
		if (n % 2 == 1) {
			cur = mul(cur, mult);
		}
		n /= 2;
		mult = mul(mult, mult);
	}
	return cur;
}

int main() {
	ll N;
	cin >> N;
	/*for (ll i = 100; i < 200; i++) {
		N = i;
		if (N == 1) {
			cout << 0 << endl;
		}
		if (N == 2) {
			cout << 1 << endl;
		}
		if (N == 3) {
			cout << 1 << endl;
		}
		vector<vector<ll>> ans = myPow(N-3);
		cout << (ans[0][0]%p + ans[0][1]%p) % p << endl;
	}*/
	if (N == 1) {
		cout << 1 << endl;
		return 0;
	}
	if (N == 2) {
		cout << 1 << endl;
		return 0;
	}

	vector<vector<ll>> ans = myPow(N - 2);
	cout << (ans[0][0] + ans[0][1]) % p << endl; // for fibonacci, you might want to adjust this based on what you're calculating
	return 0;
}
