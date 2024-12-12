#define ll long long

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<string>
#include <iomanip>

using namespace std;

struct Road{
    int start;
    int end;
    double dist;

    Road(int start, int end, double dist){
        this->start = start;
        this->end = end;
        this->dist = dist;
    }
};

struct Node{
    int idx;
    ll x;
    ll y;
};

int parent[1001];

void union_parent(int a, int b);
int find_parent(int a);
int get_parent(int a);
bool same_parent(int a, int b);
double cal_dist(Node a, Node b);

void make_roads(Node node);

int N, M;
vector<Road> roads;
vector<Node> nodes(1001);

bool compare(const Road &a, const Road &b) {
    return a.dist < b.dist;
}

int main(){
    cin >> N >> M;
    for(int i = 1; i <= N;i++){
        parent[i] = i; // 부모 배열 초기화
        int x, y;
        Node node;
        node.idx = i;
        cin >> node.x >> node.y;
        nodes[i] = node;
        make_roads(node);
    }
    for(int i = 0; i < M;i++){
        int s, e;
        cin >> s >> e;
        union_parent(s,e);
    }
    sort(roads.begin(), roads.end(), compare);
    int count = 0;
    double dist = 0;
    for(int i = 0; i < roads.size() && count <= N-M-1;i++){
        //cout << roads[i].dist << " ";
        if(same_parent(roads[i].start, roads[i].end)) continue; // 사이클인 경우 무시
        // cout << roads[i].start << " " << roads[i].end << endl;
        union_parent(roads[i].start, roads[i].end);
        count++;
        dist += roads[i].dist;
    }
    cout << fixed;
	cout.precision(2);
	cout << dist << '\n';

    return 0;
}

// 규칙 : 작은 idx가 parent가 된다. 
void union_parent(int node_idx1, int node_idx2){
    int parent_a = find_parent(node_idx1);
    int parent_b = find_parent(node_idx2);
    if(parent_a < parent_b) parent[parent_b] = parent_a;
    else parent[parent_a] = parent_b;
}

int find_parent(int a){
    if(parent[a] == a) return a;
    return find_parent(parent[a]);
}

bool same_parent(int a, int b){
    if(find_parent(a) == find_parent(b)) return true;
    return false;
}

void make_roads(Node node){
    // cout << "make_road: " << node.idx << endl;
    for(int i = 1; i < node.idx;i++){ // 방금 추가한 노드는 제외하기 위해 nodes.size()-1만큼 for문을 돈다
        double dist = cal_dist(node, nodes[i]);
        // cout << i << " " << node.idx << " " << dist << endl;
        roads.push_back(Road(i, node.idx, dist)); // 새롭게 road추가
    }
}

double cal_dist(Node a, Node b) {
    double dx = pow(a.x - b.x, 2);
    double dy = pow(a.y - b.y, 2);
    return sqrt(dx + dy);
}