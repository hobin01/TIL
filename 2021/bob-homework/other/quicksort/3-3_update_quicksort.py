# 랜덤한 리스트 (100만개 원소) 오름차순 (ex. 1 2 3 4 5) 정렬 퀵소트
# 업그레이드 버전

import time # 시간 측정
import psutil # 메모리 측정
import os 
import csv # csv 파일 읽기

# 중간값 구하기
def MidNum(List, a, b, c):
    num1 = List[a]
    num2 = List[b]
    num3 = List[c]
    if ((num2 > num1) and (num1 > num3)) or ((num3 > num1) and (num1 > num2)):
        return a
    elif ((num1 > num2) and (num2 > num3)) or ((num3 > num2) and (num2 > num1)):
        return b
    else:
        return c

# partition 하는 함수
def PartitionAndMakePivot(List, left, right):
    # List - 정렬하고자하는 리스트
    # left - List의 가장 왼쪽 index
    # right - List의 가장 오른쪽 index (전체 리스트 기준)
    # low, high 역전하는 지점에서 끝 (더 이상 정렬할 것 없음)
    low = left + 1
    high = right
    
    # 정렬하고자 하는 List의 맨 끝 두 원소와
    # 두 원소의 가운데 값 중 중간값을 pivot 값으로 지정 (기준 값)
    mid = (left + right) // 2
    mid_idx = MidNum(List, left, right, mid)
    
    List[left], List[mid_idx] = List[mid_idx], List[left]
    pivot = List[left]
    
    # low, high 역전 시 더 이상 정렬할 것 없다
    while low <= high:
        # low 가 끝까지 안 갔고, 해당 원소가 pivot 이하일 때, 
        # 원소는 그대로, low는 오른쪽으로
        while low <= right and List[low] <= pivot:
            low += 1
        
        # high가 끝까지 안 갔고, 해당 원소가 pivot 이상일 때,
        # 원소는 그대로, high는 왼쪽으로
        while high >= (left + 1) and List[high] >= pivot:
            high -= 1
        
        # low와 high 위치 원소가 정렬되어야 할 때
        if low <= high:
            List[low], List[high] = List[high], List[low]
    
    # pivot을 기준으로 리스트를 나눈다 <=> pivot과 high 위치를 바꾼다
    # pivot = List[left]
    List[left], List[high] = List[high], List[left]
    
    # high가 새로운 피벗 위치
    return high

# 퀵소트 함수
def QuickSort(List, left, right):
    
    # 더 이상 정렬 할 것 없음
    # List가 정렬됨
    if left >= right:
        return
    
    # pivot 위치 구하기
    pivot_idx = PartitionAndMakePivot(List, left, right)
    
    # 새로 구한 pivot 위치를 기준으로 재귀적으로 List[pivot_idx] 값보다 작은 리스트,
    # List[pivot] 값보다 큰 리스트로 생각하고 돌린다.
    QuickSort(List, left, pivot_idx - 1)
    QuickSort(List, pivot_idx + 1, right)
    
    return 

def GetMemory():
    # 리턴 단위 MB
    pid = os.getpid()
    mem = psutil.Process(pid)
    mem = mem.memory_info()[0] / 2**20
    return mem

# main 
def main():
    
    start_mem = GetMemory()
    start_time = time.time() # 단위 = second
    
    # csv 불러오기
    with open('./RandomNumbers.csv', "r") as csv_f:
        List = list(csv.reader(csv_f))
    
    for i in range(len(List)):
        List[i] = int(List[i][0])
        
    QuickSort(List, 0, len(List) - 1)
    oper_time = time.time() - start_time
    end_mem = GetMemory()

    print("time : {:.3f} sec".format(oper_time))
    print("memory : {:.3f} MB".format(end_mem - start_mem))
    
    if List == sorted(List):
        print("List sorting complete")
    
    csv_f.close()
    
if __name__ == '__main__':
    main()