#include <iostream>

using namespace std;

// permutation nPr 해당하는 것들 순차적으로 구하기 

int n;
int r;
int* nums;
int** result;
bool* visited;
int* perm;

void init() {
    n = 10;
    r = 3;
    nums = new int[n];
    for(int i = 0; i < n; i++) nums[i] = i;

    // 10P3 = 720
    result = new int*[720];
    for(int i = 0; i < 720; i++) result[i] = new int[r];

    visited = new bool[n];
    for(int i = 0; i < n; i++) visited[i] = false;

    perm = new int[r];
    for(int i = 0; i < r; i++) perm[i] = 0;
}

void permutation(int depth, int &idx) {
    // 개수 다 채움
    if(depth == r) {
        for(int i = 0; i < r; i++) {
            result[idx][i] = perm[i];
        }
        idx++;
        return;
    }

    for(int i = 0; i < n; i++) {
        if(visited[i]) continue;

        visited[i] = true;
        perm[depth] = nums[i];
        permutation(depth + 1, idx);
        visited[i] = false;
    }
}

void output() {
    for(int i = 0; i < 720; i++) {
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
    permutation(depth, idx);
    output();
}
