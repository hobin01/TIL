fn main() {
    let s = String::from("hello");
    takes_ownership(s);
    let x: i32 = 5;
    makes_copy(x);

    //println!("{s}"); // error by s is moved
    println!("{x}");

    let s1 = String::from("hello!");
    let len = calculate_len(&s1);
    println!("{}, {}", s1, len);

    let mut s2 = String::from("hello, ");
    
    let s3 = &mut s2;
    s3.push_str("world");

    println!("{}", s2);

    let mut s4 = String::from("hello world");
    let s5 = &s4;
    let s6 = &s4;
    println!("{}, {}", s5, s6);

    let s7 = &mut s4;
    s7.push_str("!!!!");
    println!("{}", s7);
}

fn takes_ownership(str: String) {
    println!("{str}");
}

fn makes_copy(num: i32) {
    println!("{num}");
}

fn calculate_len(s: &String) -> usize {
    s.len()
}