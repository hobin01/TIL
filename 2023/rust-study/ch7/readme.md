ch7

rust 프로젝트 관리

- Package : 
크레이드를 빌드하고, 테스트하고, 공유하는데 사용

- Crate : 
라이브러리나 실행 가능한 모듈로 구성된 트리 구조

- Module, use : 
구조, 스코프를 제어하고, 조직 세부 경로를 감춤

- Path : 
구조체, 함수, 모듈 등의 이름 지정 

---

크레이트 (Crate) : rust가 컴파일 차례에 고려하는 가장 작은 코드 단위

rustc로 단일 코드 파일 컴파일 시에도 이를 크레이트로 생각하고 컴파일한다.

바이너리 크레이트 : 실행 파일 단위로 컴파일할 수 있는 프로그램. main 함수를 포함해야 한다.

라이브러리 크레이트 : main함수 없어 실행 파일로 컴파일되지는 않지만 라이브러리로 사용되는 파일.

일반적으로 rust에서 크레이트라 하면 라이브러리 크레이트를 의미

패키지는 어떤 기능을 제공하는 하나 이상의 크레이트 묶음. 

패키지에는 여러 개의 바이너리 크레이트를 포함할 수 있지만, 라이브러리 크레이트는 하나만 넣을 수 있다.

실제로 Cargo.toml 파일에는 바이너리 크레이트의 루트인 src/main.rs가 따로 명시되어 있지는 않음.

어떤 패키지가 src/main.rs와 src/lib.rs (라이브러리 파일)을 가지고 있다면 해당 패키지는 패키지와 같은 이름의 바이너리, 라이브러리 크레이트를 포함하게 된다.

src/bin 디렉토리에 파일을 배치하면 각 파일이 바이너리 크레이트가 된다.

---

- 크레이트 루트부터 시작 : 크레이트 컴파일 시 크레이트 루트부터 컴파일을 시작

라이브러리 크레이트 루트 : src/lib.rs, 바이너리 크레이트 루트 : src/main.rs

- 모듈 선언 : 크레이트 루트 파일에는 모듈 선언 가능

garden이라는 모듈을 사용하려면 아래 위치에서 garden 모듈이 있는지 컴파일러가 확인

1. 인라인, mod garden 뒤에 중괄호 쓴 곳의 안 쪽
2. src/garden.rs 파일 안
3. src/garden/mod.rs 파일 안

- 서브 모듈 선언 : 크레이트 루트가 아닌 다른 파일에서 서브 모듈 선언이 가능

src/garden.rs 안에 mod vegetables; 를 선언함으로써 아래 경로에 vegetable 모듈이 있는지 컴파일러가 확인

1. 인라인, mod vegetables 뒤에 중관로 쓴 곳의 안 쪽
2. src/garden/vegetables.rs 파일 안
3. src/garden/vegetables/mod.rs 파일 안

- 모듈 내 코드로의 경로 : 모듈이 크레이트의 일부로 구성되면 공개 규칙 허용 한도 내에서 해당 코드의 경로를 사용하여 동일 크레이트 내에서 모듈 코드 참조 가능

garden::vegetables 모듈 안에 있는 Asparagus 타입은 아래와 같이 사용 가능

```rust
crate::garden::vegetables::Asparagus
```

- 비공개 vs 공개 : 모듈 내의 코드는 부모 모듈에게는 기본적으로 private으로 지정. 모듈 공개하려면 pub mod를 선언하여야 하고, 타입, 함수 등에도 pub 키워드 붙여야 한다.

- use 키워드 : 경로 탐색을 위한 단축키 역할

crate::garden::vegetables::Asparagus 타입 사용을 위해 일일이 이렇게 작성하는 것이 아닌,

사용하고자 하는 스코프 내에서 use crate::garden::vegetables::Asparagus; 를 선언하면 Asparagus 타입을 사용 가능

example

module 이라는 이름의 바이너리 크레이트를 만들고, 트리 구조가 아래와 같을 때

