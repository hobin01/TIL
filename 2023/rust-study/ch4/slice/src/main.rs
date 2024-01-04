fn main() {
    let s :String = String::from("hello world");
    let hello = &s[0..5];
    let world = &s[6..];

    println!("{}, {}", hello, world);

    let first = first_word(&s);
    println!("{}", first);

    let arr = [1,2,3,4,5];
    let slice_arr = &arr[1..3];
    for num in slice_arr {
        println!("{num}");
    }
}

fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        // index, byte value
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}