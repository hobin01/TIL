ch12

커맨드 라인 프로그램 만들기

grep 구현 (프로젝트 이름 : minigrep)

1. 2개의 커맨드라인 파라미터 받기

구현 결과 : cargo run -- searchstring example-filename.txt 실행 가능하도록 하기

-- : 파라미터 입력 
searchstring : 구현된 검색 명령어 
example-filename.txt : 찾고자 하는 파일

```rust
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    dbg!(args);
}
```

env::args() 메서드의 경우 유효하지 않은 유니코드 입력 시 panic 발생

필요한 경우, std::env::args_os 메서드 사용해야 함

env::args().collect() 메서드로 입력된 값들을 Vec<String> 으로 변환

dbg! 매크로를 이용해 벡터 내용 출력

파라미터 포함한 입력 : cargo run -- param1 param2 와 같이 입력

인자값 변수 저장 : Vec<String>에 저장된 값 나눠서 저장시키면 됨

```rust
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    dbg!(&args);

    let opt = &args[0];
    let query = &args[1];
    let file_name = &args[2];

    println!("param1 : {}", opt);
    println!("parma2 : {}", query);
    println!("param3 : {}", file_name);
}
```

cargo run -- needle stack 실행 결과

```
[src/main.rs:5] &args = [
    "target/debug/minigrep",
    "needle",
    "stack",
]
param1 : target/debug/minigrep
parma2 : needle
param3 : stack
```

args에 저장된 첫 번째 파라미터 값은 바이너리 파일 (target/debug/minigrep)

프로그램 실행 중 호출된 이름을 프로그램이 사용할 수 있게 한다.

이후 파라미터는 동일하게 잘 저장됨

---

파일 읽기 

현재 읽으려는 poem.txt 파일은 cargo를 실행시킬 ch12/minigrep/poem.txt 에 존재

```rust
use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let file_path = &args[2];

    println!("file path : {}", file_path);

    let contents = 
        fs::read_to_string(file_path)
            .expect("read file fail");
    
    println!("contents : \n{}", contents);
}
```

fs::read_to_string() 메서드는 file path에 맞는 파일 읽어서 Result<String> 반환

expect 로 Result 리턴이 Err 일 때 발생시킬 에러메시지 작성

---

프로그램을 향상시키기 위해서는 기능을 분리하여 각 함수가 하나의 작업만을 수행하는 것이 최선

스코프 내에 더 많은 변수 있을 수록 변수의 목적 계속 추적하는 것 어려움

모든 에러에 대해서 동일한 메시지가 아닌 각 에러 별 정보 제공해야 함

index out of bounds 같은 에러는 파라미터에 따라 에러 발생시키므로 에러 설명에 어려움 존재

모든 에러 처리 코드가 한 곳에 있어서 코드 유지보수할 때 에러 처리 로직 변경하기 원할

리팩토링으로 위 문제 해결해야 한다.

- 프로그램을 main.rs, lib.rs 로 분리
- 커맨드 라인 파싱 로직이 작으면 main.rs에 그대로 있어도 됨
- 복잡하면 lib.rs에 파싱 로직 구현하는 것이 좋음

이후 main.rs 는 인자값으로 파싱 로직 호출, 환경 설정, lib.rs run 호출, 에러 처리 등의 기능만을 수행

주요 파싱 로직은 lib.rs로 처리

또한 테스트의 경우, main 함수를 직접 테스트할 수는 없으므로 테스트 로직을 lib.rs에서 실행시키는 것이 좋음

우선 main.rs 내에서 필요한 로직 분리

1. 파서 분리

```rust
use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let (query, file_path) = parse_config(&args);

    let contents = 
        fs::read_to_string(file_path)
            .expect("read file fail");
    
    println!("contents : \n{}", contents);
}

fn parse_config(args: &[String]) -> (&str, &str) {
    let query = &args[1];
    let file_path = &args[2];

    (query, file_path)
}
```

파라미터를 모은 벡터를 parse_config 함수에 통으로 넘김으로써 main 함수는 파라미터가 어떻게 처리될 지 책임지지 않음

하지만 parse_config 함수 리턴 값인 튜플을 그대로 사용하지 않고 또 분리시켜 사용하므로 비효율적

```rust
use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let config = parse_config(&args);

    let contents = 
        fs::read_to_string(config.file_path)
            .expect("read file fail");
    
    println!("contents : \n{}", contents);
}

struct Config {
    query: String,
    file_path: String,
}

fn parse_config(args: &[String]) -> Config {
    let query = args[1].clone();
    let file_path = args[2].clone();

    Config {query, file_path}
}
```

튜플로 생성했던 값을 struct로 처리하도록 수정

