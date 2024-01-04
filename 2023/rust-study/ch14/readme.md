ch14

cargo, crates.io 더 알아보기 

릴리즈 프로필을 통한 빌드 커스터마이징

릴리즈 프로필 (release profile) : 커스터마이징 가능한 프로필

코드 컴파일을 위한 옵션 제어 가능

프로필 별로 독립적으로 설정됨

cargo는 2개의 주요 프로필이 존재

cargo build 실행 시 dev 프로필, cargo build --release 실행 시 release 프로필

dev 프로필은 개발에 적합한 기본값, release 프로필은 릴리즈 빌드용 설정값

Cargo.toml 파일의 "[profile.*]" 를 명시적으로 추가하지 않은 경우, 기본값으로 설정

```rust
// Cargo.toml
[profile.dev]
opt-level = 0

[profile.release]
opt-level = 3
```

opt-level 은 코드에 적용할 최적화 수치로 0에서 3의 값

높은 최적화 수치 적용할 수록 컴파일 시간 늘어나므로, 개발 중 자주 컴파일하는 상황에서는 최적화가 덜 되길 원함

그래서 dev의 opt-level의 기본값을 0

릴리즈 시, 컴파일은 1번만 하므로, 기본값이 3

각 최적화 수치에 대한 자세한 내용은 https://doc.rust-lang.org/cargo/reference/profiles.html 에 존재

---

Crates.io에 배포

crates.io는 패키지 소스코드를 공개하므로, 오픈 소스인 경우만 호스팅

문서화 주석 만들기

문서화 : 다른 사용자들이 패키지를 어떻게, 언제 사용할 지 알려주므로 시간을 투자해서 작성해야 함

문서화 주석 : /// 를 이용해 마크다운 형식으로 주석 작성
` ``` ` 이용 시, rust 형식의 코드로 에디팅 가능

```rust
// my_crate/src/lib.rs

/// crate test
/// add num and 1
/// 
/// # Examples
/// 
/// ```
/// let arg = 5;
/// let ans = my_crate::add_one(arg);
/// assert_eq!(6, ans);
/// ```

pub fn add_one(x: i32) -> i32 {
    x + 1
}
```

cargo doc 실행 시 문서화 주석 부분을 crate.io에 맞게 html 파일 제공

cargo doc --open 으로 확인 가능

`# Examples` 구문으로 Examples 임을 명시 가능

이외 유용한 구문

- Panics : 패닉을 일으킬 수 있는 시나리오. 이러한 상황에서는 해당 API 호출하면 안 됨을 명시

- Errors : 해당 API가 Result 타입 반환 시 발생 가능한 에러 종류 및 에러 발생 조건을 명시

- Safety : unsafe한 상황에서 API를 호출할 때 지켜야할 사항에 대해 설명

---

테스트로서의 문서화 주석

cargo test 실행 시 문서화 주석에 적힌 테스트 코드가 실행됨

주석이 포함된 아이템

`//!` 은 주석을 담고 있는 아이템을 문서화

예를 들어 `my_crate` 라는 crate의 목적을 설명하려면 아래와 같이 `//!` 로 시작하는 문서화 주석 추가

```rust
//! # my_crate
//! `my_crate` is a crate for crate.io test

/// crate test
/// add num and 1
/// 
/// # Examples
/// 
/// ```
/// let arg = 5;
/// let ans = my_crate::add_one(arg);
/// assert_eq!(6, ans);
/// ```

pub fn add_one(x: i32) -> i32 {
    x + 1
}
```

---

pub use 로 공개 API 내보내기

lib.rs가 계층 구조로 복잡하게 되어 있을 때 최종적으로 필요한 API만 사용자들이 사용할 수 있도록 하는 방법

예를 들어, art 라는 라이브러리의 lib.rs 가 아래와 같은 경우

```rust
//! # Art
//!
//! A library for modeling artistic concepts.

pub mod kinds {
    /// The primary colors according to the RYB color model.
    pub enum PrimaryColor {
        Red,
        Yellow,
        Blue,
    }

