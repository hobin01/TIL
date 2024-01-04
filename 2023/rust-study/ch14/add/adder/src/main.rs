use add_one;
use rand;

fn main() {
    let num = 10;
    println!("{} + 1 = {}", num, add_one::add_one(num));
}