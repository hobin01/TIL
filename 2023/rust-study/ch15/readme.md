ch15 스마트 포인터

일반적인 포인터 : & 로 가리키고 있는 값에 대한 참조자 불러옴

하지만 참조 외에 특별한 기능하지는 않음

스마트 포인터 : 포인터처럼 동작하며, 추가적인 기능 포함

스마트 포인터 타입은 여러 개 존재

ex. 참조 카운팅 (reference counting) : 포인터가 소유자의 개수를 추적하고 더 이상 소유자가 없으면 데이터 정리하는 방식으로, 여러 소유자를 만들 수 있게 해줌

참조자는 데이터를 빌리기만 하지만, 대부분의 스마트 포인터는 가리킨 데이터를 소유함

대표적인 스마트 포인터 : String, Vec<>

스마트 포인터는 보통 Deref, Drop trait을 구현함

Deref : 스마트 포인터 구조체 인스턴스가 차몾자처럼 동작하도록하여 참조자, 스마트 포인터와 함꼐 작동하는 코드 작성할 수 있도록 함

Drop : 스마트 포인터 인스턴스가 스코프 밖으로 벗어났을 때 실행되는 코드를 커스터마이징

책에서는 표준 라이브러리에 있는 가장 일반적인 스마트 포인터 위주로 다룸

직접 스마트 포인터 작성도 가능

다룰 내용 : 값을 힙에 할당하기 위한 Box<>, 복수 소유권을 가능하게 하는 참조 카운팅 Rc<>, borrow 규칙을 런타임에 강제하는 RefCell<>을 통해 접근 가능한 Ref<>, RefMut<>

---

Box<> : 가장 직관적인 스마트 포인터

Box는 힙에 데이터를 저장할 수 있게 해줌 (스택에는 힙 데이터 가리키는 포인터 저장)

그 외의 성능 차이는 없음

그리고 특별한 추가 기능도 없음

Box는 아래 상황에서 자주 쓰임

- 컴파일 타임에는 크기 알 수 없는 타입이 있는데 정확한 크기를 요구하는 context 내에서 해당 타입의 값을 사용하고 싶을 때

- 큰 데이터를 갖고 있고 소유권을 옮기고 싶지만, 그렇게 했을 때 데이터가 복사되지 않을 것을 보장하고 싶을 때

- 어떤 값을 소유하고, 이 값의 구체화된 타입보다는 특정 trait을 구현한 타입이라는 점만 신경 쓰고 싶을 때

---

Box를 사용하여 힙에 데이터 저장하기

아래는 Box를 사용하여 힙에 i32 타입의 값을 저장하는 방법

```rust
fn main() {
    let b = Box::new(5);
    println!("{}", b);
}
```

위에서 선언한 b라는 변수는 Box 타입을 가짐

이 때 5라는 i32 값은 힙에 저장

Box 안의 데이터는 스택에 있는 것처럼 접근 가능 (ex 그냥 print 할 때 b 로 출력)

스코프 벗어나면 다른 데이터와 마찬가지로 할당 해제됨

할당 해제는 스택에 저장된 포인터, 힙에 저장된 데이터 모두에게 발생

---

Box로 재귀적 타입 가능하게 하기

재귀적 타입 (recursive type) : 자신 안에 동일한 타입의 또 다른 값을 담을 수 있음

rust는 컴파일 타임에 어떤 타입이 얼마만큼의 공간을 차지하는 지 알아야 하기 때문에 재귀적 타입은 문제 발생

이론적으로는 무한히 많은 재귀적 타입 값 중첩이 발생하므로 컴파일 시 얼마만큼의 공간이 필요한 지 알 수 없음

Box를 이용해 재귀적 타입 정의에 Box를 넣어 재귀적 타입으로 이용 가능

재귀적 타입의 예제 : cons list : 함수형 프로그래밍 언어에서 흔히 사용되는 데이터 타입

cons list : 중첩된 쌍으로 구성된 linked list의 Lisp 버전

cons에 어떤 값과 다른 쌍으로 구성된 쌍을 넣어 호출함으로써 재귀적인 쌍으로 이루어진 cons list 구성 가능

ex. (1, (2, (3, Nil)))

위 예제에서 각 item은 2개의 요소를 갖고 있음. Nil은 재귀의 기본 케이스를 의미 

일반적인 Null, Nil과는 의미 다름

rust에서 위와 같은 구성 가능하지만, 보통 Vec<>로 리스트 구성하는 게 더 나음

