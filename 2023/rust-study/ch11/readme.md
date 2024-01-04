ch11

자동화 테스트

테스트 함수는 보통 다음 동작 수행

1. 필요한 데이터나 상태 설정
2. 테스트할 코드 실행
3. 의도한 결과 나오는 지 확인

rust에서 테스트 : test 속성이 annotation된 함수

derive와 마찬가지로 fn 앞에 #[test] 추가하면 테스트 함수로 변경

테스트는 cargo test 로 실행

테스트 실행 시, 함수 실행 결과를 보고하는 테스트 바이너리 빌드함

--lib 옵션으로 라이브러리 생성 시, 테스트 템플릿 제공한다.

```rust
pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}

```

위 코드에서 #[test] annotation으로 it_works 함수가 테스트 함수임을 표시

위 코드에서는 assert_eq! 매크로를 이용해 result에 대해 assert 체크

테스트 시 cargo test 에 옵션 추가해 일부 테스트 함수만 실행 가능

벤치마크 결과는 nightly 버전에서 사용 가능 (현재 버전 기준)

또한 API 문서에 작성한 내용 테스트도 가능 (14장에서 설명)

```rust
pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    #[test]
    fn another() {
        panic!("test fail!!!");
    }
}
```

위 코드와 같이 panic! 매크로 이용해서 의도적으로 fail 유도 가능

---

어떤 조건이 true 임을 보장하는 지 확인하는 테스트는 assert! 매크로가 유용

assert! 매크로는 boolean 값 파라미터를 받는다.

true인 경우, 테스트 통과, false인 경우, panic! 매크로 호출

```rust
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn larger_can_hold_smaller() {
        let larger = Rectangle {
            width: 5,
            height: 10,
        };
        let smaller = Rectangle {
            width: 3,
            height: 1,
        };

        assert!(larger.can_hold(&smaller));
        assert!(smaller.can_hold(&larger));
    }
}
```

tests 모듈도 하나의 모듈이므로 tests 모듈 바깥에 정의된 Rectangle 구조체를 사용하려면 

use super::*; use crate::Rectangle; 과 같이 use 키워드로 사용할 인스턴스나 모듈을 스코프 내로 가져와야 한다.

assert! 매크로를 호출함으로써 can_hold 함수 결과가 true 면 테스트 성공, false 면 panic! 매크로 호출

위 코드 실행 시 smaller.can_hold(&larger) 부분에서 assertion failed 발생했다고 나옴.

---

assert_eq!, assert_ne! 매크로

```rust
pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
        assert_ne!(result, 5);
    }
}
```

assert! 매크로에 == 연산으로 동일한지 여부 확인 가능

이와 동일한 기능이 assert_eq!

단 주의해야 할 점은 assert_eq!, assert_ne! 매크로로 비교하기 위해서는 PartialEq, Debug 트레잇이 구현된 타입만이 비교 가능

예를 들어 구조체를 적용하기 위해서는 #[derive(PartialEq, Debug)] annotation 적용해야 함. 

```rust
#[cfg(test)]
mod tests {

    #[derive(PartialEq, Debug)]
    struct A{
        num: u32,
    }

    #[test]
    fn struct_works() {
        let a1 = A{
            num: 1,
        };

        let a2 = A{
            num: 1,
        };

        assert_eq!(a1, a2);
    }
}
```

---

매크로에 커스텀 메시지 추가

```rust
pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 5, "not equal to 4!!!");
    }

    #[test]
    fn equal_check() {
        let result = 1;
        let result_check = 2;
        assert!(
            result == result_check,
            "result : {}, result_check : {}",
            result, result_check
        );
    }
}
```

위 코드와 같이 assert! 관련 매크로 실행 결과 실패 시 panic! 매크로가 호출되면서 나올 메시지를 정할 수 있다.

메시지는 기존의 string 처럼 처리하면 된다.

---

테스트 실행 제어

cargo test --help : cargo test 에 사용가능한 옵션 도움말

cargo test -- --help :cargo test -- 에 사용가능한 옵션 도움말

rust에서 테스트 시 기본적으로 병렬 테스트 수행

테스트 병렬 실행 시, 각 테스트가 자원 공유, 환경 변수 등에 대해서 공유 상태를 갖거나 의존 관계를 가지면 안 됨

테스트를 병렬 실행하지 않거나 사용할 스레드 개수 조절하려면 아래와 같이 --test-threads 옵션으로 사용할 스레드 개수 조절

```
cargo test -- --test-threads=1
```

