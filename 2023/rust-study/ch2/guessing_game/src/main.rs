use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    println!("Guess the number!");

    // 1 ~ 100 random number
    let secret_number = rand::thread_rng().gen_range(1..=100);

    loop {

        println!("Input your number.");

        let mut guess = String::new();

        // stdin to guess
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        
        // parse to u32
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num, // num : result of parsing
            Err(_) => continue, // Err(_) : any error value
        }; // 대입하는 것이므로 ; 필요

        println!("You guessed : {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("small!"),
            Ordering::Greater => println!("big!"),
            Ordering::Equal => {
                println!("same!!!!!");
                break; // break loop
            },
        }
    }
}