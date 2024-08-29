#include <iostream>
using namespace std;

template <typename T>

class Vector {
private:
    T* data; // 실제 데이터 저장
    size_t sz; // 현재 사이즈
    size_t cap; // 현재 capacity

public:
    // 생성자
    Vector() : data(nullptr), sz(0), cap(0) {}

    // 소멸자
    ~Vector() {
        delete[] data;
    }

    void resize(size_t newCap) {
        // 새 데이터 메모리 할당 및 복사
        T* newData = new T[newCap];
        for(size_t i = 0; i < sz; i++)
            newData[i] = data[i];
        
        // 기존 메모리 해제 후 새 메모리 포인터에 연결
        delete[] data;
        data = newData;

        // capacity 업데이트
        cap = newCap;
    }

    void push_back(const T& val) {
        // cap 부족하면 2배로 늘리기
        if(sz == cap) {
            resize(cap == 0 ? 1 : cap * 2);
        }
        data[sz++] = val;
    }

    void pop_back() {
        // 요소 제거 
        // sz만 줄여도 실제 접근 시 sz 이상으로 접근 못함
        if(sz > 0)
            --sz;
    }

    T& operator[](size_t index) {
        // [] 오버라이딩
        static T dummy;
        if(index >= sz) {
            cout << "index out of range : " << "input : " << index << ", vector size : " << sz << '\n';
            return dummy;
        }
        return data[index];
    }

    Vector& operator=(const Vector& vec) {
        // = 오버라이딩
        if(this == &vec)
            return *this;
        
        delete[] data;

        sz = vec.sz;
        cap = vec.cap;
        data = new T[cap];
        for(size_t i = 0; i < sz; i++)
            data[i] = vec.data[i];
        
        return *this;
    }

    size_t size() const {
        // 현재 size 리턴
        return sz;
    }

    size_t capacity() const {
        // 현재 capacity 리턴 
        return cap;
    }
};

void printVec(Vector<int>& vec)
{
    cout << "size : " << vec.size() << '\n';
    cout << "capacity : " << vec.capacity() << '\n';

    for(size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
}

int main()
{
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    printVec(vec);

    vec.pop_back();
    vec.pop_back();

    printVec(vec);

    vec.resize(vec.size() * 2);

    printVec(vec);

    Vector<int> vec2;
    vec2.push_back(1);
    vec2.push_back(2);
    vec2.push_back(3);

    vec = vec2;

    printVec(vec);
}