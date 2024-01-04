ch5

구조체 선언 : key : value 형태로 선언하고 , 로 구분

```rust
struct User {
    active: bool,
    name: String,
    email: String,
    sign_in_count: u64,
}
```

구조체 선언 시 let user = User {...} 와 같이 선언하며, 가변으로 선언시 마찬가지로 mut 추가해야함.

```rust
let mut user1 = User {
    active: true,
    name: String::from("name123"),
    email: String::from("email@abc.com"),
    sign_in_count: 1,
};

user1.name = String::from("name_change");
```
가변 선언 시 특정 필드만 가변으로는 선언 불가함.

구조체 사용 시 key 값 입력을 안 하면 기존 순서에 맞게 value 부여되며, 함수 리턴 값으로 구조체 사용 가능

..user1 과 같이 입력하여 구조체 필드 값을 카피하면 해당 필드 이후의 모든 value 값이 카피된다.

이 때 주의할 점은 String과 같이 카피에 따라 기존 변수가 사용 불가한 경우, 구조체 변수 또한 사용 불가하며, u64와 같이 스택만을 이용한 데이터의 카피 시 기존 변수가 사용 가능하다.

```rust
fn main() {
    let mut user1 = User {
        active: true,
        name: String::from("name123"),
        email: String::from("email@abc.com"),
        sign_in_count: 1,
    };

    user1.name = String::from("name_change");

    let user2 = User{
        ..user1
    };

    println!("{}", user1.name); // error : user1의 name 타입은 String 타입이므로 힙에 데이터 저장되어 move 발생 
    println!("{}", user1.active); // no error : active는 bool 타입이므로 스택에 데이터 저장
}
```

---

직접 작성한 구조체는 별도 디버그 기능이 없으므로 이를 추가해주어야 함 ( #[derive(Debug)] )

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let rect1 = Rectangle {
        width: 30,
        height: 50,
    };

    println!("rect1 is {:?}", rect1);
}
```

출력 시 {:?} 대신 {:#?} 사용하면 줄 바꿈이 포함된 구조체 전체 구조를 보여줌

특정 필드에 대한 디버깅을 진행하고 싶다면 아래와 같이 해당 필드에 dbg!(value) 형식으로 지정

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let scale = 2;
    let rect1 = Rectangle {
        width: dbg!(30 * scale),
        height: 50,
    };

    dbg!(&rect1);
}
```

---

메소드 문법

각 구조체에 대해 impl 키워드로 메소드 작성

구조체 그 자체를 읽기 위해서는 &self를 파라미터로 입력받는다. 구조체 내용을 변경하고 싶다면 &mut self를 파라미터로 받는다.

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn print_area(&self) {
        println!("area : {}", self.area());
    }

    fn change_width(&mut self, new_width: u32) {
        self.width = new_width;
    }
}

fn main() {
    let mut rect = Rectangle {
        width: 30,
        height: 50,
    };

    rect.print_area();

    rect.change_width(50);

    rect.print_area();
}
```

impl 시 구조체 그 자체에 대한 무언가를 할 때 &self 가 아닌 self로 선언하면 구조체 자체에 대한 move가 발생하여 이후 해당 구조체 변수 사용이 불가능함.

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn print_area(&self) {
        println!("area : {}", self.area());
    }

    fn change_width(&mut self, new_width: u32) {
        self.width = new_width;
    }

    fn moved(self) {
        println!("move!!! {:?}", self);
    }
}

fn main() {
    let mut rect = Rectangle {
        width: 30,
        height: 50,
    };

    rect.print_area();

    rect.change_width(50);

    rect.print_area();

    // rect.moved(); // self 선언 시 참조자(&) 없이 그냥 선언하여 사용하였으므로 moved() 함수 실행과 동시에 rect 변수에 대한 move 발생하여 이후 rect 변수는 사용 불가

    println!("{:?}", rect);
}
```

메소드 실행 시 C의 ., -> 와 같이 참조 구분은 따로 없이 자동으로 선언된 파라미터에 맞게 지정함

구조체 자체에 대한 리턴 시 Self 로 리턴. 아래와 같이 sq 변수 선언 시 Rectangle 구조체 가지게 됨.

```rust
impl Rectangle {
    fn square(size: u32) -> Self {
        Self {
            width: size,
            height: size,
        }
    }
}

let sq=Rectangle::square(3);
```



