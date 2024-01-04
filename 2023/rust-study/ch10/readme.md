ch10

generic 타입 : 프로그래밍 언어에서 중복되는 개념을 처리하기 위한 도구

rust에서 함수는 i32, String 같은 구체적인 타입 외에 제네릭 타입을 파라미터로 받을 수 있다.

제네릭 예시 : Option<T>, Vec<T>, Result<T, E> 등 

--- 

제네릭 데이터 타입

리스트에서 가장 큰 값을 갖는 원소를 찾는 함수가 아래와 같을 때 리스트를 이루는 원소의 타입이 다르다면?

```rust
fn largest_i32(list: &[i32]) -> &i32 { // i32를 갖는 슬라이스 의미, vector 넣어도 알맞게 형변환 이루어짐
    let mut largest = &list[0];
    for item in list {
        if item > largest {
            largest = item;
        }
    }

    largest
}

fn largest_char(list: &[char]) -> &char {
    let mut largest = &list[0];
    for item in list {
        if item > largest {
            largest = item;
        }
    }

    largest
}

fn main() {
    let number_list = vec![12, 34, 56, 78];
    let char_list = vec!['a', 'b', 'c', 'd'];
    let result = largest_i32(&number_list);
    println!("{}", result);
    let result = largest_char(&char_list);
    println!("{}", result);
}
```

largest_number, largest_char 함수는 input 타입 외에 모든 것이 동일. 이럴 때 제네릭 타입을 이용해 하나로 함수를 구성할 수 있다.

제네릭 타입 지정 시 매개변수 이름은 보통 T로 지정 (type 의미)

그리고 제네릭 타입이라는 것을 알려주기 위해 <T>를 함수 이름에 포함하여야 한다.

아래와 같이 구성 가능 (아직은 컴파일 안 됨)

```rust
fn largest<T>(list: &[T]) -> &T {
    let mut largest = &list[0];
    for item in list {
        if item > largest { // error : 모든 T가 될 수 있는 타입에 대해서 > 가 정의 안 되어 있기 때문에 나타남
            largest = item;
        }
    }
    largest 
}
fn main() {
    let number_list = vec![12, 34, 56, 78];
    let char_list = vec!['a', 'b', 'c', 'd'];
    let result = largest(&number_list);
    println!("{}", result);
    let result = largest(&char_list);
    println!("{}", result);
}
```

구조체에 대해서도 제네릭 타입으로 구성 가능

```rust
struct Point<T> {
    x: T,
    y: T,
}

fn main() {
    let intP = Point {x: 1, y: 2};
    let floatP = Point {x: 1.0, y: 2.0};
}
```

하지만 제네릭 타입 적용하여도 현재 T로 동일한 타입으로 구성하였으므로 x, y 모두 같은 타입이어야 한다.

서로 다른 타입을 허용하고 싶다면 제네릭 타입 2개 지정하면 된다.

```rust
struct Point<T, U> {
    x: T,
    y: U,
}
fn main() {
    let intP = Point {x: 1, y: 2};
    let floatP = Point {x: 1.0, y: 2.0};
    let mixP = Point {x: 1, y : 2.0};
}
```

제네릭 메소드 정의

구조체나 열거형에 메소드를 정의할 때 제네릭 타입을 이용할 수 있다.

제네릭 타입에 대한 메서드 선언 시 impl<T> 와 같이 마찬가지로 제네릭 타입으로 구현한다는 의미를 추가하여야 한다.

하지만 distance 함수와 같이 직접적으로 타입 명시도 가능하다. 이 때는 impl 뒤에 타입 선언 안 한다. 단, 해당 타입을 제외한 타입에 대해서는 해당 함수를 불러 올 수 없다.

```rust
struct Point<T, U> {
    x: T,
    y: U,
}

impl<T, U> Point<T, U> {
    fn x(&self) -> &T {
        &self.x
    }
}

impl Point<f32, f32> {
    fn distance(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}
```

---

