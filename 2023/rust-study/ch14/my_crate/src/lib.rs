//! # my_crate
//! `my_crate` is a crate for crate.io test

/// crate test
/// add num and 1
/// 
/// # Examples
/// 
/// ```
/// let arg = 5;
/// let ans = my_crate::add_one(arg);
/// assert_eq!(6, ans);
/// ```

pub fn add_one(x: i32) -> i32 {
    x + 1
}