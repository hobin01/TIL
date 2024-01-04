use test_config;

#[test]
fn it_add_two() {
    assert_eq!(4, test_config::add_pub(2, 2));
    // assert_eq!(4, test_config::add(2, 2)); // error by private fn
}