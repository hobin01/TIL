ch17

객체 지향의 일반적인 특징들
- 객체
- 캡슐화
- 상속
- ...

객체지향프로그래밍 : 객체로 구성된 프로그래밍, 객체는 데이터 및 데이터를 활용하는 프로시저를 묶고, 프로시저들은 메서드 혹은 연산이라 부름

캡슐화 : 객체를 이용하는 코드에서 객체의 상세 구현에 접근할 수 없게 하는 것

객체와 직접 상호작용하기 위해서는 객체 코드를 공개하는 수 밖에 없음 

rust에서는 pub 키워드를 이용해서 공개 여부 결정

이를 이용해서 캡슐화가 가능

```rust
pub struct AveragedCollection {
    list: Vec<i32>,
    average: f64,
}

impl AveragedCollection {
    pub fn add(&mut self, value: i32) {
        self.list.push(value);
        self.update_average();
    }

    pub fn remove(&mut self) -> Option<i32> {
        let result = self.list.pop();
        match result {
            Some(value) => {
                self.update_average();
                Some(value);
            }
            None => None,
        }
    }

    pub fn average(&self) -> f64 {
        self.average
    }

    fn update_average(&mut self) {
        let total: i32 = self.list.iter().sum();
        self.average = total as f64 / self.list.len() as f64;
    }
}
```

위 케이스에서 pub 키워드를 갖는 것은 add, remove, average

update_average 메서드는 외부에서 사용할 수 없음

따라서 average는 어떻게 구해지는 지 알 수 없지만 구해지는 중 

이와 같이 pub 키워드로 세부 구현 사항 캡슐화 가능

---

GUI 툴을 만든다면 사용자가 무슨 타입을 쓸 지 모르므로 각 타입은 기본 기능을 수행하는 데이터 타입으로부터 상속받아 구현하는 것이 일반적

예를 들어, draw라는 이름의 메서드를 갖고 있는 Component라는 클래스를 정의한다면, Button, Image, SelectBox 등은 Component를 상속받아 draw 메서드를 사용할 수 있게 됨

trait object : 트레이트를 구현한 타입의 인스턴스와 런타임에 해당 타입의 트레이트 메서드를 조회하는데 사용되는 테이블을 모두 가리킴

`&, Box<T>` 등 포잍너 타입으로 지정하고, `dyn` 키워드를 추가함으로써 트레이트 객체를 생성할 수 있음 

```rust
pub trait Draw {
    fn draw(&self);
}

pub struct Screen {
    pub components: Vec<Box<dyn Draw>>,
}

impl Screen {
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    }
}
```

위 예와 같이 Draw라는 트레잇을 갖는 데이터 타입을 components로 구성하고 이를 Screen 구조체에 넣음

따라서 components는 Draw 트레잇을 만족하는, 즉 현재까지는 draw 메서드를 구현한 모든 데이터 타입을 사용할 수 있게 됨

이와 유사하게 제네릭을 이용해 다음과 같이 정의도 가능

```rust
pub trait Draw {
    fn draw(&self);
}

pub struct Screen<T: Draw> {
    pub components: Vec<T>,
}

impl<T> Screen<T>
where 
    T: Draw,
{
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    } 
}
```

동일한 타입의 컬렉션만 사용한다면 제네릭 타입을 이용하는 것이 더욱 바람직함

하지만 여러 타입 이용 시 트레잇 객체를 사용하는 것이 좋음

아래는 여러 타입 이용하는 예시

```rust
pub trait Draw {
    fn draw(&self);
}

pub struct Screen {
    pub components: Vec<Box<dyn Draw>>,
}

impl Screen {
    pub fn run(&self) {
        for component in self.components.iter() {
            component.draw();
        }
    }
}

pub struct Button {
    pub width: u32,
    pub height: u32,
    pub label: String,
}

impl Draw for Button {
    fn draw(&self) {
        // draw 내용
    }
}

pub struct SelectBox {
    pub width: u32,
    pub height: u32,
    pub options: Vec<String>,
}

impl Draw for SelectBox {
    fn draw(&self) {
        // draw 내용
    }
}
```

