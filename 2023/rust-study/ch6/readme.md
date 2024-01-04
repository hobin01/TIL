ch6

enum 타입 (열거형)

열거형 생성은 기존 다른 언어의 열거형과 동일

```rust
enum EnumTest {
	one,
	two,
	three,
}
```

struct 안에 열거형 입력 시 enum의 특정 값을 입력받게 할 수 있다. enum 타입 입력 시 ::으로 해당 값 입력 받는다.

```rust
enum IpAddrKind {
    v4,
    v6,
}

struct IpAddr {
    kind: IpAddrKind,
    address: String,
}

fn main() {
    let home = IpAddr {
        kind: IpAddrKind::v4,
        address: String::from("127.0.0.1"),
    };
}
```

enum의 각 변수마다 타입 지정 가능하며, 튜플, struct, 배열 등도 가능하다.

```rust
#[derive(Debug)]
enum IpAddrKind {
    v4,
    v6,
}

#[derive(Debug)]
struct IpAddr {
    kind: IpAddrKind,
    address: String,
}

#[derive(Debug)]
enum Info {
    ip(IpAddr),
    mac([u8;6]),
    phone(String),
}

fn main() {
    let home = IpAddr {
        kind: IpAddrKind::v4,
        address: String::from("127.0.0.1"),
    };

    let home_mac = Info::mac([0x12, 0x34, 0x56, 0x78, 0x90, 0xAB]);
    println!("{:?}", home_mac);
}
```

또한 enum에 대해서도 메소드 정의가 가능하다. (impl)

---

Option 열거형

rust에서는 null의 개념이 없음. 그렇기 때문에 비어있는 리스트에서 값을 가져오는 등의 널 관련 에러가 발생하지 않음.

대신 Option 열거형에 정의된 None을 이용한다. Option 열거형의 None과 Some은 별도로 Option::을 붙히지 않아도 된다. 

None은 말 그래도 아무 값이 없다는 것이고, Some은 T에 해당하는 타입의 어떤 값이 있다는 것이다.

```rust
enum Option<T> {
    None,
    Some(T),
}

// <T> : 제네릭 타입 
```

```rust
let some_number = Some(5);
let some_char = Some('e');

let absent_number: Option<i32> = None;
```

---

match 흐름 제어

C의 switch와 비슷한 기능이지만 각 match되는 값의 리턴

enum 타입과도 같이 사용 가능

```rust
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => {
            println!("Lucky penny!");
            1
        }
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}
```

Option<T>를 이용한 매칭도 가능. 하지만 None 타입에 대한 케이스를 반드시 명시하여야 한다.

```rust
fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        None => None,
        Some(i) => Some(i+1),
    }
}

fn main() {
    let five = Some(5);
    plus_one(five);
    plus_one(None);
}

```

일반적으로 매칭이 이루어지지 않는 경우는 마지막 값에 매칭되므로 이런 예외처리 시 _로 보통 처리함. 또한 별도의 리턴 결과를 명시하지 않고 ()로 처리하면 어떤 결과도 없음.

```rust
fn main() {
    let dice = 6;
    match dice {
        6 => print_six(),
        _ => print_other(),
    }
}

fn print_six() {
    println!("six!!!");
}

fn print_other() {
    println!("other!!");
}
```

---

if let 사용

match를 이용하는 대신 아래와 같이 if let 구문을 이용해 match처럼 이용이 가능하다.

```rust
let mut count = 0;
match coin {
    Coin::Quarter(state) => println!("State quarter from {:?}!", state),
    _ => count += 1,
}

let mut count = 0;
if let Coin::Quarter(state) = coin {
    println!("State quarter from {:?}!", state);
} else {
    count += 1;
}
```

