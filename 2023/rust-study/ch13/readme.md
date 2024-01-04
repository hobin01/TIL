ch13

함수형 언어

rust 주요 특징 중 하나는 함수형 프로그래밍 지원하는 것

함수형 스타일 프로그래밍 : 함수를 값처럼 파라미터로 넘기는 것, 결과값으로 함수를 리턴하는 것, 함수를 변수에 할당하는 것 포함

---

클로저(Closure) : 자신의 환경을 캡처하는 익명 함수

클로저는 변수에 저장하거나 다른 함수에 인자로 넘길 수 있는 익명 함수

일반 함수와 다르게 클로저는 정의된 스코프에서 값을 캡처할 수 있음

```rust
#[derive(Debug, PartialEq, Copy, Clone)]
enum ShirtColor {
    Red,
    Blue,
}

struct Inventory {
    shirts: Vec<ShirtColor>
}
impl Inventory {
    fn giveaway(&self, user_preference: Option<ShirtColor>) -> ShirtColor {
        user_preference.unwrap_or_else(|| self.most_stocked())
    }

    fn most_stocked(&self) -> ShirtColor {
        let mut num_red = 0;
        let mut num_blue = 0;

        for color in &self.shirts {
            match color {
                ShirtColor::Red => num_red += 1,
                ShirtColor::Blue => num_blue += 1,
            }
        }

        if num_red > num_blue {
            ShirtColor::Red
        } else {
            ShirtColor::Blue
        }
    }
}

fn main() {
    let store = Inventory {
        shirts: vec![ShirtColor::Blue, ShirtColor::Red, ShirtColor::Blue],
    };

    let user_pref1 = Some(ShirtColor::Red);
    let giveaway1 = store.giveaway(user_pref1);
    println!(
        "The user with preference {:?} gets {:?}",
        user_pref1, giveaway1
    );

    let user_pref2 = None;
    let giveaway2 = store.giveaway(user_pref2);
    println!(
        "The user with preference {:?} gets {:?}",
        user_pref2, giveaway2
    );
}
```

giveaway 메서드에서 Option<T> 인 user_preference 에 unwrap_or_else 메서드 호출함

user_preference 가 Some 값을 가지면 unwrap 된 결과를 리턴,

None 값을 가지면 클로저를 호출하여 self.most_stocked() 를 리턴

현재 || 로써 아무런 매개변수가 없는 클로저

---

클로저와 함수의 차이

클로저는 매개변수나 리턴값을 명시하지 않음

그리고 클로저는 함수처럼 노출된 인터페이스로 사용되지 않기 때문에 변수 이름이 지어지거나 사용자들에게 노출되지 않고 저장됨

클로저에 매개변수와 리턴값을 명시할 수도 있음


```rust
let _expensive_closure = |num: u32| -> u32 {
    println!("calculate slowly...");
    thread::sleep(Duration::from_secs(2));
    num
};
```

클로저에 타입 명시가 추가되면 함수의 문법과 유사

클로저가 단일 동작만을 할 시, {} 없어도 된다

```rust
fn add_one_v1 (x: u32) -> u32 {x + 1};
let add_one_v2 = |x: u32| -> u32 {x + 1};
let add_one_v3 = |x: u32| {x + 1};
let add_one_v4 = |x: u32| x + 1;

let result = add_one_v2(123);
println!("{result}");
```

위 함수 및 변수는 모두 동일 동작함

아무런 타입 명시하지 않을 시, 아무 타입이나 클로저를 호출 가능

하지만 다음 클로저 호출 시, 동일한 타입이 호출 가능

---

참조자 캡처, 소유권 이전

클로저는 세 가지 방식으로 값을 캡처할 수 있음

불변으로 빌려오기, 가변으로 빌려오기, 소유권 이동

클로저는 캡처된 값이 쓰이는 방식에 기반해 캡처할 방법 결정

