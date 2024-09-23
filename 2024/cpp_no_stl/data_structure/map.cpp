#include <iostream>

using namespace std;

template<typename K, typename V>
struct Node {
    K key;
    V val;
    Node* left;
    Node* right;
};

template<typename K, typename V>
class Map {
private:
    Node<K, V>* root;
    size_t _size;

    // 노드 삽입 (key 작은 거 왼쪽, 큰 거 오른 쪽)
    Node<K, V>* _insert(Node<K, V>* node, K key, V val) {
        if(node == nullptr) {
            Node<K, V>* newNode = new Node<K, V>();
            newNode->key = key;
            newNode->val = val;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }

        if(key < node->key) {
            node->left = _insert(node->left, key, val);
        } else if(key > node->key) {
            node->right = _insert(node->right, key, val);
        } else {
            // key 존재하는 경우 val 업데이트
            node->val = val;
        }
        return node;
    }

    // 노드 검색
    Node<K, V>* _find(Node<K, V>* node, K key) {
        if(node == nullptr || node->key == key)
            return node;
        
        if(key < node->key)
            return _find(node->left, key);
        else 
            return _find(node->right, key);
    }

    // 노드 삭제
    Node<K, V>* _erase(Node<K, V>* node, K key) {
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
                Node<K, V>* tmp = node->right;
                delete node;
                return tmp;
            } 
            else if(node->right == nullptr) {
                Node<K, V>* tmp = node->left;
                delete node;
                return tmp;
            } 
            else {
                Node<K, V>* tmp = _minValNode(node->right);
                node->key = tmp->key;
                node->val = tmp->val;
                node->right = _erase(node->right, tmp->key);
            }
        }
        return node;
    }

    Node<K, V>* _minValNode(Node<K, V>* node) {
        // 자식 노드 중 제일 작은 거 찾기
        Node<K, V>* cur = node;
        while(cur && cur->left != nullptr)
            cur = cur->left;
        return cur;
    }

public:
    Map() : root(nullptr), _size(0) {}
    ~Map() {
        clear(root);
    }

    void clear(Node<K, V>* node) {
        if(node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
        _size = 0;
    }

    void insert(K key, V val) {
        root = _insert(root, key, val);
        _size++;
    }

    bool find(K key, V& val) {
        Node<K, V>* node = _find(root, key);
        if(node != nullptr) {
            val = node->val;
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
    Map<int, int> m;
    m.insert(1, 11);
    m.insert(2, 22);
    m.insert(3, 33);

    int val;
    m.find(1, val);
    cout << val << '\n';
    m.find(2, val);
    cout << val << '\n';
    m.find(3, val);
    cout << val << '\n';
    m.find(4, val);
    cout << val << '\n';

    m.erase(1);
    m.erase(2);
    cout << m.size() << '\n';

    m.erase(3);
    cout << m.size() << '\n';
    cout << m.empty() << '\n';
}