```
module
├── Cargo.lock
├── Cargo.toml
└── src
    ├── garden
    │   └── vegetables.rs
    ├── garden.rs
    └── main.rs
```

src/main.rs

```rust
use crate::garden::vegetables::Asparagus;

pub mod garden;

fn main() {
    let plant = Asparagus {};
    println!("I'm growing {:?}!", plant);
}
```

pub mod garden; 라인으로 컴파일러에게 src/garden.rs에 있는 코드를 포함할 것을 알려준다.

src/garden.rs

```rust
pub mod vegetables;
```

pub mod vegetables; 라인으로 컴파일러에게 src/garden/vegetables.rs의 코드를 포함할 것을 알려준다.

src/garden/vegetables

```rust
#[derive(Debug)]
pub struct Asparagus {}
```

라이브러리 크레이트 생성 시 cargo new --lib library_name 과 같이 선언하면 라이브러리 크레이트 생성됨.
(cargo build)

restaurant 라이브러리 예시

src/lib.rs

```rust
mod front_of_house {
    mod hosting {
        fn add_to_waitlist() {}

        fn seat_at_table() {}
    }

    mod serving {
        fn take_order() {}

        fn serve_order() {}

        fn take_payment() {}
    }
}
```

---

모듈 경로에는 2가지 형태 존재

절대 경로 : 외부 크레이트 코드는 해당 크레이트 이름을 시작으로, 현재 크레이트 코드는 crate:: 으로 시작

상대 경로 : 현재 모듈을 시작으로 self, super 등의 키워드 사용하여 식별자 지정

```rust
mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }
}

pub fn eat_at_restaurant() {
    crate::front_of_house::hosting::add_to_waitlist(); // absolute path
    front_of_house::hosting::add_to_waitlist(); // relative path
}
```

위와 같이 지정 시 hosting 모듈, add_to_waitlist() 함수는 기본값 private으로 지정되었으므로 pub 키워드를 붙혀야 함.

super로 시작하는 상대 경로 지정은 부모 모듈로부터 시작하는 상대 경로와 동일

```rust
fn deliver_order() {}

mod back_of_house {
    fn fix_incorrect_order() {
        cook_order();
        super::deliver_order();
    }

    fn cook_order() {}
}
```

fix_incorrect_order 함수는 back_of_house 모듈 내에 위치하므로 super는 back_of_house의 부모 모듈 (여기서는 루트)를 의미 

구조체에 pub 키워드 지정 시 구조체를 구성하는 필드는 아직 private으로 이루어짐

이를 공개하려면 필드에도 pub 키워드를 지정하여야 함.

```rust
mod back_of_house2 {
    pub struct Breakfast {
        pub toast: String,
        seasonal_fruit: String,
    }

    impl Breakfast {
        pub fn summer(toast: &str) -> Breakfast {
            Breakfast {
                toast: String::from(toast),
                seasonal_fruit: String::from("peaches"),
            }
        }
    }
}

pub fn eat_at_restaurant2() {
    // Order a breakfast in the summer with Rye toast
    let mut meal = back_of_house2::Breakfast::summer("Rye");
    // Change our mind about what bread we'd like
    meal.toast = String::from("Wheat");
    println!("I'd like {} toast please", meal.toast);

    // The next line won't compile if we uncomment it; we're not allowed
    // to see or modify the seasonal fruit that comes with the meal
    // meal.seasonal_fruit = String::from("blueberries"); // error by private
}
```

열거형 (enum)은 pub 키워드 지정 시 모든 변수가 공개됨.

```rust
mod back_of_house {
    pub enum Appetizer {
        Soup,
        Salad,
    }
}

pub fn eat_at_restaurant() {
    let order1 = back_of_house::Appetizer::Soup;
    let order2 = back_of_house::Appetizer::Salad;
}
```

---

use 키워드 사용

use 키워드 사용하여 해당 모듈에 정의된 내용을 사용함을 의미 (일종의 shortcut)

