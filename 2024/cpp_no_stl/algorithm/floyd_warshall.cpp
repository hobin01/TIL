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

int dist[5][5];

void init() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            dist[i][j] = map[i][j];
        }
    }
}

void output() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }   
}

int min(int a, int b) {
    if(a > b) return b;
    return a;
}

void floyd_warshall() {
    for(int k = 0; k < 5; k++) {
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    init();
    floyd_warshall();
    output();
}