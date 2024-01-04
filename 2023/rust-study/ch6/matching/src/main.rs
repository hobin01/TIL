enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}

fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        None => None,
        Some(i) => Some(i+1),
    }
}

fn main() {
    let coin = Coin::Penny;
    value_in_cents(coin);

    let five = Some(5);
    plus_one(five);
    plus_one(None);

    let dice = 5;
    match dice {
        6 => print_six(),
        _ => print_other(),
    }
}

fn print_six() {
    println!("six!!!");
}

fn print_other() {
    println!("other!!");
}