위에서 Button과 SelectBox 모두 Draw를 구현했다고 하면 Draw 트레잇 객체가 되므로 동일 트레잇을 구현한 서로 다른 데이터 타입을 동일한 인스턴스에 기록할 수 있다. 

아래는 그 예제

```rust
use trait_object::{Button, Screen, SelectBox};

fn main() {
    let screen = Screen {
        components: vec![
            Box::new(SelectBox {
                width: 75,
                height: 10,
                options: vec![
                    String::from("Yes"),
                    String::from("Maybe"),
                    String::from("No"),
                ],
            }),
            Box::new(Button {
                width: 50,
                height: 10,
                label: String::from("OK"),
            }),
        ],
    };

    screen.run();
}
```

---

객체 지향 디자인 패턴 구현하기

상태 패턴(state pattern) : 객체 지향 디자인 패턴, 어떤 값이 내부적으로 가질 수 있는 상태 집합을 정의한다는 것

예를 들어 블로그 게시물 구조체의 경우, 초안, 검토, 게시 집합이 상태 객체가 됨 

러스트에서는 객체와 상속보다는 구조체와 트레잇을 주로 사용함 

여기서는 객체 지향 방식으로 상태 패턴 구현한 다음 러스트스러운 방식으로 변경하도록 함

최종 기능은 다음과 같음

1. 블로그 게시물은 빈 초안으로 시작
2. 초안이 완료되면 게시물 검토가 요청됨
3. 게시물이 승인되면 게시됨
4. 게시된 블로그 게시물만이 출력될 내용물을 반환하므로 승인되지 않은 게시물이 실수로 게시되는 것을 방지함

간단한 샘플

```rust
use blog::Post;

fn main() {
    let mut post = Post::new();

    post.add_text("Salad!!!");
    assert_eq!("", post.content());

    post.request_review();
    assert_eq!("", post.content());

    post.approve();
    assert_eq!("Salad!!!", post.content());
}
```

post라는 값을 Post 객체로 새로 생성하고

텍스트 입력 후 비어 있는 지 확인 및 검토, 승인 과정을 거쳐 최종 post 내용이 초기와 같은 지 테스트하도록 함

- 위를 구성하기 위한 구조체들 

Draft : 초안 상태를 의미 

이후에 추가적인 상태 객체를 구현 

```rust
pub struct Post {
    state: Option<Box<dyn State>>,
    content: String,
}

impl Post {
    pub fn new() -> Post {
        Post {
            state: Some(Box::new(Draft{})),
            content: String::new(),
        }
    }
}

trait State {}

struct Draft {}

impl State for Draft {}
```

- Post 구조체에 대한 추가 구현

현재까지는 초안 상태에서만 게시물 구성 가능하므로 "" 리턴하는 부분 추가

```rust
impl Post {
    pub fn new() -> Post {
        Post {
            state: Some(Box::new(Draft{})),
            content: String::new(),
        }
    }

    pub fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }

    pub fn content(&self) -> &str {
        ""
    }
}
```

- 게시물에 대한 검토 요청으로 상태를 변경

Draft 상태에서 검토 요청을 위한 상태로 변경하기 위해 PendingReview 상태로 변경

```rust
pub struct Post {
    state: Option<Box<dyn State>>,
    content: String,
}

impl Post {
    pub fn new() -> Post {
        Post {
            state: Some(Box::new(Draft{})),
            content: String::new(),
        }
    }

    pub fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }

    pub fn content(&self) -> &str {
        ""
    }

    pub fn request_review(&mut self) {
        if let Some(s) = self.state.take() {
            self.state = Some(s.request_review())
        }
    }
}

trait State {
    fn request_revuew(self: Boxx<Self>) - Box<dyn State>;
}

struct Draft {}

impl State for Draft {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        Box::new(PendingReview {})
    }
}

struct PendingReview {}

impl State for PendingReview {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }
}
```

