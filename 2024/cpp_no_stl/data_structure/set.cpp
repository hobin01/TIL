#include <iostream>

using namespace std;

template<typename K>
struct Node {
    K key;
    Node* left;
    Node* right;
};

template<typename K>
class Set {
private:
    Node<K>* root;
    size_t _size;

    // 노드 삽입 (key 작은 거 왼쪽, 큰 거 오른 쪽)
    Node<K>* _insert(Node<K>* node, K key) {
        if(node == nullptr) {
            Node<K>* newNode = new Node<K>();
            newNode->key = key;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }

        if(key < node->key) {
            node->left = _insert(node->left, key);
        } else if(key > node->key) {
            node->right = _insert(node->right, key);
        }
        return node;
    }

    // 노드 검색
    Node<K>* _find(Node<K>* node, K key) {
        if(node == nullptr || node->key == key)
            return node;
        
        if(key < node->key)
            return _find(node->left, key);
        else 
            return _find(node->right, key);
    }

    // 노드 삭제
    Node<K>* _erase(Node<K>* node, K key) {
        if(node == nullptr)
            return nullptr;

        if(key < node->key) {
            node->left = _erase(node->left, key);
        } 
        else if(key > node->key) {
            node->right = _erase(node->right, key);
        } 
        else {
            // 삭제할 거 찾음
            if(node->left == nullptr) {
                Node<K>* tmp = node->right;
                delete node;
                return tmp;
            } 
            else if(node->right == nullptr) {
                Node<K>* tmp = node->left;
                delete node;
                return tmp;
            } 
            else {
                Node<K>* tmp = _minValNode(node->right);
                node->key = tmp->key;
                node->right = _erase(node->right, tmp->key);
            }
        }
        return node;
    }

    Node<K>* _minValNode(Node<K>* node) {
        // 자식 노드 중 제일 작은 거 찾기
        Node<K>* cur = node;
        while(cur && cur->left != nullptr)
            cur = cur->left;
        return cur;
    }

public:
    Set() : root(nullptr), _size(0) {}
    ~Set() {
        clear(root);
    }

    void clear(Node<K>* node) {
        if(node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
        _size = 0;
    }

    void insert(K key) {
        root = _insert(root, key);
        _size++;
    }

    bool find(K key) {
        Node<K>* node = _find(root, key);
        if(node != nullptr) {
            return true;
        }

        cout << "key : " << key << " does not exist!!!\n";
        return false;
    }

    void erase(K key) {
        root = _erase(root, key);

        _size--;
        if(_size < 0)
            _size = 0;
    }

    bool empty() {
        return root == nullptr;
    }

    size_t size() {
        return _size;
    }
};

int main() 
{
    Set<int> m;
    m.insert(1);
    m.insert(2);
    m.insert(3);

    bool val = m.find(1);
    cout << val << '\n';
    m.find(2);
    cout << val << '\n';
    m.find(3);
    cout << val << '\n';
    m.find(4);
    cout << val << '\n';

    m.erase(1);
    m.erase(2);
    cout << m.size() << '\n';

    m.erase(3);
    cout << m.size() << '\n';
    cout << m.empty() << '\n';
}