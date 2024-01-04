fn main() {
    let mut v: Vec<i32> = Vec::new();

    v.push(1);
    v.push(2);
    v.push(3);

    let v2 = vec![1,2,3];

    let second = &v[1];
    println!("{}", second);

    let second2 = &v[1];
    println!("{}", second2);

    let second3 = v2.get(1);
    match second3 {
        Some(second3) => println!("{}", second3),
        None => println!("aaa"),
    }

    let mut v3 = vec![1,2,3];
    let first = v3[0];
    v3.push(4);
    println!("first : {}", first);
    println!("fourth : {}", v3[3]);

    let mut v4: Vec<String> = vec![];
    v4.push(String::from("first"));
    //let first_string = v4[0];
    println!("{}", &v4[0]);
    v4.push(String::from("second"));
    v4[0] = String::from("first!!!!");
    println!("{}", &v4[0]);

    for i in &v4 {
        println!("{i}");
    }

    v4[0] = String::from("first___");

    for i in &mut v3 {
        *i += 10;
        println!("{}", &i);
    }

    for i in &mut v4 {
        *i = String::from("change!!!");
        println!("{}", &i);
    }
}
