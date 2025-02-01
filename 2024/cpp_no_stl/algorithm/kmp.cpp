#include <iostream>

using namespace std;

struct Node {
    // 단순 int 저장용 
    int val;
    Node* next;

    Node() {
        val = 0;
        next = nullptr;
    }
};

class List {
    // 단방향 리스트 (단순 저장용)
private:
    Node* head;
    Node* tail;
    int size;

public:
    List() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~List() {
        while(head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    void push(int val) {
        Node* node = new Node();
        node->val = val;

        if(head == nullptr) {
            head = node;
            tail = node;
            size++;
            return;
        } 

        tail->next = node;
        tail = node;
        size++;
    }

    int getSize() {
        return size;
    }

    void print() {
        Node* node = head;
        while(node != nullptr) {
            cout << node->val << ' ';
            node = node->next;
        }
        cout << '\n';
    }
};

int strlen(char* str) {
    int idx = 0;
    while(*(str + idx) != 0) idx++;
    return idx;
}

int* getPi(char* pattern) {

    int patternLen = strlen(pattern);

    int* pi = new int[patternLen];
    for(int i = 0; i < patternLen; i++) pi[i] = 0;

    int i = 1; // 패턴의 탐색 위치
    int len = 0; // 현재 체크된 길이 

    while(i < patternLen) {
        // 체크된 prefix, suffix 일치하는 경우, 저장 및 체크 길이 증가 
        if(pattern[i] == pattern[len]) pi[i++] = ++len;
        else {
            // 일치 안 하는 경우, 이전에 체크 길이로 복귀
            if(len != 0) len = pi[len - 1];
            // 전부 일치 안하면 일치하는 prefix, suffix 없으므로 0 저장 및 인덱스 증가 
            else pi[i++] = 0;
        }
    }

    return pi;
}

List* kmp(char* text, char* pattern) {
    int textLen = strlen(text);
    int patternLen = strlen(pattern);

    int i = 0; // text index
    int j = 0; // pattern index

    int* pi = getPi(pattern); // prefix, suffix 일치하는 길이 계산된 pi 배열 

    List* result = new List(); // 단순 결과 저장용 

    while(i < textLen) {
        // 패턴 중 일부와 일치하는 경우
        if(text[i] == pattern[j]) {
            i++;
            j++;
        }

        // 패턴 전체와 일치
        // result 추가 및 이전 prefix, suffix 일치하는 부분으로 옮김
        if(j == patternLen) {
            result->push(i - j);
            j = pi[j - 1];
        }
        // 패턴과 다른 부분 발생 
        // prefix, suffix 일치하는 부분으로 이동 / 없으면 인덱스 증가 
        else if((i < textLen) && (text[i] != pattern[j])) {
            if(j != 0) j = pi[j - 1];
            else i++;
        }
    }

    return result;
}

int main() {
    char* text1 = "abcdefg hijklmn abcdefg hijklmn abcdefg hijklmn";
    char* text2 = "";
    char* text3 = "aaaaaaaaaa";

    char* pattern1 = "abc";
    char* pattern2 = "hij";
    char* pattern3 = "a";
    char* pattern4 = "aaa";

    List* result;
    
    result = kmp(text1, pattern1);
    result->print();
    delete result;

    result = kmp(text1, pattern2);
    result->print();
    delete result;

    result = kmp(text2, pattern3);
    result->print();
    delete result;

    result = kmp(text3, pattern3);
    result->print();
    delete result;

    result = kmp(text3, pattern4);
    result->print();
    delete result;
}