main 함수의 args 변수는 parse_config 함수에게 변수값을 빌려주려고 했지만, Config 구조체가 해당 값의 소유권을 가지면 borrow 에러 발생

임시로 clone 메서드로 복사 처리함 (13장에서 해당 부분 효율적으로 처리하는 방법 소개)

```rust
use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let config = Config::new(&args);

    let contents = 
        fs::read_to_string(config.file_path)
            .expect("read file fail");
    
    println!("contents : \n{}", contents);
}

struct Config {
    query: String,
    file_path: String,
}

impl Config {
    fn new(args: &[String]) -> Config {
        let query = args[1].clone();
        let file_path = args[2].clone();

        Config {
            query,
            file_path,
        }
    }
}
```

parse_config 함수 목적이 Config 구조체 생성하는 것이므로 new 함수를 impl 하여 원하는 Config 구조체 값 바로 얻도록 수정

```rust
use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let config = Config::new(&args);

    let contents = 
        fs::read_to_string(config.file_path)
            .expect("read file fail");
    
    println!("contents : \n{}", contents);
}

struct Config {
    query: String,
    file_path: String,
}

impl Config {
    fn new(args: &[String]) -> Config {

        if args.len() < 3 {
            panic!("not enough args");
        }

        let query = args[1].clone();
        let file_path = args[2].clone();

        Config {
            query,
            file_path,
        }
    }
}
```

단순히 cargo run 실행하면 자세한 에러는 안 나오며, index out of bounds 라고만 나옴

자세한 에러 처리를 위해 args 인자 3개 (default 1개 포함) 미만이면 panic을 일으켜 자세한 에러처리

```rust
use std::{env, fs, process};

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let config = Config::build(&args).unwrap_or_else(|err| {
        println!("Problem parsing args: {err}");
        process::exit(1);
    });

    let contents = 
        fs::read_to_string(config.file_path)
            .expect("read file fail");
    
    println!("contents : \n{}", contents);
}

struct Config {
    query: String,
    file_path: String,
}

impl Config {
    fn build(args: &[String]) -> Result<Config, &'static str> {

        if args.len() < 3 {
            return Err("not enough args");
        }

        let query = args[1].clone();
        let file_path = args[2].clone();

        Ok(Config { query, file_path, })
    }
}
```

Config 구조체 생성에 성공, 실패 여부에 따라 에러 처리하도록 Result 로 리턴값 수정

또한 일반적으로 new 라는 이름은 실패 여부가 잘 없게 느껴지므로 build 로 이름 수정

그리고 에러처리 시 panic! 이 아닌 에러로 처리하도록 정의하기 위해 unwrap_or_else 메서드 이용해서 에러 메시지 출력

(Result의 Err을 그대로 출력하면 너무 많은 정보 나오기 때문)

그리고 마지막으로 프로그램 종료를 위해 exit(1) 추가

```rust
// lib.rs

use std::error::Error;
use std::fs;

pub struct Config {
    pub query: String,
    pub file_path: String,
}

impl Config {
    pub fn build(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough args");
        }

        let query = args[1].clone();
        let file_path = args[2].clone();

        Ok(Config { query, file_path, })
    }
}

pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.file_path)?;
    println!("{contents}");
    Ok(())
}
```

기존 main.rs에 구현되었던 Config 관련한 정보를 lib.rs 로 옮김

그리고 run 함수를 새로 만들면서 file_path가 존재할 때는 해당 경로 파일 읽고 출력, 별도 리턴 없음

에러 시 어떤 에러가 발생할 지 모르니 타입 특정짓지 않도록 Box<dyn Error> 리턴

```rust
// main.rs

use std::{env, process};
use minigrep::{Config, run};

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let config = Config::build(&args).unwrap_or_else(|err| {
        println!("arguments error : {err}");
        process::exit(1);
    });

    if let Err(e) = run(config) {
        println!("application error : {e}");
        process::exit(1);
    }
}

```

main.rs 파일에서는 args로 넘어온 값에 대해 파라미터가 모자라면 config 구조체 생성 시, 에러처리 진행

args는 올바를 때 run 함수 호출하면서 성공 시, 해당 파일 읽고 내용 출력,

실패 시 해당 에러를 출력 하도록 리팩토링 완료

---

TDD로 라이브러리 기능 개발

1. 실패하는 테스트 작성, 예상한 이유로 실패하는 지 확인
2. 새로운 테스트 통과하기 충분한 코드 작성 및 수정
3. 작성한 코드 리펙토링
4. 반복

```rust
// lib.rs

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn one_result() {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.";

        assert_eq!(vec!["safe, fast, productive."], search(query, contents));
    }
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    vec![]
}
```

의도적으로 실패하는 테스트 

빈 벡터를 반환하는 search 함수 호출함으로써 테스트하고자 하는 함수 부분 작성