```rust
enum List {
    Cons(i32, List),
    Nil,
}
```

위와 같이 List 타입을 구성했다면 infinite size 갖는 재귀 타입이라 컴파일 안 된다고 알려줌

Box<>를 이용하여 알려진 크기를 가진 재귀적 타입은 아래와 같이 구성 가능

```rust
enum List {
    Cons(i32, Box<List>),
    Nil,
}

use crate::List::*;

fn main() {
    let list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
}

```

Box는 포인터 값만 스택에 저장하고 있기 때문에 필요로 하는 공간 얼마인지 알고 있음

그러므로 재귀적 타입에서 Box 타입을 사용함으로써 전체 공간이 힙에 있을 다음 List 값을 가리키게 됨

위 예제에서 Cons 는 아래와 같은 구조 가짐

Cons : i32, Box (usize)

따라서 항상 Cons는 i32 + usize 만큼만의 크기를 갖게 되므로 재귀적 타입으로 사용 가능

---

Deref trait으로 스마트 포인터를 일반 참조자처럼 취급하기

Deref trait을 구현하면 역참조 연산자 * 동작을 커스터마이징 가능

Deref를 구현함으로써 참조자에 동작하는 코드가 스마트 포인터에도 사용될 수 있음

일반적인 참조자는 포인터의 한 종류, 아래 예제는 i32 타입에 대한 참조자를 생성하고 역참조 연산자를 사용해 참조자가 가리키는 값을 얻어냄

```rust
fn main() {
    let x = 5;
    let y = &x;

    assert_eq!(5, x);
    assert_eq!(5, *y);
}
```

위에서는 y가 x의 참조자를 갖고 있으므로 *y로 y가 가리키는 값, 즉, 5를 얻음

만약 `assert_eq!(5, y)` 인 경우, 타입이 다르다는 에러 발생

Box<>를 참조자처럼 사용하기

```rust
fn main() {
    let x = 5;
    let y = Box::new(x);

    assert_eq!(5, x);
    assert_eq!(5, *y);
}
```

위에서 y는 x의 값이 복사된 Box 타입을 가짐

이 때도 동일하게 *y로 y가 가진 값을 가져올 수 있음

---

자체 스마트 포인터 정의하기

Box<> 타입ㅇ은 하나의 요소를 가진 튜플 구조체로 정의됨

Box와 동일한 기능을 하도록 MyBox 타입을 구현함

```rust
struct MyBox<T> (T);

impl <T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}
```

기본적으로 Box 에 정의된 new 함수와 동일한 MyBox의 new 함수를 정의함

MyBox 타입은 제네릭 T를 하나만 갖는 튜플 구조체

MyBox::new 는 T 타입 값을 하나 받아 새로운 MyBox 타입의 값을 반환

아직은 역참조는 구현 안 되었으므로 아래와 같이 역참조 진행 시 *가 의미하는 게 뭔지 모름

```rust
struct MyBox<T> (T);

impl <T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

fn main() {
    let x = 5;
    let y = MyBox::new(x);

    assert_eq!(5, x);
    assert_eq!(5, *y);
}
```

*로 역참조하기 위해서는 Deref trait 구현해야 함

표준 라이브러리의 Deref trait은 deref라는 메서드를 하나 구현하도록 되어 있음

```rust
use std::ops::Deref;

struct MyBox<T> (T);

impl <T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

impl <T> Deref for MyBox<T> {
    type Target = T;
    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

fn main() {
    let x = 5;
    let y = MyBox::new(x);

    assert_eq!(5, x);
    assert_eq!(5, *y);
}
```

deref 함수로 &self.0 를 반환함으로써 튜플 구조체의 첫 번째 값인 T 타입의 값을 가져옴

즉 역참조 역할을 진행

*y를 호출할 때 실제로는 *(y.deref()) 가 실행됨

---

암묵적 역참조 강제

Deref를 구현한 어떤 타입의 참조자를 다른 타입의 참조자로 변경

예를 들어, String의 경우, &String을 &str로 변경함

이는 String의 Deref trait이 &str을 반환하도록 구현되었기 때문

```rust
fn hello(name: &str) {
    println!("hello : {name}");
}
```

위 hello 함수는 문자열 슬라이스를 파라미터로 가짐

역참조 강제를 이용해 `MyBox<String>` 타입에 대한 참조자로 hello 호출을 가능하게 만들어 줌

```rust
fn main() {
    let m = MyBox::new(String::from("123"));
    hello(&m);
}
```

