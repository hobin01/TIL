pub fn prints_and_returns_10(a: i32) -> i32 {
    println!("get value : {}", a);
    10
}

pub fn add_two(a: i32) -> i32 {
    a + 2
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn this_test_will_pass() {
        let value = prints_and_returns_10(4);
        assert_eq!(10, value);
    }

    #[test]
    fn this_test_will_fail() {
        let value = prints_and_returns_10(8);
        assert_eq!(5, value);
    }

    #[test]
    fn add_three_and_two() {
        assert_eq!(5, add_two(3));
    }

    #[test]
    fn add_one_hundred_and_two() {
        assert_eq!(102, add_two(100));
    }

    #[test]
    #[ignore]
    fn ignore_test() {
        panic!("this will be ignored");
    }
}
