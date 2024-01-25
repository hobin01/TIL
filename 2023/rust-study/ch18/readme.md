ch18

패턴과 매칭

패턴 (pattern) : 복잡하거나 단순한 타입의 구조와 매칭을 위한 러스트 특수 문법

패턴은 match 등과 함께 사용하면 프로그램 흐름을 더 잘 제어할 수 있음

패턴은 다음의 조합으로 구성
- 리터럴 값
- 분해한 (destructed) 배열, 열거형, 구조체, 튜플
- 변수
- 와일드카드
- 자리 표시자 (placeholder)

ex) x, (a,3), Some(Color::Red)

---

match에서 패턴은 기본적으로 사용 중임

```rust
match VALUE {
    PATTERN1 => EXPRESSION1,
    PATTERN2 => EXPRESSION2,
}

match x {
    None => None,
    Some(i) => Some(i+1),
}
```

if, let 조건 표현식을 이용한 패턴 매칭

```rust
fn main() {
    let favorite_color: Option<&str> = None;
    let is_tuesday = false;
    let age: Result<u8, _> = "34".parse();

    if let Some(color) = favorite_color {
        println!("Using your favorite color, {color}, as the background");
    } else if is_tuesday {
        println!("Tuesday is green day!");
    } else if let Ok(age) = age {
        if age > 30 {
            println!("Using purple as the background color");
        } else {
            println!("Using orange as the background color");
        }
    } else {
        println!("Using blue as the background color");
    }
}
```

위 예의 경우 favorite_color = None 이므로 if 조건 만족 안 하고 

is_tuesday = false 이므로 else if 통과 안 하고

age 값이 할당되어 있으며 34이므로 else if > if 순으로 통과하므로 

"Using purple as the background color" 이 출력됨

match와 if let 차이 : match는 모든 패턴에 대해 체크하지만, if는 모든 패턴에 대한 조건이 없더라도 모든 케이스를 체크하지 않음

따라서 else 등으로 패턴 매칭이 되지 않는 나머지 부분을 처리하지 않더라도 논리적 오류는 없음

이외에도 while, for loop 등에서도 loop가 동작하는 조건에 대해 패턴 매칭이 이루어짐

그리고 let 으로 변수 타입 지정 및 할당, 함수 파라미터에 올바른 타입의 인자 넣기 등에도 모두 패턴 매칭이 이루어진 결과

---

반박 가능성 : 패턴이 매칭에 실패할지의 여부

패턴 : 반박 가능한 패턴, 반박 불가능한 패턴 존재

넘겨진 모든 가능한 값에 대해 매칭되는 패턴 : 반박 불가능한 패턴 (irrefutable pattern)

`let x = 5;` 와 같은 경우, x는 무엇이든 매칭되므로 매칭에 실패할 수 없음

일부 가능한 값에 대해 매칭에 실패할 수 있는 패턴 : 반박 가능한 패턴 (refutable pattern)

`let a_value = None; let Some(x) = a_value;` 와 같은 경우, a_value가 None값이므로 Some(x)에 매칭될 수 없음

함수 파라미터, let, for loop 등에는 반박 불가능한 패턴만 허용됨

이는 값이 매칭되지 않으면 프로그램이 의미 있는 작업을 수행할 수 없기 때문

if let, while let 은 반박 불가능한 패턴과 반박 가능한 패턴을 모두 허용하지만, 반박 불가능한 패턴에 대해서는 경고를 줌

반박 불가능한 패턴 적용 시 값이 할당되었다는 사실이 true로 동작해 if, while 조건을 항상 만족하기 때문

ex) some_option_value 가 None인 경우 어떤 작업을 수행할 때

```rust
let Some(x) = some_option_value;
```

와 같이 선언 시 let에 반박 가능한 패턴이 사용되었으므로 에러 발생

만약 이러한 조건을 통해 어떤 작업을 하고 싶다면 if let 구문을 사용해 위 케이스가 false가 되도록 해야 함

```rust
if let Some(x) = some_option_value {
    // do something...
}
```

---

패턴 문법

- 리터럴 매칭 : 패턴과 리터럴을 직접 매칭

```rust
let x = 1;
match x {
    1 => println!("one"),
    2 => println!("two"),
    _ => println!("else"),
}
```

- 명명된 변수 매칭

명명된 변수는 어떤 값과도 매칭되는 반박 불가능한 패턴

match 식에서 명명된 변수를 사용할 때, match는 새로운 스코프를 시작하기 때문에 match 내부에서 선언된 변수는 match 외부의 같은 이름의 변수를 무시하게 됨

```rust
fn main() {
    let x = Some(5);
    let y = 10;

    match x {
        Some(50) => println!("Got 50"),
        Some(y) => println!("Matched, y = {y}"),
        _ => println!("Default case, x = {:?}", x),
    }

    println!("at the end: x = {:?}, y = {y}", x);
}
```

