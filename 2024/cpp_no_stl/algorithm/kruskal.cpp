#include <iostream>

using namespace std;

// MST : edge 가중치 최소인 걸로 구성된 tree
// kruskal : edge 가중치 순으로 정렬 후
// cycle 유무에 따라 (union-find) 이을 지 결절
// 복잡도 : O(E log E)

// -1 : edge 없는 거 
// MST 계산용 무향 그래프
int graph[7][7] = {
	{0, 29, -1, -1, -1, 10, -1},
	{29, 0, 16, -1, -1, -1, 15},
	{-1, 16, 0, 12, -1, -1, -1},
	{-1, -1, 12, 0, 22, -1, 18},
	{-1, -1, -1, 22, 0, 27, 25},
	{10, -1, -1, -1, 27, 0, -1},
	{-1, 15, -1, 18, 25, -1, 0}
};

struct edge {
    int node1;
    int node2;
    int dist;
};

int parents[7];
edge *edges;
int edgesSize;

edge *result;
int sum;
int mstSize;

int compare(edge &e1, edge &e2) {
    // dist 크면 1, 작으면 -1, 같으면 0 
    if(e1.dist > e2.dist) return 1;
    else if(e1.dist < e2.dist) return -1;
    return 0;
}

void quick_sort(edge *arr, int left, int right) {
    if(left >= right) return;

    int l = left;
    int r = right;
    edge tmp;

    edge pivot = arr[(l + r) / 2];

    while(l <= r) {
        while(compare(arr[l], pivot) == -1) l++;
        while(compare(arr[r], pivot) == 1) r--;

        if(l < r) {
            // pivot 기준으로 바꿔야 할 값들
            edge tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            l++;
            r--;
        }
        else if(l == r) {
            l++;
            r--;
        }
    }

    quick_sort(arr, left, r);
    quick_sort(arr, l, right);
}

int find_parent(int node, int *parent) {
    if(node == parent[node]) return node; 
    parent[node] = find_parent(parent[node], parent);
    return parent[node];
}

bool union_nodes(int node1, int node2, int *parent) {
    int parent1 = find_parent(node1, parent);
    int parent2 = find_parent(node2, parent);

    // cycle 생성
    if(parent1 == parent2) 
        return false;

    // 작은 값 부모로 지정 
    else if(parent1 < parent2) {
        parent[parent2] = parent1;
    } else {
        parent[parent1] = parent2;
    }
    return true;
}

void kruskal() {
    // edge 정렬 
    quick_sort(edges, 0, edgesSize - 1);

    int idx = 0;
    for(int i = 0; i < edgesSize; i++) {
        int node1 = edges[i].node1;
        int node2 = edges[i].node2;
        int dist = edges[i].dist;

        bool notCycle = union_nodes(node1, node2, parents);
        if(notCycle) {
            result[idx] = {node1, node2, dist};
            sum += dist;
            idx++;
        }
    }

    mstSize = idx;
}

void init() {
    // parent 자신으로 초기화 
    for(int i = 0; i < 7; i++) {
        parents[i] = i;
    }

    // edges, result 초기화 
    edges = new edge[50];
    result = new edge[50];
    for(int i = 0; i < 50; i++) {
        edges[i] = {-1, -1, -1};
        result[i] = {-1, -1, -1};
    }

    // edge 추가 
    int idx = 0;
    for(int i = 0; i < 7; i++) {
        for(int j = i + 1; j < 7; j++) {
            if(graph[i][j] > 0) {
                edges[idx] = {i, j, graph[i][j]};
                idx++;
            }
        }
    }

    edgesSize = idx;
    sum = 0;
    mstSize = 0;
}

void output() {
    cout << "MST (node1 node2 weight)\n";
    for(int i = 0; i < mstSize; i++) {
        cout << result[i].node1 << ' ' << result[i].node2 << ' ' << result[i].dist << '\n';
    }

    cout << "Weights : " << sum;
}

int main() {
    init();
    kruskal();
    output();
}