fn main() {
    let mut s = String::new();
    s.push('a');
    s.push_str(" string");

    println!("{}", &s);

    let hello = "hello";
    let mut s2 = hello.to_string();
    s2.push(' ');
    s2.push_str("world");

    println!("{}", &s2);

    s2.push_str(&s);
    println!("{}", &s);
    println!("{}", &s2);

    s.push('a');

    let mut ss = String::new();
    let ss1 = "hello".to_string();
    let ss2 = " world".to_string();
    
    ss = format!("{}+++{}", ss1, ss2);
    println!("{ss}");
    println!("{ss1}");

    let hh = &ss[0..1];
    println!("{}", &hh);

    let sss = "sss123";
    let sss2 = &sss[0..1];
    println!("{}", &sss2);

    for c in sss.chars() {
        println!("{c}");
    }

    for b in sss.bytes() {
        println!("{b}");
    }
}
