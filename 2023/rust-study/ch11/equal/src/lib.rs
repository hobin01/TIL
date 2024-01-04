pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[derive(PartialEq, Debug)]
    struct A{
        num: u32,
    }

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
        assert_ne!(result, 5);
    }

    #[test]
    fn struct_works() {
        let a1 = A{
            num: 1,
        };

        let a2 = A{
            num: 1,
        };

        assert_eq!(a1, a2);
    }
}
