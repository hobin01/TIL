#include <iostream>

using namespace std;

// combination nCr 해당하는 것들 순차적으로 구하기 

int n;
int r;
int* nums;
int** result;
int* comb;

void init() {
    n = 10;
    r = 3;
    nums = new int[n];
    for(int i = 0; i < n; i++) nums[i] = i;

    // 10C3 = 120
    result = new int*[120];
    for(int i = 0; i < 120; i++) result[i] = new int[r];

    comb = new int[r];
    for(int i = 0; i < r; i++) comb[i] = 0;
}

void combination(int depth, int &idx, int start) {
    // 개수 다 채움
    if(depth == r) {
        for(int i = 0; i < r; i++) {
            result[idx][i] = comb[i];
        }
        idx++;
        return;
    }

    for(int i = start; i < n; i++) {
        comb[depth] = nums[i];
        combination(depth + 1, idx, i + 1);
    }
}

void output() {
    for(int i = 0; i < 120; i++) {
        for(int j = 0; j < r; j++) {
            cout << result[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    init();
    int depth = 0;
    int idx = 0;
    int start = 0;
    combination(depth, idx, start);
    output();
}
