struct User {
    active: bool,
    name: String,
    email: String,
    sign_in_count: u64,
}


fn main() {
    let mut user1 = User {
        active: true,
        name: String::from("name123"),
        email: String::from("email@abc.com"),
        sign_in_count: 1,
    };

    user1.name = String::from("name_change");

    let user2 = User{
        ..user1
    };

    println!("{}", user2.name);

    // println!("{}", user1.name); // error by move
}
