#include <iostream>

using namespace std;

template<typename T>
void swap_(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
class PriorityQueue {
    // 최대 힙 구조 (제일 큰 게 top)
    // top = heap[0]

private:
    T* _heap; // 힙 구조 배열 
    size_t _size; // 현재 크기
    size_t _cap; // capacity

    // 자식이 부모보다 크면 교체 
    void heapifyUp(int idx) {
        if(idx == 0)
            return;
        
        int parentIdx = (idx - 1) / 2;
        if(_heap[idx] > _heap[parentIdx]) {
            swap_(_heap[idx], _heap[parentIdx]);
            heapifyUp(parentIdx);
        }
    }

    // 부모보다 자식이 크면 교체 
    void heapifyDown(int idx) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int largest = idx;

        // 왼쪽 자식 있고, 부모보다 큰 경우 
        if(left < _size && _heap[left] > _heap[largest])
            largest = left;

        // 오른쪽 자식 있고, 최대값보다 큰 경우 
        if(right < _size && _heap[right] > _heap[largest])
            largest = right;

        // 현재 노드보다 큰 거 있는 경우 
        if(largest != idx) {
            swap_(_heap[idx], _heap[largest]);
            heapifyDown(largest);
        }
    }

    // 다 찬 경우, cap 2배로 증가
    void resize() {
        T* newHeap = new T[_cap * 2];

        for(int i = 0; i < _size; i++)
            newHeap[i] = _heap[i];

        delete[] _heap;
        _heap = newHeap;
        _cap *= 2;
    }

public:
    // 초기 cap 10으로 지정
    PriorityQueue() : _size(0), _cap(10) {
        _heap = new T[_cap];
    }

    // pq 해제 시 할당했던 메모리 전체 해제
    ~PriorityQueue() {
        delete[] _heap;
    }

    // pq 내 모든 원소 삭제
    void clear() {
        delete[] _heap;
        _size = 0;
        _cap = 10;

        _heap = new T[_cap];
    }

    // 원소 삽입 (최대 힙)
    void push(T val) {
        if(_size == _cap) {
            resize();
        }
        _heap[_size] = val;
        heapifyUp(_size);
        _size++;
    }

    // 원소 삭제 (top 제거)
    T pop() {
        if(_size == 0) {
            cout << "PQ is empty!!!\n";
            return T();
        }
        
        int maxVal = _heap[0];
        _heap[0] = _heap[_size - 1];
        _size--;
        heapifyDown(0);

        return maxVal;
    }

    // 최대값 반환 
    T top() {
        if(_size == 0) {
            cout << "PQ is empty!!!\n";
            return T();
        }
        
        return _heap[0];
    }

    // 큐 비었는 지 확인 
    bool empty() {
        return _size == 0;
    }

    // 큐 크기 확인 
    size_t size() {
        return _size;
    }
};

int main()
{
    PriorityQueue<int> pq;
    pq.push(10);
    pq.push(20);
    pq.push(5);
    pq.push(100);

    cout << "top : " << pq.top() << '\n';
    pq.pop();
    cout << "top : " << pq.top() << '\n';
    pq.pop();

    cout << "size : " << pq.size() << '\n';
    cout << "empty : " << pq.empty() << '\n';

    pq.clear();
    cout << "size : " << pq.size() << '\n';
    cout << "empty : " << pq.empty() << '\n';

    pq.pop();

    pq.push(100);
    pq.push(-123);
    cout << "top : " << pq.top() << '\n';
    pq.pop();
    cout << "top : " << pq.top() << '\n';
    pq.pop();
    cout << "top : " << pq.top() << '\n';
}