'a 로 라이프타임 지정하여 contents 파라미터의 라이프타임과 search 함수의 리턴값의 라이프타임 동일하도록 작성

```rust
// lib.rs

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn one_result() {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.";

        assert_eq!(vec!["safe, fast, productive."], search(query, contents));
    }
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut results = Vec::new();
    
    for line in contents.lines() {
        if line.contains(query) {
            results.push(line);
        }
    }

    results
}
```

테스트 통과

contents 문자열을 줄 별로 보면서 query 내용이 포함된 줄은 vector에 push

cargo test 로 테스트 시 테스트 통과 

search 함수가 원하는 결과 생성하는 걸 테스트했으므로 run 함수에 search 함수 적용하면 됨

```rust
// lib.rs

pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.file_path)?;
    
    for line in search(&config.query, &contents) {
        println!("{line}");
    }

    Ok(())
}
```

run 실행 시 search 함수가 실행되므로 기존 poem.txt 파일에 원하는 단어있는 줄 검색 가능

cargo run -- frog poem.txt

---

환경변수 사용

환경변수 이용해서 대소문자 구분 없는 검색 기능

```rust
// lib.rs
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case_insensitive() {

        let query = "RusT";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.
Trust me.";

        assert_eq!(
            vec!["Rust:", "Trust me."], 
            search_case_insensitive(query, contents)
        );
    }
}

pub fn search_case_insensitive<'a> (
    query: &str,
    contents: &'a str
) -> Vec<&'a str> {
    let query = query.to_lowercase();
    let mut results = Vec::new();

    for line in contents.lines() {
        if line.to_lowercase().contains(&query) {
            results.push(line);
        }
    }

    results
}
```

str의 to_lowercase() 메서드 이용해서 소문자 값으로 변환

주어진 contents에 rust 라는 단어 포함되있는 줄이 Rust: , Trust me. 이므로 해당 테스트는 통과

```rust
// lib.rs

use std::error::Error;
use std::fs;
use std::env;

pub struct Config {
    pub query: String,
    pub file_path: String,
    pub ignore_case: bool,
}

impl Config {
    pub fn build(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough args");
        }

        let query = args[1].clone();
        let file_path = args[2].clone();
        let ignore_case = env::var("IGNORE_CASE").is_ok();

        Ok(Config { query, file_path, ignore_case})
    }
}

pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.file_path)?;

    let results = if config.ignore_case {
        search_case_insensitive(&config.query, &contents)
    } else {
        search(&config.query, &contents)
    };
    
    for line in results {
        println!("{line}");
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case_sensitive() {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.";

        assert_eq!(vec!["safe, fast, productive."], search(query, contents));
    }

    #[test]
    fn case_insensitive() {

        let query = "RusT";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.
Trust me.";

        assert_eq!(
            vec!["Rust:", "Trust me."], 
            search_case_insensitive(query, contents)
        );
    }
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut results = Vec::new();
    
    for line in contents.lines() {
        if line.contains(query) {
            results.push(line);
        }
    }

    results
}

pub fn search_case_insensitive<'a> (
    query: &str,
    contents: &'a str
) -> Vec<&'a str> {
    let query = query.to_lowercase();
    let mut results = Vec::new();

    for line in contents.lines() {
        if line.to_lowercase().contains(&query) {
            results.push(line);
        }
    }

    results
}
```

환경 변수 IGNORE_CASE 가 true 일 때, search_case_insensitive 함수 호출

아래와 같이 환경 변수 설정 후 실행

export IGNORE_CASE=1

cargo run -- to poem.txt

---

표준 에러로 에러 메시지 작성

표준 출력이 특정 파일에 리디렉션 되도록 하기

cargo run > output.txt

현재 아무 파라미터도 설정하지 않았으므로, 에러 메시지가 표준 스트림으로 output.txt에 저장됨 

표준 에러스트림 : eprintln!()

```rust
// main.rs
use std::{env, process};
use minigrep::{Config, run};

fn main() {
    let args: Vec<String> = env::args().collect();
    
    let config = Config::build(&args).unwrap_or_else(|err| {
        eprintln!("arguments error : {err}");
        process::exit(1);
    });

    if let Err(e) = run(config) {
        eprintln!("application error : {e}");
        process::exit(1);
    }
}
```

에러 처리를 표준 에러 스트림으로 출력하도록 하여, 아래와 같은 커맨드 입력 시 에러 발생하면 output.txt에는 아무런 내용도 입력되지 않는다.

cargo run > output.txt

다만 콘솔에만 에러 메시지 출력

아래와 같이 성공적인 커맨드 입력 시 output.txt에는 정상 입력

cargo run -- to poem.txt > output.txt