스레드를 1개만 사용함으로써 병렬 처리 안 하도록 조절

---

함수 출력 표시

rust의 테스트 라이브러리는 성공한 테스트는 println! 매크로를 호출해도 출력이 나오지 않음

```rust
pub fn prints_and_returns_10(a: i32) -> i32 {
    println!("get value : {}", a);
    10
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn this_test_will_pass() {
        let value = prints_and_returns_10(4);
        assert_eq!(10, value);
    }

    #[test]
    fn this_test_will_fail() {
        let value = prints_and_returns_10(8);
        assert_eq!(5, value);
    }
}
```

위 코드를 cargo test 로 실행 시 this_test_will_pass 함수와 관련된 내용은 성공했다는 메시지만 나옴

실패한 테스트인 this_test_will_fail 함수는 println! 매크로와 관련된 내용 출력

성공한 테스트에 대해서도 출력하려면 --show-output 옵션 추가

```
cargo test -- --show-output
```

---

이름 지정하여 일부만 테스트

```rust
pub fn prints_and_returns_10(a: i32) -> i32 {
    println!("get value : {}", a);
    10
}

pub fn add_two(a: i32) -> i32 {
    a + 2
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn this_test_will_pass() {
        let value = prints_and_returns_10(4);
        assert_eq!(10, value);
    }

    #[test]
    fn this_test_will_fail() {
        let value = prints_and_returns_10(8);
        assert_eq!(5, value);
    }

    #[test]
    fn add_three_and_two() {
        assert_eq!(5, add_two(3));
    }

    #[test]
    fn add_one_hundred_and_two() {
        assert_eq!(102, add_two(100));
    }
}
```

단순히 cargo test 로 테스트 실행 시, 모든 테스트가 병렬적으로 진행

특정 함수나 모듈만을 테스트하려면 해당 함수나 모듈 이름의 일부를 옵션으로 주면 된다. 

예를 들어 위에서 add 이름이 들어간 함수를 테스트하려면 아래와 같이 실행. 모듈 테스트 시에도 해당 이름 들어간 모듈 체크 가능 

```
cargo test add
```

따로 지정하지 않으면 무시시킬 테스트는 #[ignore] annotation을 시키면 된다.

```rust
#[test]
#[ignore]
fn ignore_test() {
    panic!("this will be ignored");
}
```

--ignored 옵션으로 ignore 이 annotation 된 테스트만 진행 가능

```
cargo test -- --ignored
```

---

유닛 테스트, 통합 테스트

유닛 테스트 : 모듈 단위로 테스트

통합 테스트 : 테스트 라이브러리 외부에서 불러와서 테스트

유닛 테스트는 src 디렉토리 내의 각 파일에 테스트 대상이 될 코드와 함께 작성

각 파일에 tests 모듈을 만들고 cfg(test) 를 annotation 하는 것이 일반적 

rust에서 #[cfg(test)] annotation 은 cargo test 로만 실행하라는 의미 

라이브러리 빌드 시 테스트 파일은 빌드되지 않음

```rust
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
```

비공개 함수 테스트

rust는 비공개 함수 테스트를 지원함. pub 키워드가 붙어있지 않아도 테스트를 허용

```rust
fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
```

위와 같이 tests 모듈 바깥에 존재하는 add 함수에 pub 키워드를 붙히지 않아도 it_works 테스트 함수는 정상 테스트 가능

통합테스트는 작성된 라이브러리와 분리하여 외부 코드와 마찬가지로 테스트를 진행

따라서 라이브러리의 공개 API만 호출 가능

통합 테스트 시, tests 디렉토리를 통해 테스트 진행

아래와 같은 디렉토리 구조 가진다고 가정하자.

```
test_config
├── Cargo.lock
├── Cargo.toml
├── src
│   └── lib.rs
└── tests
    └── integration_test.rs
```

cargo test 실행 시 tests 디렉토리 내부의 통합 테스트 코드도 실행시킴

```rust
use test_config;

#[test]
fn it_add_two() {
    assert_eq!(4, test_config::add_pub(2, 2));
    // assert_eq!(4, test_config::add(2, 2)); // error by private fn
}
```

따라서 통합 테스트의 경우, #[cfg(test] annotation 필요 없음

또한 유닛 테스트와 달리 private 처리된 함수에 대해서는 테스트 불가

cargo test 실행 시 유닛 테스트와 통합 테스트 모두 실행

통합 테스트 파일만 실행시키려면 

cargo test --test integration_test 와 같이 옵션 부여


