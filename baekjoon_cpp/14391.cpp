#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int N, M, maxValue = 0, curValue = 0;
int Map[4][4]; // 4x4 크기로 고정
bool visited[4][4];

// 아래[0], 오른쪽[1]
int dx[2] = { 1, 0 };
int dy[2] = { 0, 1 };

void go(int dir, int x, int y, stack<pair<int, int>>& s);
void stop(int x, int y, stack<pair<int, int>> s);
pair<int, int> scan();
bool inRange(int x, int y);
int calc(stack<pair<int, int>> s);

void input() {
    cin >> N >> M;
    string str;
    for (int r = 0; r < N; r++) {
        cin >> str;
        for (int c = 0; c < M; c++) {
            Map[r][c] = str[c] - '0';
        }
    }
}

void dfs(int r, int c) {
    if (r == N) {
        int sum = 0;
        for (int r = 0; r < N; r++) {
            int temp = 0;
            for (int c = 0; c < M; c++) {
                if (visited[r][c]) temp = temp * 10 + Map[r][c];
                else {
                    sum += temp;
                    temp = 0;
                }
            }
            sum += temp;
        }
        for (int c = 0; c < M; c++) {
            int temp = 0;
            for (int r = 0; r < N; r++) {
                if (!visited[r][c]) temp = temp * 10 + Map[r][c];
                else {
                    sum += temp;
                    temp = 0;
                }
            }
            sum += temp;
        }
        maxValue = max(maxValue, sum);
        return;
    }
    if (c == M) {
        dfs(r + 1, 0);
        return;
    }
    visited[r][c] = true;
    // 가로로 이어짐
    dfs(r, c + 1);

    visited[r][c] = false;
    // 세로로 이어짐
    dfs(r, c + 1);
}

void solve() {
    dfs(0, 0);
    cout << maxValue << "\n";
}

int main() {
    input();
    solve();
    return 0;
}
