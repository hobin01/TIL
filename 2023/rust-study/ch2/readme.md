ch2

let, match 등 기본적인 구조 : 랜덤 숫자 맞추기 게임으로

- 사용하고자 하는 라이브러리 스코프 지정

```rust
use std::io;
```

- 변수 지정

rust에서 let으로 선언하면 기본적으로 immutable

mutable 변수 선언하려면 let mut

```rust
let apple = 5; // immutable
let mut banana = 5; // mutable
```

- 인스턴스 생성

가변 변수 guess에 String 인스턴스를 생성

```rust
let mut guess = String::new();
```

- 입력 받기

```rust
io::stdin()
	.read_line(&mut guess)
	.expect("failed to read line");
```

use std::io 선언했기 때문에 io::stdin() 으로 사용 가능

선언 안 하면 std::io::stdin() 으로 작성해야 함

.read_line(&mut guess) : & : 메모리 참조자, guess를 가변으로 선언했기 때문에 &mut guess 와 같이 선언 (rust에서 메모리 참조자도 기본적으로 불변이기 때문)

.expect() : 에러 처리 구문. 작성하지 않아도 경고로 넘어가면서 컴파일은 됨.

- 변수 값 출력

```rust
println!("You guessed: {guess}");
```

{} 안에 변수 지정 가능, 아래와 같이도 출력 가능

```rust
println!("You guessed: {}", guess);
```

---

Crate : 러스트 코드 묶음 (패키지, 라이브러리)

Cargo.toml의 dependencies에 

Crate 이름 = "버전" 

형식으로 입력하고 cargo build 로 빌드하면 됨. (이 때 필요한 다른 크레이트 파일도 가져옴)

ex) rand = "0.8.5" // 0.8.5 ~ 0.8.9 버전 의미 

가져온 크레이트 버전은 Cargo.lock 파일에 기록되어 추후 버전 업데이트가 필요하더라도 충돌 안 나는 범위에서 업데이트 진행함.

(업데이트 : cargo update)

---

rust에서는 타입 다르지만 이름 같은 변수 선언 가능 

```rust
let mut guess = String::new();
let guess: u32 = guess.trim().parse();
```

match : 일종의 if문

match 뒤에 나오는 파라미터 결과 => math 문 결과 형식으로 이루어짐 

let x = match option {...} 과 같이 x에 결과 대입도 가능

loop : 무한 루프

String.trim().parse() : 결과는 Result 라는 enum 타입 : Ok, Err 가짐

- 최종 예제

```rust
use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    println!("Guess the number!");

    // 1 ~ 100 random number
    let secret_number = rand::thread_rng().gen_range(1..=100);

    loop {

        println!("Input your number.");

        let mut guess = String::new();

        // stdin to guess
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        
        // parse to u32
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num, // num : result of parsing
            Err(_) => continue, // Err(_) : any error value
        }; // 대입하는 것이므로 ; 필요

        println!("You guessed : {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("small!"),
            Ordering::Greater => println!("big!"),
            Ordering::Equal => {
                println!("same!!!!!");
                break; // break loop
            },
        }
    }
}
```
