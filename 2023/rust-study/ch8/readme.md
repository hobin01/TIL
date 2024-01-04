ch8

vector : 메모리 구조 상 서로 이웃하도록 리스트 구성. 벡터는 같은 타입의 값만 저장 가능

i32 타입의 원소를 갖는 벡터 구성

```rust
let v: Vec<i32> = Vec::new();
```

기본값이 정해져 있는 경우 아래와 같이 초기화 가능

```rust
let v = vec![1,2,3];
```

push : 벡터에 원소 추가

```rust
let mut v = Vec::new();
v.push(1);
v.push(2);
v.push(3);
```

위와 같은 경우, 1,2,3 과 같이 i32로 기본 타입이 정해져 있기 때문에 타입 따로 명시하지 않아도 됨.

get : 벡터 원소 읽기 - index로 접근하여 읽는다. get으로 읽으면 Option<&T> 타입이 리턴되어 match에서 Some 등으로 확인 가능하다.

```rust
let v = vec![1,2,3,4,5];
let third = &v[2]; // &i32 type
let third2 = v[2]; // i32 type
let third3 = v.get(2); // Option<&i32> type

match second3 {
    Some(second3) => println!("{}", second3),
    None => println!("None!!!"),
}
```

벡터의 메모리가 더 이상 추가할 수 없다면 (capacity 다 찼으면) 원소 추가 시 이전 벡터 자체도 새로운 메모리를 가리키게됨.

따라서 아래의 경우 에러 발생

```rust
let mut v = vec![1,2,3];
let first = &v[0];
v.push(4);
println!("first : {}", first); // error by v.push(4)
```

값만 카피하고자 하는 경우 let first = v[0] 와 같이 사용할 수 있지만, copy가 구현되지 않은 힙 영역을 사용하는 타입에 대해서는 borrow 유무 주의하여야 한다.

```rust
let mut v4: Vec<String> = vec![];
v4.push(String::from("first"));
// let first_string = v4[0]; // error by String
let first_string = &v4[0];
```

벡터에 대한 루프 (for i in &v)

```rust
let v = vec![1,2,3];
for i in &v {
	println!("{i}");
}
```

loop 발생 시 값만 카피한다면 & 없어도 되지만, 힙 영역 사용하는 타입의 경우, loop 이후 원소의 ownership이 바뀌게 되므로 주의하여야 한다.

loop를 통해 벡터 원소 변경 시 *(역참조)를 이용해 변경 가능 

```rust
let mut v = vec![1,2,3];
for i in &v {
	*i += 10;
}
```

---

rust에서 문자열 : String, 문자열 슬라이스 : &str, 2가지 타입 존재하며, 일반적으로 크게 구분짓지 않고 문자열로 칭함.

String은 힙 구조 가지면서 mutable 하며, &str은 immutable한 utf-8 byte 값을 가지는 문자열 슬라이스라 생각하면 됨.

(C++ 기준으로 String = string, str = *char)

문자열에 대한 소유권을 가지고 어떤 작업을 하려면 String이 더 유용하고, 단순히 문자열을 보기만을 원하면 &str이 더 적합하다.

실제로 String 타입은 바이트 벡터에 몇 가지 제한을 둔 것으로 구현되었기 때문에 Vec<T>에서 사용 가능한 대부분 연산을 사용할 수 있음.

String 선언

```rust
let mut s = String::new();
```

&str 타입을 String으로 변환할 수 있음. ( to_string() ) 사실 to_string() 메서드와 String::from 은 동일한 역할을 한다.

```rust
let hello = "hello";
let s = hello.to_string();
```

String에 문자, 문자열 추가 (push, push_str)

```rust
let hello = "hello";
let mut s2 = hello.to_string();
s2.push(' ');
s2.push_str("world");

println!("{}", &s2);
```

push의 파라미터는 char, push_str의 파라미터는 &str (그러므로 String 타입을 push_str로 추가하려면 &String 으로 push_str 하면 됨)

