// 실제 시험장에서 class 만들고 처리하기는 너무 오래 걸림
// 현실적으로 가능한 버전 (단순 배열 이용)
// stack, queue, pq 정도가 현실성 있음

#include <stdio.h>

#define MAX_SIZE 100

// 1. stack
struct Stack {
    int data[MAX_SIZE];
    int size;

    Stack() {
        for(int i = 0; i < MAX_SIZE; i++) data[i] = 0;
        size = 0; 
    }
};

void push(Stack &stk, int val) {
    stk.data[stk.size++] = val;
}

void pop(Stack &stk) {
    if(stk.size == 0) return;
    stk.data[--stk.size] = 0;
}

int top(Stack &stk) {
    if(stk.size == 0) return -1;
    return stk.data[stk.size - 1];
}

void print(Stack &stk) {
    printf("stack : ");
    for(int i = stk.size - 1; i >= 0; i--) {
        printf("%d ", stk.data[i]);
    }
    printf("\n");
}

// 2. queue
struct Queue {
    int data[MAX_SIZE];
    int size;
    int front; // 첫 번째 index 
    int rear; // 마지막 index + 1

    Queue() {
        for(int i = 0; i < MAX_SIZE; i++) data[i] = 0;
        size = 0;
        front = 0;
        rear = 0;
    }
};

void push(Queue &q, int val) {
    q.data[q.rear] = val;
    q.rear = (q.rear + 1) % MAX_SIZE;
    q.size++;
}

void pop(Queue &q) {
    if(q.size == 0) return;
    q.data[q.front] = 0;
    q.front = (q.front + 1) % MAX_SIZE;
    q.size--;
}

int front(Queue &q) {
    if(q.size == 0) return -1;
    return q.data[q.front];
}

void print(Queue &q) {
    printf("queue : ");
    for(int i = 0; i < q.size; i++) {
        printf("%d ", q.data[(q.front + i) % MAX_SIZE]);
    }
    printf("\n");
}

// 3. pq 
struct PQ {
    int data[MAX_SIZE];
    int size;

    PQ() {
        for(int i = 0; i < MAX_SIZE; i++) data[i] = 0;
        size = 0;
    }
};

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void push(PQ &pq, int val) {
    // min heap 기준 
    // left, right은 상관없고, parent가 더 작으면 됨 

    int i = pq.size;
    pq.data[i] = val;
    pq.size++;

    int parent;
    while(i > 0) {
        parent = (i - 1) / 2;
        if(pq.data[parent] <= pq.data[i]) break; // max-heap : >= 
        swap(pq.data[parent], pq.data[i]);
        i = parent;
    }
}

void pop(PQ &pq) {
    if(pq.size == 0) return;
    // 0번째 거랑 맨 마지막 거 swap 
    // left, right 중 parent보다 작은 거 업데이트 (swap)
    // 최종적으로 parent < (left, right) 되도록 

    pq.data[0] = pq.data[--pq.size];

    int i = 0;
    int left, right, smallest;
    while(true) {
        left = i * 2 + 1;
        right = i * 2 + 2;
        smallest = i;

        // max-heap : data : > 
        if((left < pq.size) && (pq.data[left] < pq.data[smallest])) smallest = left;
        if((right < pq.size) && (pq.data[right] < pq.data[smallest])) smallest = right;

        // 업데이트되는 거 없음
        if(smallest == i) break;
        swap(pq.data[i], pq.data[smallest]);
        i = smallest;
    }
}

int top(PQ &pq) {
    if(pq.size == 0) return -1;
    return pq.data[0];
}

void print(PQ &pq) {
    printf("pq : ");
    for(int i = 0; i < pq.size; i++) {
        printf("%d ", pq.data[i]);
    }
    printf("\n");
}

int main() {
    //////// stack test
    Stack stk;

    push(stk, 1);
    push(stk, 2);
    push(stk, 3);
    print(stk);

    pop(stk);
    pop(stk);
    print(stk);

    printf("top : %d\n", top(stk));

    push(stk, 123);
    print(stk);

    pop(stk);
    pop(stk);
    printf("top : %d\n", top(stk));

    ///////////// queue test
    Queue q;
    
    push(q, 1);
    push(q, 2);
    push(q, 3);
    print(q);

    pop(q);
    pop(q);
    print(q);

    printf("front : %d\n", front(q));

    push(q, 123);
    print(q);

    pop(q);
    pop(q);
    printf("front : %d\n", front(q));

    /////////////// pq test
    PQ pq;

    push(pq, 3);
    push(pq, 2);
    push(pq, 1);
    push(pq, 4);
    push(pq, 5);
    print(pq);

    pop(pq);
    pop(pq);
    pop(pq);
    print(pq);

    printf("top : %d\n", top(pq));

    push(pq, 1);
    push(pq, 2);
    print(pq);

    push(pq, 3);
    print(pq);

    pop(pq);
    pop(pq);
    printf("top : %d\n", top(pq));

    pop(pq);
    pop(pq);
    pop(pq);
    printf("top : %d\n", top(pq));
}