    /// The secondary colors according to the RYB color model.
    pub enum SecondaryColor {
        Orange,
        Green,
        Purple,
    }
}

pub mod utils {
    use crate::kinds::*;

    /// Combines two primary colors in equal amounts to create
    /// a secondary color.
    pub fn mix(c1: PrimaryColor, c2: PrimaryColor) -> SecondaryColor {
        // --생략--
    }
}
```

실제 사용 시 `use art::utils::mix` 와 같이 사용해야 함

이를 배포 시 art의 lib.rs에 pub use 키워드를 사용함으로써, art::mix 와 같이 사용 가능하도록 만들 수 있다.

```rust
//! # Art
//!
//! A library for modeling artistic concepts.

pub use self::kinds::PrimaryColor;
pub use self::kinds::SecondaryColor;
pub use self::utils::mix;

pub mod kinds {
    // --생략--
}

pub mod utils {
    // --생략--
}
```

---

cargo 작업공간

작업공간(workspace)은 동일한 Cargo.lock 과 출력 디렉토리를 공유하는 패키지 집합

작업 공간을 만드는 방법은 여러 가지 존재

예시로는 하나의 바이너리와 두 개의 라이브러리를 작업공간에 담을 것

주요 기능을 제공할 바이너리는 두 라이브러리를 의존성으로 갖게 될 것

첫 번째 라이브러리는 add_one 함수를 제공

두 번째 라이브러리른 add_two 함수를 제공

먼저 add 디렉토리 생성 후, Cargo.toml 파일 생성

```rust
[workspace]

members = [
    "adder",
]
```

add 디렉토리 내에서 cargo new adder 로 adder 바이너리 크레이트 생성, cargo build 진행

작업 공간은 컴파일된 결과가 위치할 하나의 target 디렉토리를 최상위에 가짐

adder 크레이트는 target 디렉토리를 갖기 않음

따라서 이후 컴파일 결과는 add/target에 위치

그 다음으로 add_one 이라는 크레이트 생성

최상위 Cargo.toml에 member로 add_one 추가

```rust
[workspace]

members = [
    "adder",
    "add_one",
]
```

cargo new add_one --lib 로 add_one 이라는 라이브러리 크레이트 생성

add_one 라이브러리에 add_one 함수 추가

```rust
pub fn add_one(x: i32) -> i32 {
    x+1
}
```

이후 adder 패키지에서 add_one을 사용하기 위해 adder/Cargo.toml에 add_one 의 경로 추가

```rust
// adder/Cargo.toml
// 생략

[dependencies]
add_one = {path="../add_one"}
```

cargo는 작업공간 내의 크레이트들이 서로 의존할 것이라고 가정하지 않으므로, 의존성에 대한 명시가 필수적

이제 의존성이 추가되었으므로 adder/main.rs에서 add_one 크레이트의 add_one 함수 호출

```rust
// adder/main.rs

use add_one;

fn main() {
    let num = 10;
    println!("{} + 1 = {}", num, add_one::add_one(num));
}
```

최상위 add 디렉토리에서 cargo build 진행 후 run 진행

특정 바이너리 크레이트 실행하려면 cargo run -p adder 와 같이 -p 옵션으로 바이너리 크레이트 파일 지정

---

외부 패키지 의존하기

작업공간에는 최상위에만 하나의 Cargo.lock 파일 생성

이는 모든 크레이트가 같은 버전을 사용함을 보증

동일한 패키지에 대해 하위 크레이트에 존재하는 외부 패키지 중 하나의 버전을 선택하여 Cargo.toml에 기록함

예를 들어 add_one 에 rand 패키지를 추가하기 위해 add_one/Cargo.toml 의 dependency에 rand="0.8.5" 추가 후 

add 디렉토리에서 cargo build 시 해당 패키지를 가져옴

하지만 adder 디렉토리에서는 아직 의존성이 없으므로 동일한 패키지를 adder/Cargo.toml 에 추가하면 됨

---

cargo install : Crates.io에 있는 바이너리를 설치함

예를 들어, 이이전에 ripgrep 과 같은 패키지 설치하려면

cargo install ripgrep 하면 됨


