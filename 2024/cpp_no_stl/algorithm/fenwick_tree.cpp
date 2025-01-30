#include <iostream>
// random 생성용
#include <cstdlib>
#include <ctime>

using namespace std;

// fenwick tree
// index 1 부터 시작 
// tree 합을 저장하여 구간합 쿼리 최적화 
// 원본 배열과 동일한 크기의 메모리만 있으면 됨 (세그먼트 트리는 2n-1 개 필요)
// 최하위 1 비트 값을 더한 것이 다음 전달 index
// ex. 6 (00110) -> 6 + 2 (00010) = 8 (01000) -> 8 + 8 (01000) = 16 (10000)
// 최하위 1 비트 값 = idx & -idx (-i = ~i + 1)
// 6번째 값은 펜윅 트리의 6, 8, 16 번째 값에 추가되게 됨 
// 구간 합 : [l, r] sum = [1, r] sum - [1, l-1] sum

int *arr; // 원본 배열 
int n; // 개수 
int *fenwick; //펜윅 트리 

void init() {
    n = 10;
    arr = new int[n+1];
    fenwick = new int[n+1];

    for(int i = 1; i <= n; i++) {
        arr[i] = rand() % 100;
        fenwick[i] = 0;
    }
}

void add(int idx, int val) {
    while(idx <= n) {
        fenwick[idx] += val;
        idx += (idx & (~idx + 1)); // idx & -idx 해도 같음 
    }
}

void update(int idx, int val) {
    // idx 위치 값 val로 변경
    int diff = val - arr[idx];
    arr[idx] = val;
    // 모든 배열에 대해 갱신하는 것이 아닌, idx 위치 값 갱신되는 곳만 차이만큼 갱신 
    add(idx, diff);
}

int prefix_sum(int idx) {
    // [1, idx] sum 계산 
    int sum = 0;
    while(idx > 0) {
        sum += fenwick[idx];
        idx -= (idx & (~idx + 1));
    }
    return sum;
}

int range_sum(int left, int right) {
    // [left, right] sum 계산 
    return prefix_sum(right) - prefix_sum(left - 1);
}

int main() {
    srand((unsigned int)time(NULL));
    init();

    // 원본 확인 
    for(int i = 1; i <= n; i++) {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    // 펜윅 트리 생성
    for(int i = 1; i <= n; i++) {
        add(i, arr[i]);
    }

    // range sum 체크 
    int r1 = range_sum(1, 10);
    int r2 = range_sum(2, 9);
    int r3 = range_sum(3, 8);
    int r4 = range_sum(4, 7);
    int r5 = range_sum(5, 6);
    cout << r1 << ' ' << r2 << ' ' << r3 << ' ' << r4 << ' ' << r5 << '\n';

    // 값 업데이트
    update(1, 1);
    update(2, 2);
    update(10, 10);
    update(9, 9);

    // 원본 확인 
    for(int i = 1; i <= n; i++) {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    // range sum 체크 
    r1 = range_sum(1, 10);
    r2 = range_sum(2, 9);
    r3 = range_sum(3, 8);
    r4 = range_sum(4, 7);
    r5 = range_sum(5, 6);
    cout << r1 << ' ' << r2 << ' ' << r3 << ' ' << r4 << ' ' << r5 << '\n';
}