이전 상태를 사용하기 위해 request_review 메서드가 상태 값의 소유권을 가져와야 함

여기서는 Post의 state를 Option으로 선언하였기 때문에 take 메서드를 이용해 state 필드 밖으로 Some 값을 빼고 원래 자리에 None을 남김

그럼으로써 state를 빌리지 않고 Post 밖으로 처리가 가능

- content 동작을 변경하는 approve 메서드 추가

Post의 content 업데이트를 위해 자신의 state에 정의된 content 메서드에 위임을 함

Post의 content 메서드에서 state의 as_ref()가 호출됨으로써 Option<&Box<dyn State>> 가 리턴됨

as_ref 호출하지 않았을 시 &self로부터 빌린 state를 이동시킬 수 없으므로 에러 발생

```rust
pub struct Post {
    state: Option<Box<dyn State>>,
    content: String,
}

impl Post {
    pub fn new() -> Post {
        Post {
            state: Some(Box::new(Draft{})),
            content: String::new(),
        }
    }

    pub fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }

    pub fn content(&self) -> &str {
        self.state.as_ref().unwrap().content(self)
    }

    pub fn request_review(&mut self) {
        if let Some(s) = self.state.take() {
            self.state = Some(s.request_review())
        }
    }

    pub fn approve(&mut self) {
        if let Some(s) = self.state.take() {
            self.state = Some(s.approve())
        }
    }
}

trait State {
    fn request_review(self: Boxx<Self>) - Box<dyn State>;
    fn approve(self: Box<Self>) -> Box<dyn State>;
}

struct Draft {}

impl State for Draft {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        Box::new(PendingReview {})
    }

    fn approve(self: Box<Self>) -> Box<dyn State> {
        self 
    }
}

struct PendingReview {}

impl State for PendingReview {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }

    fn approve(self: Box<Self>) -> Box<dyn State> {
        Box::new(Published {})
    }
}

struct Published {}

impl State for Published {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self 
    }

    fn approve(self: Box<Self>) -> Box<dyn State> {
        self 
    }
}
```

content 메서드에 대해 빈 문자열 슬라이스를 반환하는 부분을 추가하면 아래와 같음

Draft와 PendingReview 구조체에 대한 content 메서드는 구현할 필요 없음

Published 구조체는 content 메서드를 오버라이딩하고 post.content 값을 반환함

```rust
pub struct Post {
    state: Option<Box<dyn State>>,
    content: String,
}

impl Post {
    pub fn new() -> Post {
        Post {
            state: Some(Box::new(Draft{})),
            content: String::new(),
        }
    }

    pub fn add_text(&mut self, text: &str) {
        self.content.push_str(text);
    }

    pub fn content(&self) -> &str {
        self.state.as_ref().unwrap().content(self)
    }

    pub fn request_review(&mut self) {
        if let Some(s) = self.state.take() {
            self.state = Some(s.request_review())
        }
    }

    pub fn approve(&mut self) {
        if let Some(s) = self.state.take() {
            self.state = Some(s.approve())
        }
    }
}

trait State {
    fn request_review(self: Boxx<Self>) - Box<dyn State>;
    fn approve(self: Box<Self>) -> Box<dyn State>;
    fn content<'a>(&self, post: &'a Post) -> &'a str {
        ""
    }
}

struct Draft {}

impl State for Draft {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        Box::new(PendingReview {})
    }

    fn approve(self: Box<Self>) -> Box<dyn State> {
        self 
    }
}

struct PendingReview {}

impl State for PendingReview {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self
    }

    fn approve(self: Box<Self>) -> Box<dyn State> {
        Box::new(Published {})
    }
}

struct Published {}

impl State for Published {
    fn request_review(self: Box<Self>) -> Box<dyn State> {
        self 
    }

    fn approve(self: Box<Self>) -> Box<dyn State> {
        self 
    }

    fn content<'a>(&self, post: &'a Post) -> &'a str {
        &post.content
    }
}
```


