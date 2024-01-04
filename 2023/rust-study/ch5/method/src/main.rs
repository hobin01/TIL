#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn print_area(&self) {
        println!("area : {}", self.area());
    }

    fn change_width(&mut self, new_width: u32) {
        self.width = new_width;
    }

    fn moved(self) {
        println!("move!!! {:?}", self);
    }
}

fn main() {
    let mut rect = Rectangle {
        width: 30,
        height: 50,
    };

    rect.print_area();

    rect.change_width(50);

    rect.print_area();

    // rect.moved(); // no more use rect by move

    println!("{:?}", rect);
}