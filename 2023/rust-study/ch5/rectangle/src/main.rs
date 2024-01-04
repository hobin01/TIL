struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let width1 = 30;
    let height1 = 50;

    print_area(area(width1, height1));

    let rect1 = (30, 50);
    print_area(area(rect1.0, rect1.1));

    let rect2 = Rectangle {
        width: 30,
        height: 50,
    };

    print_area(area(rect2.width, rect2.height));

}

fn print_area(area: u32) {
    println!(
        "The are of the rectangle is {} sqaure",
        area
    );
}

fn area(width: u32, height: u32) -> u32 {
    return width * height;
}