MyBox에서 Deref trait을 구현했으므로 deref를 호출하여 `&MyBox<String>` 을 `&String` 으로 변환

그리고 String의 Deref trait 구현에 의해 `&String`은 다시 `&str` 로 변환

만약 Deref가 구현되어 있지 않으면 아래와 같이 코드 작성 가능

```rust
fn main() {
    let m2 = MyBox::new(String::from("123"));
    hello(&(*m2)[..]);
}
```

---

Drop trait로 메모리 정리 코드 실행

Drop : 어떤 값이 스코프 밖으로 벗어날 때 무슨 일을 할 지 커스터마이징

어떤 타입에 관해서든 Drop 구현이 가능

파일이나 네트워크 연결 같은 자원 해제에 사용

Drop은 스마트포인터 구현 시 거의 항상 이용

Box<> 타입이 버려질 때 Box가 가리키고 있는 힙 공간의 메모리 해제

Drop을 구현함으로써 파일 핸들러, 소켓, 뮤텍스 락 같은 것들 일일이 해제 안 해도 됨

컴파일러가 알아서 스코프 벗어나면 메모리 해제 시켜줌

아래는 Drop의 간단한 예제

```rust
struct CustomSmartPointer {
    data: String,
}

impl Drop for CustomSmartPointer {
    fn drop(&mut self) {
        println!("Drop CustomSmartPointer with data {}", self.data);
    }
}

fn main() {
    let c = CustomSmartPointer {
        data: String::from("my stuff"),
    };
    let d = CustomSmartPointer {
        data: String::from("other stuff"),
    };

    println!("CustomSmartPointers created");
}
```

main이 끝날 때 c와 d의 스코프가 벗어나게 되고, 이 때 Drop에 구현된 메시지가 출력됨

스택이 가리키는 변수는 선언한 것 역순으로 버려지므로 아래와 같은 출력 결과

CustomSmartPointers created
Drop CustomSmartPointer with data other stuff
Drop CustomSmartPointer with data my stuff

일반적으로 drop을 비활성화하는 일은 거의 일어나지 않음

락과 같은 경우, 강제로 같은 스코프의 락을 해제 후 다른 코드에서 해당 락을 얻도록 하는 경우가 있긴 함

rust에서는 수동으로 Drop trait의 drop 메서드를 호출하지는 못함

대신 std::mem::drop 을 사용하여 스코프가 끝나기 전에 강제로 값을 버릴 순 있음

```rust
struct CustomSmartPointer {
    data: String,
}

impl Drop for CustomSmartPointer {
    fn drop(&mut self) {
        println!("Drop CustomSmartPointer with data {}", self.data);
    }
}

fn main() {
    let c = CustomSmartPointer {
        data: String::from("my stuff"),
    };
    let d = CustomSmartPointer {
        data: String::from("other stuff"),
    };
    drop(c);
    println!("CustomSmartPointers created");
}
```

위 코드 실행 시 main의 마지막 print가 호출되기 전 c를 drop 하였음

따라서 아래와 같은 출력 결과 

Drop CustomSmartPointer with data my stuff
CustomSmartPointers created
Drop CustomSmartPointer with data other stuff

Drop과 소유권을 이용하면 rust에서 메모리 정리를 자동으로 수행하기 때문에 개발자가 별도로 메모리 정리에 신경쓰지 않아도 됨

---

Rc<> : 참조 카운트 스마트 포인터

그래프 구조와 같이 여러 엣지가 동일 노드를 가리키는 등 해당 노드가 가리키는 엣지의 소유가 되는 경우가 존재

그렇기에 하나의 데이터가 여러 개의 소유자를 가질 수 있음

복수 소유권을 가질려면 Rc<> 타입을 이용해야 함

Rc : reference counting

참조자 개수를 추적하여 해당 값이 계속 사용 중인지 판단

Rc 타입은 컴파일 타임에 어떤 부분이 데이터를 마지막으로 이용하게 될 지 알 수 없는 경우 사용

기본적으로 Rc는 싱글스레드 용이므로 멀티 스레드 환경에서는 다른 방법 사용

Rc를 이용해 데이터 공유

예를 들어, a 라는 cons list 가 5, 10 을 갖고 있고, b 라는 cons list 가 3, a, c 라는 cons list가 4, a를 갖고 있다고 가정하면 아래와 같음

```rust
enum List {
    Cons(i32, Box<List>),
    Nil,
}

use crate::List::*;

fn main() {
    let a = Cons(5, Box::new(Cons(10, Box::new(Nil))));
    let b = Cons(3, Box::new(a));
    let c = Cons(4, Box::new(a));
}
```

