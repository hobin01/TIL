#include <iostream>

using namespace std;

#define INF 987654321

int map[5][5] = {
    {0, 5, INF, INF, 9},
    {3, 0, 7, 1, INF},
    {2, 1, 0, 8, 1},
    {INF, 2, 8, 0, 5},
    {INF, INF, INF, 2, 0}
};

int dist[5];
bool visited[5];

void init() {
    for(int i = 0; i < 5; i++) {dist[i] = INF; visited[i] = false;}
}

void output(int idx) {
    cout << idx << " 기준 최단 거리\n";
    for(int i = 0; i < 5; i++) {
        int d = dist[i] == INF ? -1 : dist[i];
        cout << d << ' ';
    }
    cout << '\n';
}

int getMinNode() {
    int d = INF;
    int node = -1;
    for(int i = 0; i < 5; i++) {
        if(visited[i]) 
            continue;
        if(dist[i] < d) {
            node = i;
            d = dist[i];
        }
    }

    return node;
}

void dijkstra(int start) {
    // 초기 세팅 
    for(int i = 0; i < 5; i++) {
        dist[i] = map[start][i];
    }
    visited[start] = true;

    // 제일 짧은 거 반복하면서 고르면서 거리 업데이트 
    while(true) {
        int node = getMinNode();
        
        // 업데이트 완료 
        if(node == -1) break;

        // 선택된 제일 짧은 노드 방문 및 거리 업데이트
        visited[node] = true;

        for(int i = 0; i < 5; i++) {
            int nd = dist[node] + map[node][i];
            if(dist[i] > nd) {
                dist[i] = nd;
            }
        }
    }
}

int main() {
    for(int i = 0; i < 5; i++) {
        init();
        dijkstra(i);
        output(i);
    }
}