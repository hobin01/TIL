ch3

rust는 let으로 그냥 할당 시 immutable 변수로 지정 

그냥 let과 const 차이 : let으로 선언하여 immutable 변수로 사용 시 타입 지정 자동으로 해줌. 하지만 const로 선언 시 타입 지정 반드시 해야함. 
그리고 let으로 선언 시 변수 이름에 대한 shadowed 가능 (덮어쓰기 가능)

```rust
let x = 5;
let x = x + 1;
{
	let x = x * 2; // x = 12 (scope 다르기 때문)
}
println!("{x}"); // x = 6
```

let과 let mut 차이 : let mut 선언 시 mutable 변수로 사용. 하지만 다른 타입에 동일한 이름의 변수로서는 사용 불가

```rust
let spaces = "   ";
let spaces = spaces.len(); // ok

let mut spaces = "   ";
spaces = spaces.len(); // err
```

tuple : ()로 묶어서 처리

```rust
let tup: (i32, f32, bool) = (100, 1.00, true);
let (x, y, z) = tup;
let w = tup.0; // w = 100
let v = tup.1; // v = 1.00
let u = tup.2; // u = true
```

배열 : []로 처리

[3;5] = [3,3,3,3,3] 을 의미 (3으로 초기화된 크기 5 배열)

[i32;5] 와 같이 타입 지정 가능

```rust
let arr1 = [1,2,3];
let arr2: [i32; 5] = [1,2,3,4,5];
let arr3 = [3;5];
let arr4: [i32; 5] = [3;5];
```

---

함수 이름도 변수 이름과 마찬가지로 _로 구분시킴 (ex. function_a ())

함수 파라미터 설정 시 변수 타입 지정 필수 (ex. function_a(x: i32) )

변수에 {}로 함수로 표현하면 마지막 줄이 변수에 대입됨

```rust
let y = {
	let x = 3;
	x + 1 // 마지막 줄에는 ; 안 쓰므로써 해당 줄이 y에 대입됨을 의미 
};
```

함수 리턴 타입 : -> 로 지정

```rust
fn five(x: i32) -> i32 {
	x * 5 // 이 때도 리턴될 값에는 ; 안 붙힘 (return 키워드 붙히면 ; 붙혀도 됨)
}
```

---

제어문 (if, for, while)

if 문에 별도 괄호 없이 처리, if 문은 {}로 생성

```rust
if num < 5 {
	.....
} else if num == 5 {
	.....
} else {
	.....
}
```

변수에도 if 문으로 대입 가능 (단 분기 결과의 타입은 일치해야함)

```rust
let condition: bool = true;
let x = if condition {5} else {6};
```

loop : 그냥 loop는 무한루프 의미, break로 탈출 가능하며, 이 때 let 선언한 변수에 대입 가능

```rust
let mut cnt = 0;
let result = loop {
	cnt += 1;
	if cnt == 10 {
		break cnt * 2;
	}
};
```

while : 일반적인 while 문과 동일

```rust
let mut cnt = 10;
while cnt > 0 {
	println!("{cnt}");
	cnt -= 1;
}
```

for : 배열 원소에 대해 loop 돌면 element in arr 형태로, range 지정하려면 element in 1..5 와 같이 (역순은 .rev())

```rust
let arr = [10, 20, 30];
for ele in arr {
    println!("{ele}");
}

for num in 1..5 {
    println!("{num}");
}

for num in (1..5).rev() {
    println!("{num}");
}
```