위 경우에서 a의 소유권이 b로 이미 옮겨 갔지만, 이후 c에서 a를 소유하려고 하므로 a에 대한 소유권 moved 에러 발생

라이프타임 파라미터를 지정하여 리스트 내의 모든 요소가 전체 리스트만큼 살아있다고 지정도 가능

여기서는 List에 대한 정의를 바꿔 a가 `Rc<List>` 를 갖도록 하고 b, c에 Rc::clone(&a) 를 호출하여 a에 대한 참조 카운트를 계산

```rust
enum List {
    Cons(i32, Rc<List>),
    Nil,
}

use crate::List::*;
use std::rc::Rc;

fn main() {
    let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
    let b = Cons(3, Rc::clone(&a));
    let c = Cons(4, Rc::clone(&a));
}
```

Rc::clone 호출 시 깊은 복사는 발생하지 않으며, 참조 카운트만 증가

깊은 복사를 원하면 a.clone() 을 호출

참조 카운드를 직접 세보면 다음과 같음

```rust
enum List {
    Cons(i32, Rc<List>),
    Nil,
}

use crate::List::*;
use std::rc::Rc;

fn main() {
    let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
    println!("count after creating a = {}", Rc::strong_count(&a));
    let b = Cons(3, Rc::clone(&a));
    println!("count after creating b = {}", Rc::strong_count(&a));
    {
        let c = Cons(4, Rc::clone(&a));
        println!("count after creating c = {}", Rc::strong_count(&a));
    }
    println!("count after c goes out of scope = {}", Rc::strong_count(&a));
}
```

출력

count after creating a = 1
count after creating b = 2
count after creating c = 3
count after c goes out of scope = 2

c에 대한 스코프를 벗어난 이후, 참조 카운트 개수가 2로 감소됨을 알 수 있음

하지만 Rc는 불변 참조자를 통해 읽기 전용으로만 사용 가능

가변성을 주기 위해서는 RefCell 타입을 사용해야 함

---

RefCell<>과 내부 가변성 패턴

RefCell 타입은 가지고 있는 데이터에 대한 단일 소유권을 나타냄

Box 타입은 소유권 대여 규칙의 불변성은 컴파일 타임에 진행

RefCell 타입은 대여 규칙의 불변성은 런타임에 진행

RefCell 타입을 이용한 프로그램의 런타임에서 대여 규칙 어길 시 panic! 발생되어 프로그램 종료

컴파일 타임의 대여 규칙 검사가 에러를 더 일찍 잡을 수 있기 때문에 런타임 성능에 영향이 없다는 장점

그렇기 때문에 대부분의 경우에서 Box를 이용하는 것이 좋은 선택이고, rust의 기본 설정인 이유

하지만 일부 컴파일러가 코드의 소유권 규칙 준수를 확신할 수 없을 때 RefCell을 이용

RefCell은 싱글스레드 시나리오 내에서만 사용 가능하며, 멀티스레드 환경에서는 컴파일 에러 발생

- Rc : 동일한 데이터에 대해 복수 소유자 가능 (Box, RefCell 은 단일 소유자만 가능)
- Box : 컴파일 타임에 불변, 가변 대여를 허용 (Rc : 컴파일 타임에 불변 대여만 허용, RefCell : 런타임에 불변, 가변 대여 허용)
- RefCell : 런타임에 가변 대여 허용, 불변인 경우에도 내부 값 변경 가능

---

mock : 테스트 더블의 특정한 형태, 테스트 중 어떤 일이 일어났는지 기록하여 정확한 동작이 일어났음을 확인 

예제 테스트 시나리오 : 최대값을 기준으로 어떤 값을 추적하여 현재 값이 최대값에 얼마나 근접했는 지에 대한 메시지를 전송하는 라이브러리 작성

해당 시나리오로 한 명에게 허용되고 있는 API 호출 허용향을 추적하는데 사용

```rust
pub trait Messenger {
    fn send(&self, msg: &str);
}

pub struct LimitTracker<'a, T: Messenger> {
    messenger: &'a T,
    value: usize,
    max: usize,
}

impl<'a, T> LimitTracker<'a, T>
where
    T: Messenger
{
    pub fn new(messenger: &'a T, max: usize) -> LimitTracker<'a, T> {
        LimitTracker { messenger, value: 0, max }
    }

    pub fn set_value(&mut self, value: usize) {
        self.value = value;

        let percentage_of_max = self.value as f64 / self.max as f64;

        if percentage_of_max >= 1.0 {
            self.messenger.send("Error : over quota");
        } else if percentage_of_max >= 0.9 {
            self.messenger.send("Urgent warning : over 90%");
        } else if percentage_of_max >= 0.75 {
            self.messenger.send("Warning : over 75%");
        }
    }
}
```

