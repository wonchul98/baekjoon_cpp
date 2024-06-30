#include <iostream>
#include <string>
using namespace std;


// X�� �̰���� Ȯ��
bool checkX(char map[3][3]) {

    for (int i = 0; i < 3; i++) {
        // ���� üũ
        if (map[i][0] == 'X' && map[i][0] == map[i][1]
            && map[i][1] == map[i][2]) return true;

        // ���� üũ
        if (map[0][i] == 'X' && map[0][i] == map[1][i]
            && map[1][i] == map[2][i]) return true;
    }
    // �밢 üũ
    if (map[0][0] == 'X' && map[0][0] == map[1][1]
        && map[1][1] == map[2][2]) return true;

    if (map[0][2] == 'X' && map[0][2] == map[1][1]
        && map[1][1] == map[2][0]) return true;

    return false;
}

// O�� �̰���� Ȯ��
bool checkO(char map[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (map[i][0] == 'O' && map[i][0] == map[i][1]
            && map[i][1] == map[i][2]) return true;

        if (map[0][i] == 'O' && map[0][i] == map[1][i]
            && map[1][i] == map[2][i]) return true;
    }
    if (map[0][0] == 'O' && map[0][0] == map[1][1]
        && map[1][1] == map[2][2]) return true;

    if (map[0][2] == 'O' && map[0][2] == map[1][1]
        && map[1][1] == map[2][0]) return true;

    return false;
}
int main() {
    string input;
    while (true) {
        char map[3][3];
        cin >> input;
        if (input[0] == 'e') break;

        // x�� o�� ����
        int x = 0;
        int o = 0;
        for (int i = 0; i < 9; i++) {
            // 3x3 2���� �迭�� �����
            map[i / 3][i % 3] = input[i];
            if (input[i] == 'X') x++;
            else if (input[i] == 'O') o++;
        }
        bool isX = checkX(map);
        bool isO = checkO(map);

        if (isX && !isO && x == o + 1) printf("valid\n"); // X�� �̱� ���
        else if (!isX && isO && x == o) printf("valid\n"); // O�� �̱� ���
        else if (!isX && !isO && x == 5 && o == 4) printf("valid\n"); // ���� �� ���
        else printf("invalid\n"); // �� ��쿡 �� ���� �ȵɶ�
    }
    return 0;
}