trait : 특정 타입이 가지고 있는 기능을 다른 타입과 공유할 수 있는 기능 (다른 언어의 interface와 비슷한 기능)

트레잇 바운드를 이용하면 제네릭 타입 자리에 특정한 동작을 하는 타입 올 수 있음을 명시할 수 있다.

트레잇 정의

ex) NewsArticle 구조체와 Tweet 구조체로 이루어진 인스턴스에 저장된 데이터를 종합하는 크레이트 aggregator를 만든다.

각 타입의 요약 정보를 summarize 메소드를 호출하여 가져오려고 할 때 Summary 트레잇으로 이를 표현한다.

```rust
pub trait Summary {
    fn summarize(&self) -> String;
}
```

Summary 트레잇을 위와 같이 구성하면 Summary 트레잇을 사용하는 구조체는 반드시 summarize 함수를 구현해야 한다.

형식 : impl trait_name for struct_name {.....}

```rust
// src/lib.rs
pub trait Summary {
    fn summarize(&self) -> String;
}

pub struct NewsArticle {
    pub headline: String,
    pub location: String,
    pub author: String,
    pub content: String,
}

impl Summary for NewsArticle {
    fn summarize(&self) -> String {
        format!("{}, by {} ({})", self.headline, self.author, self.location)
    }
}

pub struct Tweet {
    pub username: String,
    pub content: String,
    pub reply: bool,
    pub retweet: bool,
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}
```

트레잇을 사용하고자 하는 스코프 내로 가져와 아래와 같이 사용 가능

```rust
// src/main.rs
use aggregator::{Summary, Tweet};

fn main() {
    let tweet = Tweet {
        username: String::from("ebook"),
        content: String::from("of course"),
        reply: false,
        retweet: false,
    };

    println!("{}", tweet.summarize());
}
```

트레잇을 이용하여 크레이트에 의존적인 다른 크레이트 또한 해당 트레잇에 맞는 함수를 구현할 수 있다.

예를 들어, aggregator 트레잇 내부의 Tweet 타입에 표준 라이브러리인 Display 를 구현할 수 있고, 

표준 라이브러리인 Vec<T> 타입에 summary 함수를 구현할 수 있다.

하지만 외부 타입에 다른 외부 트레잇을 구현할 수는 없다.

예를 들어 Vec<T> 타입에 대해 Display 트레잇을 구현할 수는 없다. (둘 다 서로 다른 표준 라이브러리에 있기 때문)

---

트레잇의 기본 구현

기본 기능을 담당하는 함수를 미리 구현할 수 있다.

```rust
pub trait Summary {
    fn summarize_author(&self) -> String;

    fn summarize(&self) -> String {
        format!("Read more .... {}", self.summarize_author())
    }
}

pub struct NewsArticle {
    pub headline: String,
    pub location: String,
    pub author: String,
    pub content: String,
}

impl Summary for NewsArticle {

    fn summarize_author(&self) -> String {
        format!("@{}", self.author)
    }
}
```

위 코드에서 NewsArticle 구조체에 대해서 summarize_author 함수만을 구현하면 summarize 함수는 Summary 트레잇에서 기본 구현이 되어 있기 때문에 호출이 가능하다.

하지만 오버라이딩하여 NewsArticle에 summarize 함수를 따로 구현하면 기본 구현된 summarize 함수는 호출할 수 없다.

트레잇의 매개변수 적용

트레잇을 함수의 매개변수로 사용할 수 있다.

Summary 트레잇을 구현한 어떤 타입을 item이라고 하면 아래와 같이 notify 함수를 구현할 수 있다.

```rust
pub fn notify(item: &impl Summary) {
    println!("News! : {}", item.summarize());
}
```

트레잇 바운드 : 트레잇을 제네릭처럼 사용하여 매개변수가 여러 개이면서 동일한 타입으로 강제할 때 아래와 같이 구성이 가능하다.

```rust
pub fn notify<T: Summary>(item1: &T, item2: &T) {
    println!("News! : {}, {}", item1.summarize(), item2.summarize());
}
```

