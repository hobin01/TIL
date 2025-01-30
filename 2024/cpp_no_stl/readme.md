c++ stl 없이 자료구조 + 알고리즘 구현용

data structure

- vector O
- stack O 
- queue O
- priority_queue O
- map, set O
- list O
- unordered_map (hashing) O
- trie O

algorithm

- binary search O
- quick sort O
- dijkstra, floyd-warshall O
- MST (kruskal) O
- permutation, combination O
- range max / min value, range sum with fenwick tree (메모리 관점에서 세그먼트, 인덱스 트리보다 나음)
- 
- N진법 사칙연산 O
- 카라츠바 빠른 곱셈 O
- 소인수분해 (polard-rho)
- 빠른 지수 연산
- 유클리드 알고리즘
- 중국인 나머지 정리
- 행렬 곱셈
- 피보나치 수열 합 
- 
- KMP
- Edmond-Karp
- SCC
- 2-SAT
- 선분 교차 알고리즘
- CCW
- Convex Hull
- topology sort 
- 호프먼 인코딩 
- 

etc

- handling char* O
- class / struct constructor, destructor, functions O
- memory allocation with new, delete O
- malloc, calloc, realloc, free O

----

기본 내용이지만 햇갈리는 것들 정리

(시험 관련)
- 시험에서 `malloc.h` 만 가능 (실제 사용 가능한 동적 메모리 관리 함수 : `malloc, calloc, realloc, free`)
- c++ new, delete, for문으로 커버 가능 (아주 조금 더 느릴 순 있음)
- 최적화 기능 끄고 채점함
  
(템플릿)
- `template<typename T>` 로 임의의 type 적용 가능한 class, struct, function 만들 수 있음

(포인터, 참조자)
- 포인터 : 주소를 갖고 있는 변수, & : 주소 자체를 의미
- ex. `int a = 10`
- `int* b = &a` : 10이라는 값이 할당된 a의 주소를 b에 저장함 (포인터 변수)
- `int& c = a` : c는 a의 주소 자체를 가져오는 참조자
- `b`는 `a`의 주소를 저장, `c`는 `a` 그 자체가 됨 (`int d = a` 는 d에 a의 값을 복사, 주소 다름)
- `*b` : 현재 b가 가리키는 값 (10을 의미)
- `b` : 현재 가리키고 있는 것인 a의 주소 (0xXXXX)
- `&b` : b라는 포인터 변수의 주소 (0xYYYY)
- `c` : c 주소에 저장된 값 (10을 의미)
- `&c` : c의 주소를 의미 (현재 a의 주소와 동일한 값) (0xXXXX)

(클래스)
- class 내에 선언된 함수는 class 내의 변수 사용 시, 굳이 this 안 써도 됨
- 생성자 : `A() : ...(val), ...(val), ...(val) {}` 와 같이 ...(val)로 private에 선언한 변수 초기화 가능 ({}에서 할당 시, 값 생성, = 으로 복사 과정 필요하지만, ...(val)로 복사 과정없이 직접 할당 가능)
- 소멸자 : `~A() {...}` 와 같이 메모리 없앨 것 ...에서 확실하게 처리 필요
- c++은 struct에도 function 지정 가능 

(문자열)
- `char*` 의 경우, 맨 마지막에 `null` 값 필요 (아스키 0, 문자값 '\0') 

(생성, 할당)
- `new`로 할당한 포인터는 반드시 `delete`로 제거해야 함
- 배열의 경우, `new`로 동적 할당 시, `int* arr = new int[10]`과 같이 크기 지정
- 배열의 경우, `delete`로 메모리 해제 시, `delete[] arr`과 같이 해제 (그냥 `delete arr` 시, `arr[0]` 위치 메모리만 해제. 나머지는 해제 안 되어 메모리 누수 발생 가능)
- 배열이 아닌 포인터는 그냥 `T* a = new T(); delete a;` 와 같이 사용
- `new T, new T()` 차이 : `()` 실행함으로써 초기값 할당 (없으면 아무 값도 들어있지 않게되므로 ()하는 것이 일반적)
