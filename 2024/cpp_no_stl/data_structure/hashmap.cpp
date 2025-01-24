#include <iostream>

using namespace std;

// 간단한 해시맵 구조 
// 해시 키를 기준으로 동일 키 값들을 체이닝 (정확한 의미의 해시맵은 아님)
// 키는 char* 가정 (상황에 따라 적절한 해싱 필요)
// char* 기준으로 ascii 값 모두 더 한 뒤 % cap 한 걸 key로 잡음 
// cap : 키 최대 개수
// Node : key, value 갖고 있으며, 이전, 다음 Node 어딘지 가짐 

struct Node {
    char* key;
    char* val;
    Node* prev;
    Node* next;
};

bool strcmp(char* s1, char* s2) {
    while(*s1 != 0 && *s2 != 0) {
        if(*s1 != *s2) return false;
        s1++;
        s2++;
    }

    if(*s1 != 0 || *s2 != 0) return false;

    return true;
}

class HashMap {
private :
    Node** map;
    int cap;

public : 
    HashMap(int capacity) {
        map = new Node*[capacity];
        cap = capacity;
    }
    ~HashMap() {
        // 연결된 모든 거 해제
        for(int i = 0; i < cap; i++) {
            Node* node = map[i];
            while(node != nullptr) {
                Node* next = node->next;
                delete node;
                node = next;
            }
        }
        // 선언했던 배열 자체 해제 
        delete[] map;
        cap = 0;
    }

    int hashing(char* key) {
        int sum = 0;
        while(*key != 0) {
            sum += *(key++);
        }
        return sum % cap;
    }

    void push(char* key, char* val) {
        Node* node = new Node();
        node->key = key;
        node->val = val;
        node->prev = nullptr;
        node->next = nullptr;

        int idx = hashing(key);
        Node* head = map[idx];

        if(head == nullptr) {
            // 처음인 케이스 
            map[idx] = node;
            return;
        }

        Node* cur = head;
        while(cur->next != nullptr) {
            cur = cur->next;
        }
        node->prev = cur;
        cur->next = node;
        return;
    }

    Node* get(char* key) {
        int idx = hashing(key);

        if(map[idx] == nullptr) {
            printf("There is no related key.");
            return nullptr;
        }

        return map[idx];
    }

    void remove(char* key, char* val) {
        int idx = hashing(key);
        Node* head = map[idx];
        Node* target = nullptr;

        if(head == nullptr) {
            printf("There is no related key.\n");
            return;
        }

        Node* cur = head;
        while(cur != nullptr) {
            if(strcmp(cur->val, val)) {
                target = cur;
            }
            cur = cur->next;
        }

        if(target == nullptr) {
            printf("There is no related val.\n");
            return;
        }

        Node* prev = target->prev;
        Node* next = target->next;

        // 1개만 있던 경우 
        if(prev == nullptr && next == nullptr) {
            map[idx] = nullptr;
        }
        // head였던 경우 
        else if(prev == nullptr) {
            map[idx] = next;
        }
        // tail였던 경우 
        else if(next == nullptr) {
            prev->next = nullptr;
        }
        else {
            prev->next = next;
            next->prev = prev;
        }

        delete target;

        return;
    }
};

int main() {
    int cap = 1000000;
    HashMap map = HashMap(cap);

    char* k1 = "k1";
    char* v10 = "v10";
    char* v11 = "v11";
    map.push(k1, v10);
    map.push(k1, v11);

    char* k2 = "k2";
    char* v20 = "v20";
    char* v21 = "v21";
    char* v22 = "v22";
    map.push(k2, v20);
    map.push(k2, v21);
    map.push(k2, v22);

    char* k3 = "k3";
    char* v30 = "v30";
    char* v31 = "v31";
    map.push(k3, v30);
    map.push(k3, v31);

    char* k4 = "k4";

    char* j2 = "j2"; // 합하면 k1이랑 동일 
    Node* head = map.get(j2);

    while(head != nullptr) {
        printf("%s : %s \n", head->key, head->val);
        head = head->next;
    }

    map.remove(k2, v20);

    head = map.get(k2);

    while(head != nullptr) {
        printf("%s : %s \n", head->key, head->val);
        head = head->next;
    }

    head = map.get(k3);

    while(head != nullptr) {
        printf("%s : %s \n", head->key, head->val);
        head = head->next;
    }

    head = map.get(k4);

    while(head != nullptr) {
        printf("%s : %s \n", head->key, head->val);
        head = head->next;
    }
}