트레잇 여러 개에 대해서 구현하려면 제네릭과 동일하게 <T: trait1, U: trait2> 형식으로 제한하면 된다.

또한 여러 개의 트레잇에 대해 함수의 파라미터로 들어갈 수 있도록 + 로 트레잇 제한을 둘 수 있다. ("or" 의미)

```rust
pub fn notify(item: &(impl Summary + Display)) {}

// 위 아래 다 가능

pub fn notify<T: Summary + Display>(item: &T) {}
```

하지만 이런 트레잇 바운드가 너무 많으면 가독성이 떨어지기 때문에 where를 이용해 제한을 둘 수 있다.

```rust
fn some_function<T: Display + Clone, U: Clone + Debug>(t: &T, u: &U) -> i32 {}

// 위 아래는 동일

fn some_function<T, U>(t: &T, u: &U) -> i32
where
    T: Display + Clone,
    U: Clone + Debug,
{}
```

또한 트레잇을 구현하는 타입을 아래와 같이 리턴시킬 수도 있다. returns_summarizable() 함수 호출 시 Summary를 구현하고 있는 Tweet 인스턴스를 리턴한다.

```rust
fn returns_summarizable() -> impl Summary {
    Tweet {
        username: String::from("horse_ebooks"),
        content: String::from(
            "of course, as you probably already know, people",
        ),
        reply: false,
        retweet: false,
    }
}s
```

하지만 다른 타입을 리턴시키도록 함수를 구성할 수는 없다. (이것이 가능하도록 하는 것은 17.2장에 나옴)

```rust
// compile error 
fn returns_summarizable(switch: bool) -> impl Summary {
    if switch {
        NewsArticle {
            headline: String::from(
                "Penguins win the Stanley Cup Championship!",
            ),
            location: String::from("Pittsburgh, PA, USA"),
            author: String::from("Iceburgh"),
            content: String::from(
                "The Pittsburgh Penguins once again are the best \
                 hockey team in the NHL.",
            ),
        }
    } else {
        Tweet {
            username: String::from("horse_ebooks"),
            content: String::from(
                "of course, as you probably already know, people",
            ),
            reply: false,
            retweet: false,
        }
    }
}
```

---

라이프타임 : 일반적인 언어에서 참조자의 라이프타임을 명시하는 것은 일반적이지 않다.

```rust
fn main() {
    let r;
    {
        let x = 5;
        r = &x; // erroe by x is dropped
    }

    println!("{}", r);
}
```

위 코드에서 x의 scope는 중괄호까지이므로 r에 x의 참조자를 대입하면 중괄호 벗어날 때 x의 라이프타임이 끝나 r을 print 할 수 없다. (r이 빈 값이므로)

함수에서의 라이프타임 (제네릭 라이프타임)

아래와 같은 코드도 컴파일 에러

```rust
fn main() {
    let s1 = String::from("abcdef");
    let s2 = "xyz";

    let result = longest(s1.as_str(), s2);
    println!("{}", result);
}

fn longest(s1: &str, s2: &str) -> &str { // error 
    if s1.len() > s2.len() {
        s1
    } else {
        s2
    }
}
```

컴파일 시 longest 함수에서 리턴될 참조자가 x인지 y인지 모른다는 에러 발생 (왜냐면 if에 따라 x일 수도 있고 y일 수도 있음)

이런 경우 라이프타임을 명시해주어야 한다. ('a) (여러 개의 라이프타임이 필요한 경우 'a, 'b, 'c 등을 이용할 수 있음)

라이프타임을 명시한다고 하여 참조자의 라이프타임이 바뀌지는 않지만 어떠한 라이프타임을 갖는 참조자든 전달할 수 있다.

```rust
fn main() {
    let s1 = String::from("abcdef");
    let s2 = "xyz";

    let result = longest(s1.as_str(), s2);
    println!("{}", result);
}

fn longest<'a>(s1: &'a str, s2: &'a str) -> &'a str {
    if s1.len() > s2.len() {
        s1
    } else {
        s2
    }
}
```


