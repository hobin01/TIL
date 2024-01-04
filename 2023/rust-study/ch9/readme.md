ch9

rust에서의 에러처리 : recoverable (복구 가능) / unrecoverable (복구 불가능)

복구 가능 에러 : 파일 찾을 수 없음과 같이 사용자에게 명령 재시도를 요청할 수 있는 에러

복구 불가능 에러 : 오버플로우와 같이 프로그램이 종료되어야 하는 에러

대부분의 언어에서 제공하는 예외 처리 기능이 rust에는 없다.

복구 가능 에러는 Result<T, E> 타입으로 처리, 복구 불가능 에러 발생 시 panic! 매크로 발생

---

일반적으로 panic! 매크로 발생 시 프로그램 상에서 스택을 unwind (되감기) 하면서 스택을 비운다.

하지만 이는 프로그램 상에서 높은 cost가 들기 때문에 대안으로 OS 상에서 스택을 비우게 만들고 프로그램은 즉시 종료되는 aborting 기능을 사용할 수 있다.

release 모드에서 aborting 기능을 사용하려면 Cargo.toml 파일에 다음을 추가한다.

```rust
[profile.release]
panic = 'abort'
```

panic! 매크로로 panic 발생은 아래와 같이 

```rust
fn main() {
    panic!("panic!!!!");
}
```

에러로 나오는 내용은 아래와 같음

```rust
thread 'main' panicked at 'panic!!!!', src/main.rs:2:5
note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
```

첫 번째 줄은 현재 파일에서 panic이 발생한 위치와 panic 내용을 알려주며, 두 번째 줄은 외부 코드에 있을 수 있는 panic 위치를 명시해준다. 

backtrace를 사용해 외부 파일에서 발생했을 수 있는 panic을 추적할 수 있다.

backtrace : 어떤 지점에 도달하기까지 호출한 모든 함수의 목록

bactrace 사용 방법

```
RUST_BACKTRACE=1 cargo run
```

backtrace 값을 얻기 위해서는 디버그 모드로 실행되어야 하며, default로 지정되어 있다.

(release 모드로 빌드 시 --release 옵션을 추가)

---

Result 타입은 열거형으로 아래와 같이 구성

```rust
enum Result<T, E> {
	Ok(T),
	Err(E),
}
```

여기서 T, E는 제네릭 타입

아래와 같이 없는 파일을 open 하려고 한다고 가정

```rust
use std::fs::File;

fn main() {
    let file_result = File::open("hello.txt");

    let file = match file_result {
        Ok(file) => file,
        Err(error) => panic!("error : {:?}", error),
    };
}
```

File::open 의 return 값은 Result<File, Error> 타입으로, open이 성공한다면 file_result 변수는 hello.txt의 파일 핸들을 갖는 Ok 인스턴스가 되며, 실패한다면 Err 인스턴스가 된다.

Option 열겨형과 Result 열거형은 prelude 되어 있어 Result::Ok 와 같이 처리하지 않아도 된다.

실행 시 아래와 같이 에러 발생된다.

```
thread 'main' panicked at 'error : Os { code: 2, kind: NotFound, message: "No such file or directory" }', src/main.rs:8:23
note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace
```

error 종류에 따라 match 시키기

아래는 파일을 open 시도 후, 없다면 create 하는 기능이다. 에러 종류에 따라서 panic 또는 새로 생성된 파일의 핸들을 return 한다.

```rust
use std::fs::File;
use std::io::ErrorKind;

fn main() {
    let file_result = File::open("hello.txt"); // 파일 오픈 시도
    let file = match file_result { // 파일 open 결과에 따른 match 진행
        Ok(file) => file, // 성공 시 file 변수는 hello.txt 파일 핸들 결과인 Result<File, Error>의 File 값을 가짐
        Err(error) => match error.kind() { // 실패 시 Error 종류에 따른 match 진행
            ErrorKind::NotFound => match File::create("hello.txt") { // NotFound 에러 시 hello.txt 파일 생성 시도
                Ok(fc) => fc, // hello.txt 파일 생성 성공 시 file 은 create 결과인 Result<File, Error>의 File 값을 가짐
                Err(err) => panic!("create error : {:?}", err), // create 실패 시 panic 발생 
            },
            other_error => {
                panic!("open error : {:?}", other_error); // NotFound 에러 외에 다른 에러 발생 시 panic 발생 
            },
        },
    };
}
```

