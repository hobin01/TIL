#include <iostream>

using namespace std;

// stack : push, pop, empty, size, clear, top

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class Stack {
private:
    Node<T>* _top;
    size_t _size;

public:
    Stack() : _top(nullptr), _size(0) {}
    ~Stack() {
        clear();
    }

    void push(T data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->next = _top;
        _top = newNode;
        ++_size;
    }

    T pop() {
        if(empty()) {
            cout << "pop error : Stack is empty!\n";
            return T();
        }

        T data = _top->data;
        Node<T>* tmp = _top;
        _top = _top->next;
        delete tmp;
        --_size;

        return data;
    }

    bool empty() {
        return _top == nullptr;
    }

    size_t size() {
        return _size;
    }

    T top() {
        if(empty()) {
            cout << "top error : Stack is empty!\n";
            return T();
        }

        return _top->data;
    }

    void clear() {
        while(!empty()) {
            pop();
        }
        _top = nullptr;
        _size = 0;
    }
};

int main() {
    Stack<int> stk;
    stk.push(1);
    stk.push(2);

    cout << "size : " << stk.size() << '\n';
    cout << "top : " << stk.top() << '\n';

    stk.pop();

    cout << "size : " << stk.size() << '\n';
    cout << "top : " << stk.top() << '\n';

    stk.pop();

    cout << "size : " << stk.size() << '\n';
    cout << "top : " << stk.top() << '\n';

    stk.pop();

    cout << "size : " << stk.size() << '\n';
    cout << "top : " << stk.top() << '\n';

    stk.push(4);
    stk.push(5);

    cout << "size : " << stk.size() << '\n';
    cout << "top : " << stk.top() << '\n';

    stk.pop();
    stk.push(6);

    cout << "size : " << stk.size() << '\n';
    cout << "top : " << stk.top() << '\n';

    stk.clear();

    cout << "size : " << stk.size() << '\n';
    cout << "top : " << stk.top() << '\n';

    stk.pop();

    cout << "size : " << stk.size() << '\n';
    cout << "top : " << stk.top() << '\n';
}