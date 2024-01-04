fn main() {
    let s1 = String::from("abcdef");
    let s2 = "xyz";

    let result = longest(s1.as_str(), s2);
    println!("{}", result);
}

fn longest<'a>(s1: &'a str, s2: &'a str) -> &'a str {
    if s1.len() > s2.len() {
        s1
    } else {
        s2
    }
}