```rust
mod front_of_house4 {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }
}

use crate::front_of_house4::hosting;

pub fn eat_at_restaurant4() {
    hosting::add_to_waitlist();
}
```

단 use 키워드는 사용된 스코프에 대해서만 shortcut이 적용됨에 유의해야 한다.

```rust
mod front_of_house5 {
    pub mod hosting5 {
        pub fn add_to_waitlist() {}
    }
}

use crate::front_of_house5::hosting5;

mod customer {
    pub fn eat_at_restaurant() {
        // hosting5::add_to_waitlist(); // error by scope of hosting5
        super::hosting5::add_to_waitlist();
    }
}
```

위 처럼 use 키워드의 scope가 현재 모듈을 의미하므로 customer 모듈에 포함되지 않음. 그러므로 customer 모듈에서도 hosting5를 사용하기 위해서는 
customer 모듈 내에서 use 키워드를 적용하거나 super::로 상위 모듈에 있음을 명시하여야 함.

기본으로 제공되는 std 모듈의 경우 일반적으로 함수 이름이나 모듈명까지 작성하는 것이 관용적이다. 하지만 동일한 이름의 모듈을 갖고 있을 때는 구분하는 것이 바람직하다.

```rust
use std::fmt;
use std::io;

fn function1() -> fmt::Result {
    // --snip--
}

fn function2() -> io::Result<()> {
    // --snip--
}
```

또는 as 키워드로 별칭을 두어 구분하도록 한다.

```rust
use std::fmt::Result;
use std::io::Result as IoResult;

fn function1() -> Result {
    // --snip--
}

fn function2() -> IoResult<()> {
    // --snip--
}
```

그리고 restaurant 모듈이 아래와 같이 구성되어 있다면 pub use 키워드를 이용해 shortcut을 지정할 수 있다.

```rust
mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }
}

pub use crate::front_of_house::hosting;

pub fn eat_at_restaurant() {
    hosting::add_to_waitlist(); // same as restaurant::hosting::add_to_waitlist();
}
```

---

외부 패키지 사용

toml 파일의 dependencies 부분에 사용하고자 하는 패키지 명시

rand = "0.8.5"

```rust
use rand::Rng;

fn rng_1to100() {
    rand::thread_rng().gen_range(1..=100);
}
```

동일 경로가 중첩되는 경우 {}로 묶어서 처리 가능. 아래는 동일한 경우를 의미하며, 자기 자신을 의미하는 경우 self로 명시

```rust
use std::cmp::Ordering;
use std::io;

// same as
use std::{cmp::Ordering, io};
```

```rust
use std::io;
use std::io::Write;

// same as
use std::io::{self, Write};
```

*(글롭 연산자)를 이용해 모든 공개 항목을 가져올 수 있음

```rust
use std::collections::*;
```

---

별개 파일로 모듈 분리

루트 모듈 (src/lib.rs)과 src/front_of_house.rs 파일을 생성하여 아래와 같이 사용 가능하다.

```rust
// src/lib.rs

mod front_of_house;

pub use crate::front_of_house::hosting;

pub fn eat_at_restaurant() {
    hosting::add_to_waitlist();
}
```

```rust
// src/front_of_house.rs

pub mod hosting {
    pub fn add_to_waitlist() {}
}
```

그리고 아래와 같이도 분리할 수 있다. 

```rust
// src/front_of_house.rs

pub mod hosting;
```

```rust
// src/front_of_house/hosting.rs

pub fn add_to_waitlist() {}
```

이처럼 해당 모듈 내에서 모듈을 직접 정의하지 않고 사용할 이름만 정의하고 디렉토리 구조로 세부 내용을 작성할 수 있다.

예전 스타일로 작성된 모듈 관리의 경우 src/front_of_house.rs 대신 src/front_of_house/mod.rs 형태로도 구성된 경우가 있으며, 이는 현재까지도 유효하므로 주의.

