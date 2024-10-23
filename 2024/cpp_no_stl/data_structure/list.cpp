#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template <typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoubleLinkedList() {
        clear(tail);
    }

    void clear(Node<T>* node) {
        if(node != nullptr) {
            clear(node->prev);
            delete node;
        }
        size = 0;
        return;
    }

    bool empty() {
        return (tail == nullptr);
    }

    void push(T data) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if(empty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        size++;
        return;
    }

    void delete_node(Node<T>* node) {
        if(node == nullptr) return;

        if(node == head) {
            head = node->next;
            head->prev = nullptr;
            delete node;
            size--;
            return;
        }

        if(node == tail) {
            tail = node->prev;
            tail->next = nullptr;
            delete node;
            size--;
            return;
        }

        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;

        return;
    }

    Node<T>* move(int idx) {
        if(size == 0) return head;

        if(size <= idx) return tail;
        
        Node<T>* node = head;
        while(idx--) {
            node = node->next;
        }
        return node;
    }

    size_t get_size() {
        return size;
    }

    void print() {

        cout << "size : " << get_size() << '\n';
        cout << "empty : " << empty() << '\n';

        Node<T>* node = head;

        if(node == nullptr) {
            cout << "empty dll";
        }
        else {
            while(node != nullptr) {
                cout << node->data << ' ';
                node = node->next;
            }
        }
        cout << "\n-------\n";
        return;
    }
};

int main() {
    DoubleLinkedList<int> dll;
    dll.print();

    dll.push(1);
    dll.push(10);
    dll.push(20);
    dll.push(123);

    dll.print();

    Node<int>* node = new Node<int>();

    node = dll.move(2);
    dll.delete_node(node);
    dll.print();

    dll.push(456);
    node = dll.move(123);
    dll.delete_node(node);
    dll.print();

    dll.push(123123);
    node = dll.move(0);
    dll.delete_node(node);
    dll.print();
}