#include <iostream>

using namespace std;

// queue : push, pop, empty, size, clear, front, rear

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class Queue {
private: 
    Node<T>* _front;
    Node<T>* _rear;
    size_t _size;

public :
    Queue() : _front(nullptr), _rear(nullptr), _size(0) {}
    ~Queue() {
        clear();
    }

    void push(T data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = nullptr;

        if(empty()) {
            _front = newNode;
            _rear = newNode;
        } else {
            _rear->next = newNode;
            _rear = newNode;
        }

        ++_size;
    }

    T pop() {
        if(empty()) {
            cout << "pop error : Queue is empty!\n";
            return T();
        }

        T data = _front->data;
        Node<T>* tmp = _front;
        _front = _front->next;

        if(_front == nullptr) {
            _rear = nullptr;
        }

        delete tmp;
        --_size;

        return data;
    }

    bool empty() {
        return _front == nullptr;
    }

    size_t size() {
        return _size;
    }

    void clear() {
        while(!empty()) {
            pop();
        }
    }

    T front() {
        if(empty()) {
            cout << "front error : Queue is empty!\n";
            return T();
        }
        return _front->data;
    }

    T rear() {
        if(empty()) {
            cout << "rear error : Queue is empty!\n";
            return T();
        }
        return _rear->data;
    }
};

int main() {
    Queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    cout << "size : " << q.size() << '\n';
    cout << "front : " << q.front() << '\n';
    cout << "rear : " << q.rear() << '\n';

    q.pop();

    cout << "size : " << q.size() << '\n';
    cout << "front : " << q.front() << '\n';
    cout << "rear : " << q.rear() << '\n';

    q.pop();

    cout << "size : " << q.size() << '\n';
    cout << "front : " << q.front() << '\n';
    cout << "rear : " << q.rear() << '\n';

    q.pop();

    cout << "size : " << q.size() << '\n';
    cout << "front : " << q.front() << '\n';
    cout << "rear : " << q.rear() << '\n';

    q.pop();

    cout << "size : " << q.size() << '\n';
    cout << "front : " << q.front() << '\n';
    cout << "rear : " << q.rear() << '\n';

    q.push(4);
    q.push(5);

    cout << "size : " << q.size() << '\n';
    cout << "front : " << q.front() << '\n';
    cout << "rear : " << q.rear() << '\n';

    q.clear();

    cout << "size : " << q.size() << '\n';
    cout << "front : " << q.front() << '\n';
    cout << "rear : " << q.rear() << '\n';

    q.push(6);

    cout << "size : " << q.size() << '\n';
    cout << "front : " << q.front() << '\n';
    cout << "rear : " << q.rear() << '\n';
}

/*
simple version

#define SIZE 1 << 16

int front = 0;
int rear = -1;
int size = 0;
int queue[SIZE] = {0, };

void push(int val) {
    rear = (rear + 1) % SIZE;
    queue[rear] = val;
    size++;
}

int pop() {
    if(size == 0)
        return -1;
    
    int res = queue[front];
    front = (front + 1) % SIZE;
    size--;
    return res;
}

int peek() {
    if(size == 0)
        return -1;
    return queue[front];
}

bool empty() {
    return size == 0;
}
*/