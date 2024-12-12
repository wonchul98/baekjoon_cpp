#include <iostream>
#include <queue>
#include <stdlib.h>

using namespace std;

void find_island();
void find_edges();
int find_next_edges();
bool inRange(int x, int y);

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int N, idx = 2;
int map[101][101];
bool visited[101][101];
queue<pair<pair<int, int>, int>> edges; // 모서리들
bool debug = false;

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    find_island();
    find_edges();
    cout << find_next_edges() << endl;

    if (debug) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << map[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}

void find_island() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 1 && !visited[i][j]) {
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                visited[i][j] = true;

                while (!q.empty()) {
                    int cur_x = q.front().first;
                    int cur_y = q.front().second;
                    q.pop();

                    map[cur_x][cur_y] = idx;
                    for (int k = 0; k < 4; k++) {
                        int next_x = cur_x + dx[k];
                        int next_y = cur_y + dy[k];
                        if (inRange(next_x, next_y) && map[next_x][next_y] == 1 && !visited[next_x][next_y]) {
                            visited[next_x][next_y] = true;
                            q.push(make_pair(next_x, next_y));
                        }
                    }
                }
                idx++;
            }
        }
    }
}

void find_edges() {
    bool edge_visited[101][101] = {false};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] != 0) {
                for (int k = 0; k < 4; k++) {
                    int next_x = i + dx[k];
                    int next_y = j + dy[k];
                    if (inRange(next_x, next_y) && !edge_visited[next_x][next_y] && map[next_x][next_y] == 0) {
                        edge_visited[next_x][next_y] = true;
                        edges.push(make_pair(make_pair(next_x, next_y), map[i][j]));
                    }
                }
            }
        }
    }
}

int find_next_edges() {
    pair<int, int> days[101][101]; // 일수 + 섬 번호
    bool local_visited[101][101] = {false}; // 로컬에서만 사용하는 visited 배열

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            days[i][j] = make_pair(0, 0);
        }
    }

    queue<pair<pair<int, int>, pair<int, int>>> q;

    while (!edges.empty()) {
        int x = edges.front().first.first;
        int y = edges.front().first.second;
        int island_num = edges.front().second;
        edges.pop();

        q.push(make_pair(make_pair(x, y), make_pair(island_num, 1)));
        days[x][y] = make_pair(1, island_num);
        local_visited[x][y] = true;
    }

    while (!q.empty()) {
        int cur_x = q.front().first.first;
        int cur_y = q.front().first.second;
        int island_num = q.front().second.first;
        int day = q.front().second.second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int next_x = cur_x + dx[i];
            int next_y = cur_y + dy[i];

            if (!inRange(next_x, next_y) || map[next_x][next_y] != 0) continue;

            if (local_visited[next_x][next_y]) {
                if (days[next_x][next_y].second != island_num) {
                    return day + days[next_x][next_y].first;
                }
            } else {
                local_visited[next_x][next_y] = true;
                days[next_x][next_y] = make_pair(day + 1, island_num);
                q.push(make_pair(make_pair(next_x, next_y), make_pair(island_num, day + 1)));
            }
        }
    }

    return -1; // 만날 수 없는 경우
}

bool inRange(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N;
}
