#include <iostream>
// sort 용
#include <algorithm>
// random 생성용
#include <cstdlib>
#include <ctime>

using namespace std;

int binarysearch(int arr[], int len, int target) {
    // arr 오름차순 가정 
    // arr[0:len] 대상으로 binary search
    // target 있는 경우 : 가장 첫 번째 등장하는 index 리턴
    // target 없는 경우 : target보다 작은 값 중 가장 큰 값의 index+1 리턴 

    int left = 0;
    int right = len;
    int mid, res;

    if(arr[0] > target) {
        res = 0;
        return res;
    }
    if(arr[len-1] < target) {
        res = len;
        return res;
    }

    while(left < right) {
        mid = (left + right) / 2;
        if(arr[mid] < target)
            left = mid + 1;
        // 같은 값이어도 최대한 앞으로
        else
            right = mid; 
    }

    res = right;
    return res;
}

int main()
{
    srand((unsigned int)time(NULL));
    clock_t start, end;

    start = clock();
    int n = 20;
    int* arr = new int[n];
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    sort(arr, arr + n);
    for(int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    int res;
    start = clock();
    res = binarysearch(arr, n, 50);
    end = clock();
    
    cout << res << '\n';
    cout << (double)(end - start) << "clocks" << '\n';

    start = clock();
    res = binarysearch(arr + 10, n - 10, 50);
    end = clock();

    cout << res << '\n';
    cout << (double)(end - start) << "clocks" << '\n';
}