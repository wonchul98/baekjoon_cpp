#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int N;
vector<int> v[51];
int fourth[51];
bool print =false;
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 9; j++) {
			int input;
			cin >> input;
			v[i].push_back(input);
		}
	}
	vector<int> e = { 1,2,3,4,5,6,7,8 };
	sort(e.begin(), e.begin() + 8);
	int max_score = 0;

	do { //���� ����
		if (print) {
			cout << "����" << endl;
			for (int i = 0; i < 8; i++) {
				cout << e[i] << " ";
			}
			cout << "\n";
		}
		int total_score = 0;
		int play_idx = 0;
		for (int i = 0; i < N; i++) { //�̴� �� �ൿ
			int idx = 0;
			vector<int> cur;
			for (int j = 0; j < 9; j++) {
				if (j == 3) cur.push_back(v[i][0]);
				else {
					cur.push_back(v[i][e[idx++]]);
				}
			}
			if (print) {
				cout << "���� ����" << endl;
				for (int i = 0; i < 9; i++) {
					cout << cur[i] << " ";
				}
				cout << "\n";
			}
			int out = 0;
			int score = 0;
			int bases[4] = { 0 };  // 0: Ȩ, 1: 1��, 2: 2��, 3: 3�� 
			while (out < 3) {
				int now = cur[play_idx++];
				if (play_idx > 8) play_idx = 0;

				if (now == 0) {
					out += 1;
				}
				else if (now >= 1 && now <= 3) {
					for (int j = 3; j >= 1; j--) {
						if (bases[j] == 1) {
							if (j + now > 3) {
								score++;
							}
							else {
								bases[j + now] = 1;
							}
							bases[j] = 0;
						}
					}
					bases[now] = 1;
				}
				else {
					score++;  // Ÿ�� �ڽ��� ����
					for (int j = 1; j <= 3; j++) {
						score += bases[j];
						bases[j] = 0;  // Ȩ���� ����
					}
				}
			}
			total_score += score; // �� �̴� ������ ���� �ջ�
			if (print) printf("score: %d, total_score: %d\n", score, total_score);
		}
		max_score = max(max_score, total_score); //�� ��� ������ �ִ� ���� ���ϱ�
	} while (next_permutation(e.begin(), e.end()));
	cout << max_score << endl;
	return 0;
}