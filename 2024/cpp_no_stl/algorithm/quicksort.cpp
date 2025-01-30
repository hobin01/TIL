#include <iostream>
// random 생성용
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void quicksort(int arr[], int left, int right) {
    if(left >= right) return;

    int l = left;
    int r = right;
    int tmp;

    int pivot = arr[(l+r)/2];

    while(l <= r) {
        // 역순 : arr[l] > pivot, arr[r] < pivot 으로 변경
        while(arr[l] < pivot) l++;
        while(arr[r] > pivot) r--;
        
        if(l < r) {
            swap(arr[l], arr[r]);
            l++;
            r--;
        } else if (l == r) {
            l++;
            r--;
        }
    }

    quicksort(arr, left, r);
    quicksort(arr, l, right);
}

int main() {
    srand((unsigned int)time(NULL));
    clock_t start, end;

    int n = 1000;
    int* arr = new int[n];
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    start = clock();
    quicksort(arr, 0, n-1);
    end = clock();

    for(int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    
    cout << '\n' << (double)(end - start) << "clocks";
}