import output from "./output";

let done: boolean = false;
let num: number = 123;
let str: string = "123123";
let expr: string = `hello
hello
hello
${num}`;
let arr: Array<number> = [1,2,3];
let arr2 : Array<number> = arr.slice();
arr2[2] = 4;
let tup: [string, number];
tup = ["abcd", 1234];

enum Color {Red, Green, Blue};
let c: Color = Color.Green;
let c2: string = Color[2];

let v: any = true;
v = 123;
// v.something(); // 컴파일은 통과함 (any 타입은 별도 검사 안 함.) (런타임에서 에러 발생)
let arrV: Array<any> = ["something", 123];

// never : 절대 발생할 수 없는 타입. 발생해서 안 되거나 에러 일으킬 때 사용. any도 never에 할당 불가. 
let nev = (): never => {throw Error('error!')};

// <number>와 같이 형변환 가능하지만, jsx 호환성 때문에 as 많이 씀
let a: any = "123";
let b: number = a as number;

output(done)
output(num)
output(str)
output(expr)
output(arr)
output(arr2)
output(tup)
output(c)
output(c2)
output(v);
output(arrV);
// output(nev());
output(b);
