use std::collections::HashMap;

fn main() {
    let mut scores = HashMap::new();
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Red"), 30);

    let team1 = String::from("Blue2");
    let b = scores.get(&team1).copied().unwrap_or(0);

    println!("{b}");

    for (k, v) in &scores {
        println!("{}, {}", k, v);
    }

    let ks = "Yello".to_string();
    scores.insert(ks, 10);
    // println!("{ks}"); // error by move
}