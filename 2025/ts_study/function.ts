import output from "./output"

function get(first: string, second: string) : string {
    return first + " " + second;
}

output(get("123", "123"));

function get2(first?: string, second?: string) : string | undefined {
    return first;
}

output(get2("123"));
output(get2(undefined, "234"));

function get3(first: string = "123", second: string): string {
    return first + " " + second;
}

output(get3("234", "234"));
output(get3(undefined, "234"));

function get4(first: string, second: string = "234") {
    return first + " " + second;
}

output(get4("123"));
output(get4("123", "123"));

function get5(first: string, ...second: string[]) : string {
    return first + " " + second.join(" ");
}

output(get5("123", "123", "234", "345"));

// 선언만 한 경우 오버라이드 가능 
function get6(x: number) : void;
function get6(x: string) : void;
function get6(x : any) : void {
    if(typeof x == "number") {
        console.log(x);
    }
    if(typeof x == "string") {
        console.log(x + "!!!");
    }
}

get6(123);
get6("123");