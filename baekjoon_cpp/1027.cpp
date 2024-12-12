#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isVisible(const vector<int>& heights, int a, int b) {
    int n = heights.size();
    double slope = (double)(heights[b] - heights[a]) / (b - a);
    double intercept = heights[a] - slope * a;

    for (int i = min(a, b) + 1; i < max(a, b); ++i) {
        double y = slope * i + intercept;
        if (y <= heights[i]) return false; // 다른 빌딩이 선분을 막는 경우
    }
    return true;
}

int main() {
    int N;
    cin >> N;
    vector<int> heights(N);

    for (int i = 0; i < N; ++i) {
        cin >> heights[i];
    }

    int maxVisible = 0;

    for (int i = 0; i < N; ++i) {
        int visibleCount = 0;
        for (int j = 0; j < N; ++j) {
            if (i != j && isVisible(heights, i, j)) {
                visibleCount++;
            }
        }
        maxVisible = max(maxVisible, visibleCount);
    }

    cout << maxVisible << endl;

    return 0;
}
