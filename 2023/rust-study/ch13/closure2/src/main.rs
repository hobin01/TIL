#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let mut list = [
        Rectangle{width: 10, height: 1},
        Rectangle{width: 3, height: 5},
        Rectangle{width: 7, height: 10},
    ];

    let mut sort_oper = 0;

    list.sort_by_key(|r| {
        sort_oper += 1;
        r.width
    });

    println!("{:?}, sorted in {sort_oper} oper", list);
}