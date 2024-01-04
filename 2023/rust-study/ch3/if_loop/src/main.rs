fn main() {
    let num : i32 = 3;
    if num < 5 {
        println!("< 5");
    }
    else {
        println! (" >= 5");
    }

    let condition: bool = true;
    let x = if condition {5} else {6};
    println!("{x}");

    let mut cnt = 0;
    let result = loop {
        cnt += 1;
        if cnt == 10 {
            break cnt * 2;
        }
    };

    println!("{result}");

    while cnt > 0 {
        println!("{cnt}");
        cnt -= 1;
    }

    let arr = [10, 20, 30];
    for ele in arr {
        println!("{ele}");
    }

    for num in 1..5 {
        println!("{num}");
    }

    for num in (1..5).rev() {
        println!("{num}");
    }
}
