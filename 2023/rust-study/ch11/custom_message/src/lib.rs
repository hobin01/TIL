pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 5, "not equal to 4!!!");
    }

    #[test]
    fn equal_check() {
        let result = 1;
        let result_check = 2;
        assert!(
            result == result_check,
            "result : {}, result_check : {}",
            result, result_check
        );
    }
}
