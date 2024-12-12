#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

int N;
vector<string> tables; // 여기에 만들어진 대진표를 넣자

void inferenceTable(string table, vector<pair<int, int>> idxAndLen);
string toggle(string table, int idx);

int main(){
    cin >> N;
    string table = "";
    vector<pair<int, int>> idxAndLen;
    idxAndLen.push_back(make_pair(0,N/2));
    idxAndLen.push_back(make_pair(N/2, N - N/2));
    for(int i = 0;i < N;i++) table.push_back('A');
    inferenceTable(table, idxAndLen);

    string trashTable = "A";
    for(int i = 0;i < N-1;i++) trashTable.push_back('B');
    //쓰레기값 넣는 코드
    int idx = 7 - tables.size();
    for(int i = 0; i < idx;i++){
        tables.push_back(trashTable);
    }

    for(int i = 0; i < tables.size();i++){
        cout << tables[i] << endl;
    }

    return 0;
}

void inferenceTable(string table, vector<pair<int, int>> idxAndLen){
     
    string inferTable = table;
    vector<pair<int, int>> newIdxAndLen;
    bool onlyOne = true;
    for(int i = 0;i < idxAndLen.size();i++){
        int idx = idxAndLen[i].first;
        int len = idxAndLen[i].second;
        if(len > 1){
            newIdxAndLen.push_back(make_pair(idx, len/2));
            newIdxAndLen.push_back(make_pair(idx+len/2, len-len/2));
            onlyOne = false;
        }else{
            newIdxAndLen.push_back(make_pair(idx, 1));
        }
        
        if(i % 2 == 0){// 변경시키는 부분
            for(int j = 0; j < len;j++){
                inferTable = toggle(inferTable, idx+j);
            }
        }
    }
    tables.push_back(inferTable);
    if(onlyOne) return;
    inferenceTable(inferTable, newIdxAndLen);
}

string toggle(string table, int idx){
    if(table[idx] == 'A') table[idx] = 'B';
    else table[idx] = 'A';
    return table;
}