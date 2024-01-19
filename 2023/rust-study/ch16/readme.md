ch16 겁없는 동시성

동시성 프로그래밍 : 프로그램의 서로 다른 부분이 독립적으로 실행되는 것

병렬 프로그래밍 : 프로그램의 서로 다른 부분이 동시에 실행되는 것

현재 설명에서는 동시성과 병렬성을 모두 동시성으로 칭하도록 함
(실제로는 다름, 하지만 동시성이냐 병렬성이냐의 문제가 아닌, 동시에 어떤 업무를 수행할 때 발생하는 문제를 컴파일 과정에서 캐치하는 것이 목적)

---

스레드를 이용해 코드를 동시에 실행하기

최신 운영체제에서 프로그램의 코드는 프로세스 내에서 실행, 운영체제는 여러 프로세스를 한 번에 관리

동일 프로그램 내에서 실행되는 독립적인 부분 : 스레드

프로세스 : 운영체제로부터 자원 할당받아 작업 수행

스레드 : 프로세스로부터 자원 할당받아 작업 수행

스레드로 동시에 어떤 작업을 수행함으로써 성능을 높히더라도, 스레드가 동시에 실행되거나, 실행 순서를 예측하기 어려운 문제가 발생함

멀티 스레드 환경에서 발생 가능한 문제들

- 여러 스레드가 일관성 없는 순서로 데이터 혹은 리소스에 접근하게 되는 race condition
- 두 스레드가 서로를 기다려서 양쪽 스레드 모두 실행되는 것을 막아버리는 deadlock
- 특정 상황에서만 발생해 안정적으로 재현하고 수정하기 힘든 버그들

---

신규 스레드 생성 : `thread::spawn` 호출해 스레드 실행

main 스레드와 신규 스레드 간 실행 예시

```rust
use std::thread;
use std::time::Duration;

fn main() {
    thread::spawn(|| {
        for i in 1..10 {
            println!("{} from the spawned thread!", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..5 {
        println!("{} from the main thread!", i);
        thread::sleep(Duration::from_millis(1));
    }
}
```

실행 결과 (실행할 때마다 다를 수 있음)

```
1 from the main thread!
1 from the spawned thread!
2 from the main thread!
2 from the spawned thread!
3 from the main thread!
3 from the spawned thread!
4 from the main thread!
4 from the spawned thread!
5 from the spawned thread!
```

main 스레드가 끝남과 동시에 spawn으로 만든 신규 스레드는 강제 종료되어 버림

따라서 위와 같은 경우, 스레드 간의 실행 순서 보장도 못하고, 올바르게 전부 실행됨도 보장 못함

```rust
use std::thread;
use std::time::Duration;

fn main() {
    let handle = thread::spawn(|| {
        for i in 1..10 {
            println!("{} from the spawned thread!", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..5 {
        println!("{} from the main thread!", i);
        thread::sleep(Duration::from_millis(1));
    }

    handle.join().unwrap();
}
```

위와 같이 spawn으로 생성한 스레드의 리턴 handle에 대해 join 메서드 호출 시, 해당 스레드 종료 때까지 대기하도록 함

즉, 해당 스레드가 종료될 때까지 현재 실행 중인 스레드를 블록함(block).

---

thread::spawn 으로 생성된 스레드에 어떤 인자를 사용하고 싶으면 클로저로 캡처를 해야함

```rust
use std::thread;

fn main() {
    let v = vec![1,2,3];

    let handle = thread::spawn(|| {
        println!("vector : {:?}", v);
    });

    handle.join().unwrap();
}
```

위와 같은 경우, 클로저로 v를 캡처하려고 하지만 스레드 종료 시점이 언제인지 모르므로 v에 대한 참조자의 유효성에 대한 에러가 발생

따라서 이와 같이 외부 변수를 클로저로 캡처할 경우, move로 소유권을 강제로 빌려와야 함

```rust
use std::thread;

fn main() {
    let v = vec![1,2,3];

    let handle = thread::spawn(move || {
        println!("vector : {:?}", v);
    });

    handle.join().unwrap();
}
```

move로 소유권을 얻어오게 되면 메인 스레드에서 drop 호출 등으로 스레드 종료 전에 소유권을 이용해 작업을 수행하는 것이 불가능해짐

---

메시지 패싱(message passing) : 스레드 또는 액터들이 서로 데이터를 담은 메시지를 보내 통신하는 것

메시지 패싱을 위한 러스트 표준 라이브러리 : channel

채널 : 송신자와 수신자로 구분

보내고자하는 데이터와 함께 송신자의 메서드를 호출, 다른 곳에서는 도달한 메시지에 대한 수신 종료를 검사

송신자 또는 수신자가 버려지면 채널이 닫힘(closed)

채널 생성 : mpsc::channel 함수를 이용

mpsc : multiple producer, single consumer

송신은 여러 개, 수신은 1개만 하도록 구성함

즉, 최종 도착지는 1개

```rust
use std::sync::mpsc;
use std::thread;

fn main() {
    let (tx, rx) = mpsc::channel();
    // tx : transmitter, rx : receiver

    thread::spawn(move || {
        let val = String::from("hi");
        tx.send(val).unwrap();
    });
}
```

move를 이용해 tx에 대한 소유권을 spawn 스레드가 갖도록 소유권을 이동시킴

tx의 send 메서드를 호출하여 val을 송신시킴

수신은 rx의 recv(), try_recv() 메서드 이용

```rust
use std::sync::mpsc;
use std::thread;

fn main() {
    let (tx, rx) = mpsc::channel();
    // tx : transmitter, rx : receiver

    thread::spawn(move || {
        let val = String::from("hi");
        tx.send(val).unwrap();
    });

    let received = rx.recv().unwrap();
    println!("received : {}", received);
}
```

recv() : 메시지 받을 때까지 현재 라인에 있는 스레드를 블록 처리함.

즉, 메시지 받을 때까지 대기함

try_recv() : 블록을 진행하지 않지만, 호출되는 시점에 메시지 있으면 Ok, 없으면 Err 반환함. 

즉, 계속 대기하지 않으므로, 무한루프 돌려놓고 다른 작업 수행 가능 

```rust
use std::sync::mpsc;
use std::thread;
use std::time::Duration;

fn main() {
    let (tx, rx) = mpsc::channel();
    // tx : transmitter, rx : receiver

    thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];

        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    for received in rx {
        println!("got : {}", received);
    }
}
```

위 예제 : 스레드가 여러 메시지를 보내면서 rx에서 별다른 처리 (recv() 등) 없이도 수신하는 예제

즉, main 스레드에서 동작하는 rx는 for loop에 별다른 sleep 기능 없지만, 알아서 수신 대기 중인 상태 유지 중

```rust
use std::sync::mpsc;
use std::thread;
use std::time::Duration;

fn main() {
    let (tx, rx) = mpsc::channel();
    // tx : transmitter, rx : receiver

    let tx1 = tx.clone();
    thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];

        for val in vals {
            tx1.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    thread::spawn(move || {
        let vals = vec![
            String::from("more"),
            String::from("message"),
            String::from("for"),
            String::from("you"),
        ];

        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    for received in rx {
        println!("got : {}", received);
    }
}
```

위 예제는 mpsc가 다중 생산자, 단일 소비자 인 것에 대한 예제

tx1과 tx를 이용해서 여러 스레드로 하나의 수신자 rx에 대해 메시지를 전송시키는 것 가능 

---

공유 상태 동시성