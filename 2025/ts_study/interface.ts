import output from "./output";

interface Person {
    age: number;
    name: string;
};

let p: Person = {age: 123, name: "asdasd"};

output(p.name);
output(p);

// ? : 선택적 프로퍼티 (? 지정 안 하면 컴파일할 때 있는 지 없는 지 검사)
interface PersonConfig {
    age?: number;
    name?: string;
    something?: any;
}

function make_person(conf: PersonConfig): Person {
    let p : Person = {age: 0, name: ""};
    if(conf.age) {
        p.age = conf.age;
    }
    if(conf.name) {
        p.name = conf.name;
    }
    return p;
}

let pc: PersonConfig = {age: 123};
let p2 = make_person(pc);

output(p2);

interface ReadOnly {
    readonly x: number;
    readonly y: number;
    readonly arr: ReadonlyArray<number>;
};

let r : ReadOnly = {x: 123, y: 234, arr: [1,2,3]};
output(r);

// readonly 선언 시 할당 외에 수정 불가
// 변수에는 const, 프로퍼티에는 readonly
// r.x = 234;
// r.arr[1] = 1;

interface ExtendConfig {
    age?: number;
    name?: string;
    [propName: string]: any; // 초과 프로퍼티 : 기본 프로퍼티 외에 추가적인 요소 아무거나 들어갈 수 있음
}

let ext: ExtendConfig = {name: "123", something: "something"};
console.log(ext);

// 초과 프로퍼티 없어도 됨
let ext2: ExtendConfig = {age: 123};
console.log(ext2);

interface searchFunc {
    // interface 안에서 함수 선언 
    // () - params, : <> - return type 
    (src: string, sub: string): boolean;
}

let search : searchFunc;
search = (src: string, sub: string) : boolean => {
    let res = src.search(sub);
    return res > -1;
}

console.log(search("123", "23"));

interface ClockInterface {
    cur: Date;
    setTime(d: Date): void;
}

class Clock implements ClockInterface {
    cur: Date = new Date();
    setTime(d: Date) {
        this.cur = d;
    } 

    constructor(num: number) {}

    // interface에 있는 것들은 무조건 public으로 사용할 수 밖에 없음

}

let clock = new Clock(123);
clock.setTime(new Date());
output(clock.cur);

class Control {
    public x: number = 123;
    public printX() {
        console.log(this.x);
    }
}

interface SelectableControl extends Control {
    select(): void;
}

class SelectControl implements SelectableControl {
    select() {}
    
    // interface가 class 상속 시, 상위 class의 프로퍼티도 interface에 지정됨
    // 그러므로 해당 interface implements 할려는 class는 제일 상위 class의 프로퍼티도 다 구현해야 함
    // interface implements 한 것이므로 super는 안 됨 
    x: number = 123;
    printX() {
        console.log(this.x + 123);
    }
}

let sel : SelectControl = new SelectControl();
sel.printX();