```rust
fn main() {
    let list = vec![1,2,3];
    println!("Before defining closure : {:?}", list);

    let only_borrows = || println!("From closure : {:?}", list);

    println!("Before calling closure : {:?}", list);
    only_borrows();
    println!("After calling closure: {:?}", list);
}
```

위에서 정의된 클로저는 list라는 vector에 대한 불변 참조자를 캡처

only_borrows라는 변수에 클로저가 바인딩되어 함수처럼 호출 가능

그리고 list 변수에 여러 개의 불변 참조자를 동시에 가질 수 있으므로 클로저 정의 후 또는 호출 후에도 list 변수에 접근 가능

```rust
fn main() {
    let mut list = vec![1,2,3];
    println!("Before defining closure : {:?}", list);

    let mut borrows = || list.push(4);

    // println!("Before calling closure : {:?}", list);
    borrows();
    println!("After calling closure: {:?}", list);
}
```

위에서는 list가 mutable 한 상황

borrows 클로저 정의된 시점에 클로저가 list에 대한 가변 참조자를 캡처

클로저 호출 이전에 list 출력을 시도하면 borrow 에러 발생

클로저에게 가변 대여 시 다른 대여가 허용되지 않기 때문

그러므로 borrows 호출이 끝난 이후 가변 대여가 종료되어 borrows() 호출 이후 list 출력은 가능

---

클로저가 소유권을 갖도록 만들고 싶으면 매개변수 호출 전 move 키워드 사용 가능

이는 새 스레드가 데이터를 소유하게 하는 경우 유용

자세한 설명은 16장에서

아래는 간단한 예시

```rust
use std::thread;

fn main() {
    let list = vec![1,2,3];
    println!("Before defining closure : {:?}", list);

    thread::spawn(move || println!("From thread : {:?}", list))
        .join()
        .unwrap();
}
```

새 스레드를 생성하여 파라미터로 실행될 클로저를 제공

클로저의 본문에서는 list를 출력

클로저 정의 전에 move 키워드를 통해 list의 소유권을 이동함을 명시

이는 메인 스레드가 list의 소유권을 유지하고 있는데 새 스레드가 끝나기 전에 list를 제거한다면 새 스레드에서는 list 사용 불가

따라서 list 변수 자체에 대한 소유권을 move 시킴으로써 새 스레드에 list에 대한 참조자가 유효하도록 유지 

메인 스레드인 main 함수에서 이후에 list 변수 사용 시 소유권 이전되었다는 에러 발생함

---

캡처된 값을 클로저 밖으로 이동, Fn trait

클로저가 자신이 정의된 환경으로부터 값의 참조자, 소유권을 캡처하면 본문은 클로저가 평가될 때 참조자나 값에 어떤 일이 발생했는 지 정의

클로저 본문은 다음의 기능이 가능

캡처된 값을 클로저 밖으로 이동시키기, 캡처된 값 변형하기, 아무 값도 캡처하지 않거나 변형시키지 않기

1. FnOnce는 한 번만 호출될 수 있는 클로저에 적용

모든 클로저는 호출될 수 있으므로, 최소한 이 trait은 구현해야 한다.

캡처된 값을 본문 밖으로 이동시키는 클로저에 대해서는 FnOnce만 구현되며, 나머지 Fn trait은 구현되지 않는데, 이는 해당 클로저가 한 번만 호출될 수 있기 때문

2. FnMut는 본문 밖으로 캡처된 값을 이동시키지는 않지만 값을 변경할 수 있는 클로저에 대해 적용

해당 클로저는 여러 번 호출 가능

3. Fn은 캡처된 값을 본문 밖으로 이동시키지 않고 캡처된 값을 변경하지도 않는 클로저, 아무 것도 캡처하지 않는 클로저에 적용

클로저가 동시에 여러 번 호출되는 환경 등에서 중요

```rust
impl<T> Option<T> {
    pub fn unwrap_or_else<F>(self, f: F) -> T
    where
        F: FnOnce() -> T
    {
        match self {
            Some(x) => x,
            None => f(),
        }
    }
}
```

