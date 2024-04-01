#include<iostream>
#define ll long long

using namespace std;
ll N, K;
ll p = 1000000007;
ll myPow(ll a, ll b);
int main() {
    cin >> N >> K;
    ll saveK = K;
    ll saveN = N;
    ll top = 1, down = 1;
    while (K--) {
        top *= N--;
        top %= p;
    }
    K = saveK;
    while (K--) {
        down *= saveK--;
        down %= p;
    }
    //cout << top << " " << down << endl;
    cout << top * myPow(down, p - 2) % p << endl;
    return 0;
}

ll myPow(ll a, ll b) {
    ll rst = 1;
    a %= p;
    while (b > 0) {
        if (b % 2 == 1) {
            rst = (rst * a) % p;
        }
        a = (a * a) % p;
        b /= 2;
    }
    return rst;
}