#include <iostream>

using namespace std;

// Trie 자료 구조 예시 
// alphabet 소문자만 있다고 가정 (필요 시, 대소문자, 숫자, 아스키 등으로 확장 가능)
// search 시, 단순히 전체 string 존재 여부가 아닌, 몇 번째까지 일치하는 prefix 있는 지 체크 
// 없는 경우 -1 리턴, prefix 일치하는 경우 일치하는 마지막 index 리턴 

const int SIZE = 26;

struct Node {
    Node* children[SIZE];
    bool isEnd; // 해당 노드가 끝인지 여부 

    Node() {
        for(int i = 0; i < SIZE; i++) {
            children[i] = nullptr;
        }
        isEnd = false;
    }
};

class Trie {
private:
    Node* root;

public: 
    Trie() {
        root = new Node();
        root->isEnd = false;
    }
    ~Trie() {
        clear(root);
    }

    void insert(char* s) {
        Node* node = root;

        while(*s != 0) {
            int idx = *s - 'a';

            // 새로 추가되는 자식 노드 
            if(node->children[idx] == nullptr) {
                node->children[idx] = new Node();
            }

            node = node->children[idx];
            s++;
        }

        node->isEnd = true;
    }

    int search(char* s) {
        Node* node = root;

        int len = 0;
        while(*s != 0) {
            int idx = *s - 'a';

            // 만나는 부분 없을 때 현재까지 체크된 idx - 1 리턴 (idx - 1번째까지 일치)
            // 처음부터 없으면 -1 리턴
            if(node->children[idx] == nullptr) {
                return len - 1;
            }

            node = node->children[idx];
            len++;
            s++;
        }

        // 다 일치하는 경우 
        return len - 1;
    }

    bool isRemoval(Node* node, char* s, int depth) {
        // s가 trie 안에 있으면 삭제 
        // 단, 자식 노드 존재하면 삭제하면 안 됨 (더 긴 게 저장된 것)

        if(node == nullptr) return false;

        if(s[depth] == 0) {
            // 문자열 끝 도달 
            // 더 이상 끝 아님 
            if(node->isEnd) node->isEnd = false;

            // 자식 노드 존재 시 메모리 해제 안 됨 
            for(int i = 0; i < SIZE; i++) {
                if(node->children[i] != nullptr) return false;
            }

            // s 탐색도 끝, 자식도 없음 : 메모리 해제 
            delete node;
            return true;
        }
        else {
            int idx = s[depth] - 'a';

            // 더 탐색 할 거 없음
            if(node->children[idx] == nullptr) return false;

            // 재귀로 자식 노드 처리 
            int deletedChild = isRemoval(node->children[idx], s, depth + 1);

            if(deletedChild) {
                // 자식 해제 완료
                // 배열 상 null 처리 
                node->children[idx] = nullptr;

                // (현재 노드가 리프) + (단어 끝 아님) : 메모리 해제 가능 
                if(node->isEnd == false) {
                    for(int i = 0; i < SIZE; i++) {
                        if(node->children[i] != nullptr) return false;
                    }

                    delete node;
                    return true;
                }
            }
        }

        return false;
    }

    void remove(char* s) {
        isRemoval(root, s, 0);
    }

    void clear(Node* node) {
        if(node == nullptr) return;
        for(int i = 0; i < SIZE; i++) {
            clear(node->children[i]);
        }
        delete node;
        return;
    }
};

int main() {
    Trie trie = Trie();

    char* s1 = "abcde";
    char* s2 = "abc";
    char* s3 = "bdec";
    char* s4 = "bdfghi";

    trie.insert(s1);
    trie.insert(s2);
    trie.insert(s3);
    trie.insert(s4);

    char* t1 = "ab";
    char* t2 = "ccc";
    char* t3 = "bdec";
    printf("t1 : %d\n", trie.search(t1));
    printf("t2 : %d\n", trie.search(t2));
    printf("t3 : %d\n", trie.search(t3));

    char* r1 = "abc";
    char* r2 = "de";
    char* r3 = "bdec";
    trie.remove(r1);
    trie.remove(r2);
    trie.remove(r3);

    printf("t1 : %d\n", trie.search(t1));
    printf("t2 : %d\n", trie.search(t2));
    printf("t3 : %d\n", trie.search(t3));
}