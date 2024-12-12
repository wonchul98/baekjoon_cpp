#define INF 987654321

#include<bits/stdc++.h>

using namespace std;
int next_node[201][201];
int dist[201][201];

int N, M;

int main(){
    cin >> N >> M;

    // next_node 배열 초기화
    for(int i = 1; i <= N;i++){
        fill_n(next_node[i], N+1, 0);
    }

    // 거리 배열 초기화
    for(int i = 1; i <= N;i++){
        fill_n(dist[i], N+1, INF);
    }

    // 거리 입력 받기
    for(int i = 0; i < M;i++){
        int s, e, d;
        cin >> s >> e >> d;
        dist[s][e] = d;
        dist[e][s] = d;
        next_node[s][e] = e;
        next_node[e][s] = s;
    }

    for (int mid = 1; mid <= N; mid++) {
        for (int start = 1; start <= N; start++) {
            for (int end = 1; end <= N; end++) {
                if (start == end) continue;
                if (dist[start][end] > dist[start][mid] + dist[mid][end]) { // 갱신하는 경우 (mid를 거치는게 빠른 경우)
                    dist[start][end] = dist[start][mid] + dist[mid][end];
                    next_node[start][end] = next_node[start][mid];
                }
            }
        }
    }
    for(int i = 1; i <= N;i++){
        for(int j = 1; j <= N;j++){
            if(next_node[i][j] == 0) cout << "- "; 
            else cout << next_node[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}