Messenger trait : self와 msg라는 불변 참조자를 send의 파라미터로 가짐

이는 Messenger trait은 mock 객체가 실제 객체와 동일하게 동작하도록 구현해야하는 메서드

아래는 mock 테스트를 위한 코드

```rust
#[cfg(test)]
mod tests {
    use super::*;

    struct MockMessenger {
        sent_msg: Vec<String>,
    }

    impl MockMessenger {
        fn new() -> MockMessenger {
            MockMessenger { sent_msg: vec![] }
        }
    }

    impl Messenger for MockMessenger {
        fn send(&self, msg: &str) {
            self.sent_msg.push(String::from(msg));
        }
    }

    #[test]
    fn over_75_percent() {
        let mock_messenger = MockMessenger::new();
        let mut limit_tracker = LimitTracker::new(&mock_messenger, 100);

        limit_tracker.set_value(80);

        assert_eq!(mock_messenger.sent_msg.len(), 1);
    }
```

위 코드 실행 시 send 메서드가 self의 불변 참조자를 가져오기 때문에 sent_msg.push 가 불가능하다는 에러 발생

그리고 &mut self를 사용하라는 문구도 발생하지 않음

이는 Messenger trait 정의가 불변이기 때문

이러한 상황을 해결하기 위한 것이 RefCell

```rust
#[cfg(test)]
mod tests {
    use super::*;
    use std::cell::RefCell;

    struct MockMessenger {
        sent_msg: RefCell<Vec<String>>,
    }

    impl MockMessenger {
        fn new() -> MockMessenger {
            MockMessenger { sent_msg: RefCell::new(vec![]) }
        }
    }

    impl Messenger for MockMessenger {
        fn send(&self, msg: &str) {
            self.sent_msg.borrow_mut().push(String::from(msg));
        }
    }

    #[test]
    fn over_75_percent() {
        let mock_messenger = MockMessenger::new();
        let mut limit_tracker = LimitTracker::new(&mock_messenger, 100);

        limit_tracker.set_value(80);

        assert_eq!(mock_messenger.sent_msg.borrow().len(), 1);
    }
}
```

send 메서드의 self는 여전히 불변 참조자이지만, 컴파일 타임에서 RefCell로 선언된 파라미터 (msg)에 대해 따로 검사하지 않음 

---

RefCell의 borrow 메서드는 스마트 포인터 타입인 Ref<T>를 반환, borrow_mut 메서드는 RefMut<T>를 반환

두 타입 모두 Deref가 구현되어 있기 때문에 일반적인 참조자처럼 사용 가능

RefCell은 현재 활성화된 Ref<>와 RefMut<> 가 몇 개나 있는 지 추적

호출할 때마다 활성화된 포인터 개수 증가, 스코프 벗어나면 감소

해당 규칙 위반 시 panic! 발생

예를 들어 아래와 같은 상황과 같이 동일 스코프 내에 같은 불변 참조자에 대한 여러 개의 가변 대여를 같은 방식으로 사용 시 panic! 발생

```rust
impl Messenger for MockMessenger {
    fn send(&self, msg: &str) {
        let mut one_borrow = self.sent_msg.borrow_mut();
        let mut two_borrow = self.sent_msg.borrow_mut();
        one_borrow.push(String::from(msg));
        two_borrow.push(String::from(msg));
    }
}
```

RefCell을 사용하는 일반적인 방법은 Rc와 조합하는 것

Rc가 어떤 데이터에 대한 복수 소유자를 허용하지만, 불변 접근만 제공하기 때문

RefCell을 갖는 데이터가 Rc를 가지면 가변이면서 동시에 복수 소유자를 갖는 값을 얻을 수 있음

```rust
#[derive(Debug)]
enum List {
    Cons(Rc<RefCell<i32>>, Rc<List>),
    Nil,
}

use crate::List::*;
use std::cell::RefCell;
use std::rc::Rc;

fn main() {
    let val = Rc::new(RefCell::new(5));
    
    let a = Rc::new(Cons(Rc::clone(&val), Rc::new(Nil)));

    let b = Cons(Rc::new(RefCell::new(3)), Rc::clone(&a));
    let c = Cons(Rc::new(RefCell::new(4)), Rc::clone(&a));

    *val.borrow_mut() += 10;

    println!("a = {:?}", a);
    println!("b = {:?}", b);
    println!("c = {:?}", c);
}
```

