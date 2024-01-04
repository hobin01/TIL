ch4

소유권 : 기존의 메모리를 관리하는 방법 (가비지 컬렉션, 개발자가 명시하는 방법 등)이 아닌 rust에서 도입한 메모리 관리 방법

컴파일 과정에서 메모리 관리를 진행하므로 프로그램 실행 속도에 영향 없음

- 소유권 규칙
1. rust에서 각각의 값은 owner 변수가 정해져 있다.
2. 한 값의 owner는 동시에 여러 개가 존재 할 수 없다.
3. owner가 scope 밖으로 벗어나면 값은 버려진다. (droppoed)

일반적인 문자열 리터럴 : rust에서 &str 타입 : 기본적으로 immutable

String 타입 : 힙에 데이터 저장됨. 할당된 메모리는 scope 벗어나는 순간 free 되도록 rust 컴파일 과정에서 체크함.

rust에서 변수가 scope 밖으로 벗어나면 drop 이라는 함수 호출하도록 (메모리 free) 작성되었기 때문.

```rust
{
	let s = String::from("hello");
	// do some with s
} // scope is over
```

rust에서 scope 벗어날 때 double free 방지하기 위해 기존 포인터를 무효화시킴. 

String 타입의 경우, 데이터 구조가 ptr, len, cap 으로 구성됨. 그리고 ptr는 실제 값을 가리킴.

만약 아래와 같다면

```rust
let s1 = String::from("hello");
let s2 = s1; // s1 무효화됨
println!("{s1}"); // ownership 컴파일 할 수 없다고 에러 발생
```

s1이 가졌던 ptr는 s2=s1 과정에서 free가 되어 버려 s1에 대해 뭘 할 수 없음. 일종의 shallow copy이지만, 기존 변수를 무효화하기 때문에 
move라고 함.

그리고 rust에서 자동으로 deep copy로 변수 복사하지는 않음. 

deep copy를 하고 싶다면 힙에 저장되는 데이터는 clone, 스택에 저장되는 데이터는 copy (Copy annotation 추가된 경우에만)

Copy 가능한 타입 : 정수형 타입(ex. i32), bool, 부동소수점 타입(ex. f32), char, Copy 가능한 타입으로 구성된 튜플 (ex. (i32, f32))

```rust
fn main() {
    let s = String::from("hello");
    takes_ownership(s);
    let x: i32 = 5;
    makes_copy(x);

    println!("{s}"); // error by s is moved
    println!("{x}"); // no error
}

fn takes_ownership(str: String) {
    println!("{str}");
}

fn makes_copy(num: i32) {
    println!("{num}");
}

```

함수의 return 값도 마찬가지로 String과 같이 할당이 필요한 타입은 move 발생함.

---

참조자 (reference) : &로 넘겨줌

```rust
let s1 = String::from("hello!");
let len = calculate_len(&s1);
println!("{}, {}", s1, len);
    
fn calculate_len(s: &String) -> usize {
    s.len()
}
```

참조자로 함수 파라미터로 넘기면 ownership 없이 포인터에 접근.

참조자로 가져온 변수의 값을 변경시키려면 let mut로 선언 후 &mut 로 넘겨줘야 함 (가변 참조자)

```rust
let mut s2 = String::from("hello, ");
let s3 = &mut s2;
s3.push_str("world");

println!("{}", s2);
```

가변 참조자의 경우, 특정 scope 내에 어떤 데이터를 가리키는 가변 참조자를 딱 하나만 만들 수 있음.

```rust
let mut s = String::from("hello");

let r1 = &mut s;
let r2 = &mut s; // error

println!("{}, {}", r1, r2);
```

위 제약사항으로 레이스 컨디션을 컴파일 과정에서 에러처리함

- 데이터 레이스 컨티션
1. 둘 이상의 포인터가 동시에 같은 데이터에 접근
2. 포인터 중 하나 이상이 데이터에 쓰기 작업을 시행
3. 데이터 접근 동기화 매커니즘이 없을 때

immutable 참조자는 여러 개 사용 가능하며, 가변 참조자와는 동시에 사용 불가

하지만 immutable 참조자의 scope가 끝난다면 가변 참조자와 함께 사용 가능

```rust
let mut s4 = String::from("hello world");
let s5 = &s4;
let s6 = &s4;
println!("{}, {}", s5, s6); // end of scope of s5, s6

let s7 = &mut s4;
s7.push_str("!!!!");
println!("{}", s7);
```

댕글링 참조자

어떤 메모리를 가리키는 포인터가 남아있는 상황에서 해당 포인터를 해제함으로써 다른 개체가 할당받았을지도 모르는 메모리를 참조하게 된 포인터

```rust
let refer_nothing = dangle();

fn dangle() -> &String {
	let s = String::from("string!!!");
	&s
}
```

만일 위와 같이 s를 리턴해야할 경우, s를 직접 리턴해야 함

```rust
let refer_nothing = dangle();

fn dangle() -> String {
	let s = String::from("string!!!");
	s
}
```

---

슬라이스 : 문자열, 배열의 일부분을 슬라이싱

문자열 슬라이싱 시 [starting_index..ending_index] 로 가져옴 (stating_index 부터 ending_index - 1번째 까지)

starting_index 에 아무 값 입력 안 하면 0으로 처리, ending_index에 아무 값 입력 안 하면 마지막+1 가리킴

```rust
fn main() {
    let s :String = String::from("hello world");
    let hello = &s[0..5];
    let world = &s[6..];

    println!("{}, {}", hello, world);
}
```

문자열 슬라이스의 타입은 &str 로 작성해야 함

- 첫 단어 파싱하는 코드

```rust
fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        // index, byte value
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}
```

배열도 동일하게 사용 가능

```rust
let arr = [1,2,3,4,5];
let slice_arr = &arr[1..3];
for num in slice_arr {
    println!("{num}");
}
```