unwrap_or_else 메서드를 이용하면 위와 동일한 동작하는 코드 아래와 같이 작성 가능

```rust
use std::fs::File;
use std::io::ErrorKind;

fn main() {
    let file = File::open("hello.txt").unwrap_or_else(|error| {
        if error.kind() == ErrorKind::NotFound {
            File::create("hello.txt").unwrap_or_else(|error| {
                panic!("create error : {:?}", error);
            })
        } else {
            panic!("open error : {:?}", error);
        }
    });
}
```

unwrap, expect : panic에 대한 shortcut

unwrap 메서드는 Result 값이 Ok면 Ok에 맞는 값을 반환, Err면 알맞은 panic! 매크로 호출

```rust
use std::fs::File;

fn main() {
    let greeting_file = File::open("hello.txt").unwrap();
}
```

expect 이용하면 원하는 panic! 매크로 호출 가능

```rust
use std::fs::File;

fn main() {
    let greeting_file = File::open("hello.txt")
        .expect("hello.txt should be included in this project");
}
```

에러 전파 : 함수 내부에서 발생할 수 있는 에러의 경우, 함수 내부에서 에러 처리하는 대신 에러를 반환하도록 하는 것

```rust
use std::fs::File;
use std::io::{self, Read};

fn read_username_from_file() -> Result<String, io::Error> {
    let username_file_result = File::open("hello.txt"); // hello.txt 파일 open
    let mut username_file = match username_file_result {
        Ok(file) => file, // hello.txt open 성공 시 hello.txt File
        Err(err) => return Err(err), // 실패 시 에러 리턴 
    };

    let mut username = String::new();
    match username_file.read_to_string(&mut username) { // open 성공 시 username에 hello.txt에서 읽은 내용 append
        Ok(_) => Ok(username), // 성공 시 username을 Ok로 감싼 값을 리턴
        Err(err) => Err(err), // 실패 시 error 리턴
    } // 마지막 문장이기 때문에 return 명시 안 해도 됨
}
```

shortcut : ?

아래 함수는 위와 동일한 기능

```rust
use std::fs::File;
use std::io::{self, Read};

fn read_username_from_file() -> Result<String, io::Error> {
    let mut username_file = File::open("hello.txt")?;
    let mut username = String::new();
    username_file.read_to_string(&mut username)?;
    Ok(username)
}
```

?를 쓰는 것과 match로 Ok, Err 구분하는 것 차이는 ?를 쓰면 From 함수를 호출하면서 에러 발생 시 현재 함수의 리턴 값에 맞는 에러 타입으로 변환한다.

하지만 ?와 호환 가능한 타입이 리턴될 때만 사용 가능 

이를 이용하면 다양한 에러 처리에는 어려움이 있지만 많은 에러를 하나의 타입으로 처리 가능.

응용하면 아래와 같이 더 간결하게도 가능

```rust
use std::fs::File;
use std::io::{self, Read};

fn read_username_from_file() -> Result<String, io::Error> {
    let mut username = String::new();

    File::open("hello.txt")?.read_to_string(&mut username)?;

    Ok(username)
}
```

또한 fs::read_to_string 을 이용하면 더욱 간결

```rust
use std::fs;
use std::io;

fn read_username_from_file() -> Result<String, io::Error> {
    fs::read_to_string("hello.txt")
}
```

? 를 사용할 수 없는 예

```rust
use std::fs::File;

fn main() {
    let greeting_file = File::open("hello.txt")?;
}
```

File::open에 ?를 취함으로써 Result 타입이 리턴되지만, 위 main 함수의 경우 ()를 리턴하므로 호환되지 않는다.

main 함수를 아래와 같이 바꿈으로써 호환되게 만들 수 있다.

```rust
use std::error::Error;
use std::fs::File;

fn main() -> Result<(), Box<dyn Error>> {
    let greeting_file = File::open("hello.txt")?;

    Ok(())
}
```

---




