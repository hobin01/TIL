fn main() {
    println!("Hello, world!");

    another_function(5);

    let y = {
        let x = 3;
        x + 1
    };

    println!("{y}");

    let y = five(5);
    println!("{}", y);
}

fn another_function(x: i32) {
    println!("another function!, {}", x);
}

fn five(x: i32) -> i32 {
    let y = x * 5;
    let z = y * 5;
    return z;
}