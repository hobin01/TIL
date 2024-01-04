fn main() {
    let tup: (i32, f32, bool) = (100, 1.00, true);
    let (x, y, z) = tup;
    let x1 = tup.0;
    let arr = [1,2,3];
    let arr2: [i32; 5] = [1,2,3,4,5];
    let arr3 = [3;5];
    let arr4: [i32; 5] = [3;5];

    println!("{}", arr4[0]);
}
