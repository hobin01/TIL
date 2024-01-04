ch1

rust 기본 코드 작성 및 실행 파일 생성

코드 작성

- main.rs
```rust
fn main() {
	println!("Hello World!");
}
```

실행 파일 만들기 

- rustc main.rs

---

cargo : 패키지, 디펜던시 관리하는 것

toml 파일로 패키지 버전, 이름 등 지정 및 관리

src 디렉토리에 코드 작성 가능 

- 빌드시키기
cargo build

=> taget/debug 에 실행 파일 생성 및 빌드 기록 생성

- 실행시키기
cargo run

- 패키지 확인 (컴파일 체크)
cargo check