a는 Rc를 갖기 때문에 b,c에서 List 생성 시 a 참조 가능

*val.borrow_mut() 을 이용해 Rc를 역참조하여 RefCell을 얻음

출력 결과

a = Cons(RefCell { value: 15 }, Nil)
b = Cons(RefCell { value: 3 }, Cons(RefCell { value: 15 }, Nil))
c = Cons(RefCell { value: 4 }, Cons(RefCell { value: 15 }, Nil))

---

앞서 Rc, RefCell 등에 의해 메모리 누수가 발생 가능함

즉, 아이템 간에 서로 순환 참조하는 참조자 생성이 가능

이는 순환을 멈추지 않으면 무한히 참조하기 때문에 참조 카운트가 0이 되지 않으므로 메모리 누수 발생

순환 참조 방지 : Rc를 Weak로 변경

Rc::clone 호출하는 것은 Rc의 strong_count을 증가시키고, 0이 된 경우에만 제거

Rc::downgrade에 Rc의 참조자를 넣어 호출하면 인스턴스 내의 값을 가리키는 약한 참조를 만드는 것도 가능

약한 참조는 소유권 관계를 만들지 않고, Rc 인스턴스가 제거되는 경우에 영향을 주지 않음

약한 참조가 포함된 순환 참조는 강한 참조 개수를 0으로 만드는 순간 깨지게 되므로 순환 참조 발생하지 않음

Rc::downgrade 호출 시 Weak<> 타입의 스마트 포인터를 얻음

Rc::downgrade는 strong_count가 아닌 weak_count를 1씩 증가

Weak가 가리키고 있는 값으로 어떤 작업을 하기 위해서는 값이 여전히 존재하는 지 확인해야 함

이를 위해 upgrade 메서드를 호출하며, 이는 Option<Rc<T>> 타입을 반환

아직 존재한다면 Some, 없다면 None 결과를 얻게 되므로 유효하지 않은 포인터는 없음

---

트리 구조 만들기

```rust
use std::cell::RefCell;
use std::rc::Rc;

#[derive(Debug)]
struct Node {
    val: i32,
    child: RefCell<Vec<Rc<Node>>>,
}

fn main() {
    let leaf = Rc::new(Node {val: 3, child: RefCell::new(vec![])});

    let branch = Rc::new(Node {val: 5, child: RefCell::new(vec![Rc::clone(&leaf)])});
}
```

위에서 Node struct는 child를 소유하고 있고, 소유권을 공유하여 트리의 각 Node에 직접 접근할 수 있도록 함

이를 위해 Vec를 Rc<Node> 로 타입 지정

그리고 어떤 Node가 다른 Node의 자식이 되도록 수정하기 위해 child는 최종적으로 RefCell 타입

main의 branch는 leaf를 clone하고 있으므로 branch도 leaf의 Node에 대한 소유권 가짐

그러므로 branch는 leaf로 접근 가능하지만, leaf는 branch로 접근 불가능

자식에서 부모로 가는 참조자 추가 위해 parent 필드 추가

```rust
use std::cell::RefCell;
use std::rc::{Rc, Weak};

#[derive(Debug)]
struct Node {
    val: i32,
    child: RefCell<Vec<Rc<Node>>>,
    parent: RefCell<Weak<Node>>,
}

fn main() {
    let leaf = Rc::new(Node {
        val: 3, 
        child: RefCell::new(vec![]), 
        parent: RefCell::new(Weak::new()),
    });

    println!("leaf parent : {:?}", leaf.parent.borrow().upgrade());

    let branch = Rc::new(Node {
        val: 5, 
        child: RefCell::new(vec![Rc::clone(&leaf)]),
        parent: RefCell::new(Weak::new()),
    });

    *leaf.parent.borrow_mut() = Rc::downgrade(&branch);

    println!("leaf parent : {:?}", leaf.parent.borrow().upgrade());
}
```

실행 결과는 다음과 같음

```
leaf parent : None
leaf parent : Some(Node { val: 5, child: RefCell { value: [Node { val: 3, child: RefCell { value: [] }, parent: RefCell { value: (Weak) } }] }, parent: RefCell { value: (Weak) } })
```