Option의 impl 내용

unwrap_or_else 함수의 경우, F라는 제네릭 타입 갖고 있음

이는 unwrap_or_else를 호출할 때 제공하는 클로저

F에 명시된 trait 바운드는 FnOnce() -> T

이는 F가 한 번만 호출될 수 있어야 하고, 인수가 없고, T를 반환해야 함을 의미

match 구문을 보면 f 라는 클로저는 None 인 경우만 호출. 즉, 단 한 번만 호출

모든 클로저가 FnOnce를 구현하므로 unwrap_or_else 함수는 다양한 클로저를 허용함

---

표준 라이브러리의 슬라이스 상에 정의된 sort_by_key의 trait 바운드는 FnMut를 사용

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let mut list = [
        Rectangle{width: 10, height: 1},
        Rectangle{width: 3, height: 5},
        Rectangle{width: 7, height: 10},
    ];

    list.sort_by_key(|r| r.width);
    println!("{:?}", list);

}
```

sort_by_key 를 이용해 width 순으로 정렬

sort_by_key는 클로저를 여러 번 호출하기 때문에 FnMut 클로저를 갖도록 정의됨

슬라이스의 각 item 별로 클로저를 호출하기 때문 

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let mut list = [
        Rectangle{width: 10, height: 1},
        Rectangle{width: 3, height: 5},
        Rectangle{width: 7, height: 10},
    ];

    let mut sort_oper = vec![];
    let val = String::from("by key called");

    list.sort_by_key(|r| {
        sort_oper.push(val);
        r.width
    })
}
```

위 코드는 sort_by_key 사용 시 클로저 환경에 val를 넣어 정렬하려는 방식 (말이 안 되는 정렬 방식)

클로저는 val를 캡처한 다음 val의 소유권을 sort_oper 벡터로 보내 val을 클로저 밖으로 이동되며, 이 때 클로저는 val이 String이므로 한 번만 호출 가능

따라서 두 번째 item에 대해 접근 시 val이 더 이상 환경에 남아 있지 않아 에러 발생

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let mut list = [
        Rectangle{width: 10, height: 1},
        Rectangle{width: 3, height: 5},
        Rectangle{width: 7, height: 10},
    ];

    let mut sort_oper = 0;

    list.sort_by_key(|r| {
        sort_oper += 1;
        r.width
    });

    println!("{:?}, sorted in {sort_oper} oper", list);
}
```

위 처럼 sort_oper에 대한 가변 참조자를 캡처만 함으로써 클로저 본문에서 sort_oper의 값만 증가시킴을 통해 sort 횟수 계산 가능 

---

반복자로 아이템 처리하기

rust에서 반복자(iterator)는 lazy

반복자를 사용하는 메서드는 반복자를 쓰기 전가지 동작하지 않음

예를 들어 아래와 같은 경우, v1_iter는 동작하기 전까지 아무것도 안 함

```rust
let v1 = vec![1,2,3];
let v1_iter = v1.iter();
```

반복자는 v1_iter에 저장. for 루프 등을 이용해서 반복자의 요소들이 루프를 돌며 사용됨

```rust
fn main() {
    let v1 = vec![1,2,3];
    let v1_iter = v1.iter();

    for v in v1_iter {
        println!("v : {v}");
    }
}
```

Iterator trait 과 next method

모든 반복자는 Iterator 라는 이름의 trait을 구현함

```rust
pub trait Iterator {
    type Item;

    fn next(&mut self) -> Option<Self::Item>;

    // 기본 구현이 있는 메서드는 생략했습니다
}
```

Iterator trait을 구현하려면 Item 타입도 함께 정의되어야 한다.

Item이 next 메서드의 반환 타입으로 사용된다.

그리고 다음 반복자로 넘어갈 next 메서드를 구현해야 한다.

```rust
// src/lib.rs