```rust
let mut s = String::new();
s.push('a');
s.push_str("bcd");
let mut s2 = "hello world ".to_string();
s2.push_str(&s);

println!("{}", &s2);
```

format! 매크로

아래와 같이 구성된 경우 s1이 move 되어 더 이상 사용 불가능하고, + 연산 시 &str 타입으로 계산되기 때문에 아래와 같이 덧셈 가능 (s1은 move되어 더 이상 사용 불가)

```rust
let mut s = String::new();
let s1 = "hello".to_string();
let s2 = " world".to_string();
s = s1 + &s2;

println!("{}", s1); // error by move
```

format! 매크로를 이용하면 형식은 println! 와 동일하지만 리턴을 String으로 하기 때문에 원하는 형식에 맞춰 String 생성 가능

```rust
let mut ss = String::new();
let ss1 = "hello".to_string();
let ss2 = " world".to_string();
    
ss = format!("{}+++{}", ss1, ss2);
```

문자열 인덱싱

String 타입은 힙 구조에 저장되기 때문에 아래와 같이 접근 시 에러 발생

```rust
let s = String::from("hello");
let h = s[0];
```

물론 &s[0] 와 같이 접근하여도 에러 발생함. 왜냐하면 String 타입에 대해서는 [i]를 이용한 인덱싱이 지원되지 않기 때문.

문자열의 일부를 가져오기 위한 슬라이싱은 지원함

```rust
let s = String::from("hello");
let h = &s[0..2]; // h = "he", type : &str
```

문자열 loop의 경우, chars() 로 char를 가져오거나 bytes() 로 byte 값을 가져올 수 있음 (&str에 대해서도 동일하게 loop 가능)

```rust
let sss = "sss123".to_string();
for c in sss.chars() {
	println!("{c}");
}
for b in sss.bytes() {
	println!("{b}");
}
```

---

해시맵

HashMap<K, V> 로 타입이 이루어져 있으며 K 키 타입과 V 밸류 타입이 기록됨. 일반적인 해시 테이블.

해시맵 생성

```rust
use std::collections::HashMap;

let mut scores = HashMap::new();
scores.insert(String::from("Blue"), 10);
scores.insert(String::from("Red"), 30);
```

해시맵도 데이터를 힙에 저장함. HashMap의 모든 원소의 키와 밸류는 동일한 타입이어야 함.

해시맵 원소 접근 (get)

get으로 접근한 키의 값이 없다면 None을 리턴함.

get의 리턴 값은 기본적으로 Option<&V> 타입이므로 값만 가지고 오고 싶다면 .copied() 메서드 이용 후 unwrap 이용

unwrap_or 로 default 값을 지정할 수 있으므로, HashMap에 키가 없는 경우 default 값을 가져오도록 할 수 있음.

```rust
use std::collections::HashMap;

fn main() {
    let mut scores = HashMap::new();
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Red"), 30);

    let team1 = String::from("Blue");
    let b = scores.get(&team1).copied().unwrap_or(0);
}
```

해시맵에 대한 loop는 (key, value) 쌍으로 가져온다. 단 이 때도 해시맵의 데이터는 힙에 저장되므로 소유권을 주의하여야 한다.

```rust
for (k, v) in &scores {
    println!("{k} {v}");
}
```

또한 insert 시에도 소유권이 바뀌기 때문에 주의하여야 함.

동일한 키를 갖도록 insert 하면 value는 덮어써짐.

키를 갖는 지 여부를 확인하는 것은 entry() 메서드를 이용하고, or_insert 메서드로 entry가 없을 때 value를 insert 하도록 할 수 있음

```rust
use std::collections::HashMap;

let mut scores = HashMap::new();
scores.insert(String::from("Blue"), 10);

scores.entry(String::from("Yellow")).or_insert(50);
scores.entry(String::from("Blue")).or_insert(50);

println!("{:?}", scores);
```



