struct Point<T, U> {
    x: T,
    y: U,
}

impl<T, U> Point<T, U> {
    fn x(&self) -> &T {
        &self.x
    }
}

impl Point<f32, f32> {
    fn distance(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}

fn main() {
    let number_list = vec![12, 34, 56, 78];
    let char_list = vec!['a', 'b', 'c', 'd'];
    //let result = largest(&number_list);
    //println!("{}", result);
    //let result = largest(&char_list);
    //println!("{}", result);

    let intP = Point {x: 1, y: 2};
    let floatP = Point {x: 1.0, y: 2.0};
    let mixP = Point {x: 1, y : 2.0};
}