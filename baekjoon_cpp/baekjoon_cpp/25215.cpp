#include<iostream>
using namespace std;

string input;
bool s = true;
bool small(int a) {
	if (int(input[a]) >= 65 && int(input[a] <= 90)) return false;
	else return true;
}

int main() {
	cin >> input;
	int extra = 0;
	for (int i = 0; i < input.length(); i++) {
		//cout << input[i];
		if (s && !small(i)) {
			if (i < input.length() - 1 && !small(i + 1)) {//aAA
				s = !s; //������ Ȱ��ȭ(�빮�� �Է�)
				extra++;
				//cout << "��" ;
			}
			else {//aAa
				extra++; //�� �Է�
				//cout << "��";
			}
		}
		else if (!s && small(i)) {
			if (i < input.length() - 1 && small(i + 1)) {//Aaa
				s = !s; //������ ��Ȱ��ȭ(�ҹ��� �Է�)
				extra++;
				//cout << "��";
			}
			else {
				extra++; //���Է�
				//cout << "��";
			}
		}
		else continue;
	}
	cout << input.length() + extra << endl;
	return 0;
}