위 예에서 match 바깥에 y가 선언되었지만, match 내부에 선언된 y는 새로운 y이며, Some 내부의 값으로 매칭되며, 이 때는 x와 매칭됨 

따라서 Some(y) 와 매칭되어 `Matched, y = 5` 가 먼저 출력되고, 이후 match 바깥의 y=10에 의해 `at the end: x = Some(5), y = 10` 를 출력함

- 다중 패턴

match 에서 `|` 를 이용해 여러 패턴과 매칭 가능

```rust
let x = 1;
match x {
    1 | 2 => println!("one | two"),
    _ => println!("else"),
}
```

- ..= 를 이용한 범위 매칭

1..=5 : 1,2,3,4,5 중 하나를 의미, 즉 1|2|3|4|5

아주 긴 범위 매칭 등에 유용

```rust
let x = 1;
match x {
    1..=5 => println!("one ~ five"),
    _ => println!("else"),
}
```

숫자 외에 char 등에도 가능

- 값 해체하여 분리하기

구조체, 열거형, 튜플 등을 분해해 부분 값들을 쓰기 위해 패턴을 사용할 수 있음

```rust
struct Point {
    x: i32,
    y: i32,
}

fn main() {
    let p = Point { x: 0, y: 7 };

    let Point { x, y } = p;
    assert_eq!(0, x);
    assert_eq!(7, y);
}
```

let 으로 새로 선언한 Point에 p의 구조체 값 순서대로 x,y 값을 매칭함

아래와 같이 match를 이용해 구조체의 특정 값 조건에 대한 작업 수행 가능

```rust
fn main() {
    let p = Point { x: 0, y: 7 };

    match p {
        Point { x, y: 0 } => println!("On the x axis at {x}"),
        Point { x: 0, y } => println!("On the y axis at {y}"),
        Point { x, y } => {
            println!("On neither axis: ({x}, {y})");
        }
    }
}
```

열거형에도 마찬가지로 적용 가능

```rust
enum Color {
    Rgb(i32, i32, i32),
    Hsv(i32, i32, i32),
}

enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(Color),
}

fn main() {
    let msg = Message::ChangeColor(Color::Hsv(0, 160, 255));

    match msg {
        Message::ChangeColor(Color::Rgb(r, g, b)) => {
            println!("Change color to red {r}, green {g}, and blue {b}");
        }
        Message::ChangeColor(Color::Hsv(h, s, v)) => {
            println!("Change color to hue {h}, saturation {s}, value {v}")
        }
        _ => (),
    }
}
```

msg 는 Color::Hsv 가 할당되어 있으므로 두 번째 match 문이 동작함

- `_` : 패턴에서 값 무시하기

무시하고자 하는 특정 부분은 _ 로 처리 가능

```rust
let numbers = (2, 4, 8, 16, 32);

match numbers {
    (first, _, third, _, fifth) => {            println!("Some numbers: {first}, {third}, {fifth}")
    }
}
```

그리고 변수명 앞에 _를 붙힘으로써 사용하지 않는 변수 무시하는 것 가능

`let _x = 5;` 라 선언 후 _x 사용 안 해도 컴파일 상에서 경고 발생하지 않음

- .. 으로 나머지 부분 무시하기

.. 을 이용해 사용되지 않는 나머지 부분 무시 가능

단 .. 이용 시 범위가 애매해지면 안 되므로 조심해야 함

```rust
struct Point {
    x: i32,
    y: i32,
    z: i32,
}

let origin = Point { x: 0, y: 0, z: 0 };

match origin { 
    Point { x, .. } => println!("x is {}", x),
}
```

- 매치 가드를 사용한 추가 조건 (match guard)

매치 가드 : match 에서 패턴에 대한 조건을 추가한 것

예를 들어 아래 예제는 num 이 Some(x) 와 매칭이 되고 x % 2 == 0 라는 추가 조건을 만족하는 경우 최종 매칭되는 케이스

```rust
let num = Some(4);
match num {
    Some(x) if x % 2 == 0 => println!("even"),
    Some(x) => println!("odd"),
    None => (),
}
```

num = 4 이므로 첫 번째에서 매칭이 완료됨

이와 같이 match 에 추가적인 if 를 적용함으로써 추가 조건을 만족할 때만 매칭되도록 할 수 있음

앞서 match 내부에서 선언한 변수는 match 외부 변수와 이름이 같더라도 별도의 변수로 동작하는 케이스가 있었음

그러한 경우를 방지하는 것이 매치 가드

아래와 같이 y가 match 외부에 선언되어 있더라도, match 내부의 if 는 match 내부에 선언된 변수가 아니라 매치 가드로 사용된 y 값이므로, match 외부의 y를 가리키고 있음

```rust
fn main() {
    let x = Some(5);
    let y = 10;

    match x {
        Some(50) => println!("Got 50"),
        Some(n) if n == y => println!("Matched, n = {n}"),
        _ => println!("Default case, x = {:?}", x),
    }

    println!("at the end: x = {:?}, y = {y}", x);
}
```

