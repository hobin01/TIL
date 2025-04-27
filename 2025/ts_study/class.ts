import output from "./output"

class Animal {
    name: string;
    constructor(name: string) {
        this.name = name;
    }
    move(dist: number = 0) : void {
        console.log(`${this.name} move ${dist}.`);
    }
}

class Snake extends Animal {
    constructor(name: string) {
        super(name);
    }
    move(dist: number) : void {
        super.move(dist);
    }
}

let snake : Snake = new Snake("snake");
snake.move(5);

// 기본적으로 public
// private, protected도 일반적인 oop랑 똑같이 사용 가능 
// readonly도 다 적용 가능 

class Employee {
    private _fullname: string;

    // getter, setter 지원 
    public get fullname(): string {
        return this._fullname;
    }

    public set fullname(name: string) {
        this._fullname = name;
    }
}

let emp : Employee = new Employee();
// getter, setter 적용 방법 
emp.fullname = "name!!!!";
console.log(emp.fullname)

