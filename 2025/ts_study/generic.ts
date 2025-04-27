// generic 타입 지원 
function identity<T>(arg: T): T {
    return arg;
}

console.log(identity<string>("string!!!!"));
console.log(identity("string!!!!")); // 입력과 같은 제네릭 타입이면 굳이 <>에 타입 안 넣어도 됨

interface GenericIdentityFunc {
    <T>(arg: T): T;
}

// 인터페이스랑 동일한 제네릭 타입 함수 지정 가능 
let myIdentity: GenericIdentityFunc = identity;

// 여러 제네릭 지정 가능 
function multiGeneric<T, U>(key: T, val: U): Map<T, U> {
    let res = new Map<T, U>();
    res.set(key, val);
    return res;
}

let m = multiGeneric<string, number>("123", 123);
console.log(m);

// generic에서 extends 같은 걸로 바로 상속 가능 
function extString<T extends string>(v: T) {
    console.log(v + "123");
}

extString("qwe");