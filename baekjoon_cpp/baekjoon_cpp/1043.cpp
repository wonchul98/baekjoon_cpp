#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int N, M, T_n;
bool know_truth[51];
bool print = false;
int map[51][51] = { 0, };
void DFS(int a);
int main() {
	cin >> N >> M;
	cin >> T_n;
	vector<int> start;
	for(int i = 0; i < T_n;i++) {
		int input;
		cin >> input;
		start.push_back(input);
		know_truth[input] = true;
	}

	for (int i = 1; i <= N; i++) {
		know_truth[i] = false;
	}

	// �׷��� �����
	vector<int> party[50];

	for (int i = 0; i < M; i++) {//��� ��Ƽ�� ���ؼ� 
		if (print) cout << "i: " << i << endl;
		int input;
		cin >> input;
		vector<int> C(2, 1);
		if(input > 2) C.insert(C.end(), 0, input-2);

		for (int j = 0; j < input; j++) {
			if(j > 1)C.push_back(0);
			int input2;
			cin >> input2;
			party[i].push_back(input2);
		}
		sort(C.begin(), C.end());
		if (print)cout << "c size: " << C.size() << endl;
		if (party[i].size() > 1) {
			do {
				int fst = -1 , snd = -1;
				for (int j = 0; j < party[i].size(); j++) {
					if (print)cout << "j: " << j << " C[j]: " << C[j] << endl;
					if (C[j] == 1 && fst == -1) fst = j;
					else if (C[j] == 1 && fst != -1) snd = j;
				}
				if (print)cout << fst << snd << endl;
				map[party[i][fst]][party[i][snd]] = 1;
				map[party[i][snd]][party[i][fst]] = 1;
				if (print) printf("connected: %d, %d\n", party[i][fst],party[i][snd]);
			} while (next_permutation(C.begin(),C.end()));
		}
		
	}
	// DFS
	for (int i = 0; i < start.size(); i++) {
		DFS(start[i]);
	}
	int cnt = 0;
	
	//��� ��Ƽ�� ���ؼ� ����
	for (int i = 0; i < M; i++) {
		bool know = false;
		for (int j = 0; j < party[i].size(); j++) {
			if (know_truth[party[i][j]]) {
				know = true;
				break;
			}
		}
		if (know) cnt++;
	}
	cout << M - cnt << endl;
	return 0;
}

void DFS(int a) {
	if (print) printf("DFS(%d)\n", a);
	know_truth[a] = true;
	for (int i = 1; i <= N; i++) {
		if (a == i) continue;
		if (map[a][i] == 1 && !know_truth[i]) {
			DFS(i);
		}
	}
	return;
}