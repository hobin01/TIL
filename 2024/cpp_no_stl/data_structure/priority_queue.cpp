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
        int* newHeap = new int[_cap * 2];

        for(int i = 0; i < _size; i++)
            newHeap[i] = _heap[i];

        delete[] _heap;
        _heap = newHeap;
        _cap *= 2;
    }

public:
}

int main()
{

}