#include <iostream>
// random 생성용
#include <cstdlib>
#include <ctime>

using namespace std;

// index tree : 균형 이진 트리 가정하여 
// 최하위 depth에 원본 배열을 순차적으로 기록 
// 최상위 root 노드를 1번 index로 잡고 
// 구간 최대, 최소, 합 계산 시 사용 
// root를 1로 잡음으로써 부모 노드 계산 시 idx / 2 하면 됨

int *arr; // 원본 배열
int n; // 입력 개수 

int treeSize; // 전체 트리 개수 (n -> 2 * 2^gauss(log(n)) - 1 개 만큼 필요)
int leafSize; // 리프 노드 개수 (n -> 2^gauss(log(n)) 개 필요)

int *maxIndexTree;
int *minIndexTree;
int *sumIndexTree;

int maxINF = 987654321;
int minINF = -987654321;

void init() {
    n = 20; 
    arr = new int[n];
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    treeSize = 63;
    leafSize = 32;

    maxIndexTree = new int[treeSize + 1]; // index 1부터 시작 
    minIndexTree = new int[treeSize + 1];
    sumIndexTree = new int[treeSize + 1];

    for(int i = 0; i < treeSize + 1; i++) {
        maxIndexTree[i] = minINF;
        minIndexTree[i] = maxINF;
        sumIndexTree[i] = 0;
    }
}

void updateMaxIndexTree(int idx) {
    // idx : 원본 배열의 index (0부터 시작)
    int treeIdx = leafSize + idx;
    int num = arr[idx];
    maxIndexTree[treeIdx] = num;

    while(treeIdx > 0) {
        if(maxIndexTree[treeIdx] < num) maxIndexTree[treeIdx] = num;
        treeIdx /= 2;
    }
}

int getMaxNumInRange(int left, int right) {
    int startIdx = leafSize + left;
    int endIdx = leafSize + right;

    int res = minINF;

    while(startIdx <= endIdx) {
        if(startIdx % 2 == 0) startIdx /= 2;
        else {
            if(res < maxIndexTree[startIdx]) res = maxIndexTree[startIdx];
            startIdx = (startIdx + 1) / 2;
        }

        if(endIdx % 2 == 0) {
            if(res < maxIndexTree[endIdx]) res = maxIndexTree[endIdx];
            endIdx = (endIdx - 1) / 2;
        }
        else endIdx /= 2;
    }

    return res;
}

void updateMinIndexTree(int idx) {
    // idx : 원본 배열의 index (0부터 시작)
    int treeIdx = leafSize + idx;
    int num = arr[idx];
    minIndexTree[treeIdx] = num;

    while(treeIdx > 0) {
        if(minIndexTree[treeIdx] > num) minIndexTree[treeIdx] = num;
        treeIdx /= 2;
    }
}

int getMinNumInRange(int left, int right) {
    int startIdx = leafSize + left;
    int endIdx = leafSize + right;

    int res = maxINF;

    while(startIdx <= endIdx) {
        if(startIdx % 2 == 0) startIdx /= 2;
        else {
            if(res > minIndexTree[startIdx]) res = minIndexTree[startIdx];
            startIdx = (startIdx + 1) / 2;
        }

        if(endIdx % 2 == 0) {
            if(res > minIndexTree[endIdx]) res = minIndexTree[endIdx];
            endIdx = (endIdx - 1) / 2;
        }
        else endIdx /= 2;
    }

    return res;
}

void updateSumIndexTree(int idx) {
    // idx : 원본 배열의 index (0부터 시작)
    int treeIdx = leafSize + idx;
    int num = arr[idx];
    sumIndexTree[treeIdx] = num;

    treeIdx /= 2;

    while(treeIdx > 0) {
        sumIndexTree[treeIdx] = sumIndexTree[2 * treeIdx] + sumIndexTree[2 * treeIdx + 1];
        treeIdx /= 2;
    }
}

int getSumNumInRange(int left, int right) {
    int startIdx = leafSize + left;
    int endIdx = leafSize + right;

    int res = 0;

    while(startIdx <= endIdx) {
        if(startIdx % 2 == 0) startIdx /= 2;
        else {
            res += sumIndexTree[startIdx];
            startIdx = (startIdx + 1) / 2;
        }

        if(endIdx % 2 == 0) {
            res += sumIndexTree[endIdx];
            endIdx = (endIdx - 1) / 2;
        }
        else endIdx /= 2;
    }

    return res;
}

int main() {
    srand((unsigned int)time(NULL));

    init();

    for(int i = 0; i < n; i++) cout << arr[i] << ' ';
    cout << '\n';

    for(int i = 0; i < n; i++) {
        updateMaxIndexTree(i);
        updateMinIndexTree(i);
        updateSumIndexTree(i);
    }

    cout << getMaxNumInRange(0, 9) << ' ' << getMaxNumInRange(10, 19) << '\n';
    cout << getMinNumInRange(0, 9) << ' ' << getMinNumInRange(10, 19) << '\n';
    cout << getSumNumInRange(0, 9) << ' ' << getSumNumInRange(10, 19) << '\n';
}