#[test]
fn iterator_demonstration() {
    let v1 = vec![1, 2, 3];

    let mut v1_iter = v1.iter();

    assert_eq!(v1_iter.next(), Some(&1));
    assert_eq!(v1_iter.next(), Some(&2));
    assert_eq!(v1_iter.next(), Some(&3));
    assert_eq!(v1_iter.next(), None);
}
```

테스트 시 v1_iter와 같이 iterator를 가변으로 생성

next 메서드를 호출하면서 반복자의 현재 시퀀스를 추적하기 때문

실제 사용 시에는 mut 할 필요는 없음

v1의 소유권을 얻어서 소유한 값을 반환하려면 iter 대신 into_iter 메서드 사용

가변 참조자에 대한 iterator가 필요한 경우, iter 대신 iter_mut 사용

---

반복자를 소비하는 메서드

next를 호출하는 메서드를 consuming adaptor(소비 어댑터)라 부름

호출하면서 반복자를 소비하기 때문

sum 메서드의 경우, 반복자의 소유권을 가져와 반복적으로 next를 호출하여 반복자를 소비

```rust
#[test]
fn iterator_sum() {
    let v1 = vec![1, 2, 3];

    let v1_iter = v1.iter();

    let total: i32 = v1_iter.sum();

    assert_eq!(total, 6);
}
```

sum이 반복자를 소유하여 호출하였으므로, sum 이후 v1_iter의 사용은 불가능

```rust
fn iterator_sum() {
    let v1 = vec![1, 2, 3];

    let v1_iter = v1.iter();

    let total: i32 = v1_iter.sum();

    let total2: i32 = v1_iter.sum();

    assert_eq!(total, 6);
}
```

위에서 total2에 대해서는 소유권 move 되어 사용 불가능하다는 에러 발생

다른 반복자를 생성하는 메서드

map은 클로저를 인수로 받아 각 아이템에 대해 호출하며 순회

map 메서드는 수정된 아이템을 생성하는 새로운 반복자를 반환

```rust
fn main() {
    let v1 = vec![1,2,3];
    v1.iter().map(|x| x+1);

    for v in v1.iter(){
        println!("{v}");
    }
}
```

위 코드 실행 시 v1은 그대로 존재 

반복자를 호출한 시점에서 클로저에 대해 아무것도 하지 않기 때문 (lazy)

그렇기 때문에 모든 아이템에 +1 을 하려면 collect() 메서드를 추가로 호출하여 반복자 소비 후 새로운 벡터 생성해야 함

```rust
fn main() {
    let v1 = vec![1,2,3];
    let v2: Vec<i32> = v1.iter().map(|x| x+1).collect();

    for v in v2.iter(){
        println!("{v}");
    }
}
```

map이 클로저를 인수로 받기 때문에 아이템에 대한 연산 수행

그리고 collect로 클로저로 수행한 연산을 모아 새로운 벡터에 저장

그리고 새로운 벡터에 대해 또 다른 반복자를 소비 

filter 메서드 : 클로저가 반복자로부터 아이템을 받아 true인 경우만 포함

아래에서 shoe_size를 캡처하는 클로저를 이용해 지정된 크기의 신발만 반환해줄 것을 요청

```rust
// src/lib.rs

#[derive(PartialEq, Debug)]
struct Shoe {
    size: u32,
    style: String,
}

fn shoes_in_size(shoes: Vec<Shoe>, shoe_size: u32) -> Vec<Shoe> {
    shoes.into_iter().filter(|s| s.size == shoe_size).collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn filters_by_size() {
        let shoes = vec![
            Shoe{
                size: 10,
                style: String::from("sneaker"),
            },
            Shoe{
                size: 13,
                style: String::from("boot"),
            },
            Shoe{
                size: 10,
                style: String::from("sandal"),
            },
        ];

        let my_size = shoes_in_size(shoes, 10);

        assert_eq!(
            my_size,
            vec![
                Shoe {
                    size: 10,
                    style: String::from("sneaker")
                },
                Shoe {
                    size: 10,
                    style: String::from("sandal")
                },
            ]
        );
    }
}
```
