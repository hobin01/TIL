mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }
}

pub fn eat_at_restaurant() {
    crate::front_of_house::hosting::add_to_waitlist(); // absolute path
    front_of_house::hosting::add_to_waitlist(); // relative path
}

fn deliver_order() {}

mod back_of_house {
    fn fix_incorrect_order() {
        cook_order();
        super::deliver_order();
    }

    fn cook_order() {}
}

mod back_of_house2 {
    pub struct Breakfast {
        pub toast: String,
        seasonal_fruit: String,
    }

    impl Breakfast {
        pub fn summer(toast: &str) -> Breakfast {
            Breakfast {
                toast: String::from(toast),
                seasonal_fruit: String::from("peaches"),
            }
        }
    }
}

pub fn eat_at_restaurant2() {
    // Order a breakfast in the summer with Rye toast
    let mut meal = back_of_house2::Breakfast::summer("Rye");
    // Change our mind about what bread we'd like
    meal.toast = String::from("Wheat");
    println!("I'd like {} toast please", meal.toast);

    // The next line won't compile if we uncomment it; we're not allowed
    // to see or modify the seasonal fruit that comes with the meal
    // meal.seasonal_fruit = String::from("blueberries"); // error by private
}

mod back_of_house3 {
    pub enum Appetizer {
        Soup,
        Salad,
    }
}

pub fn eat_at_restaurant3() {
    let order1 = back_of_house3::Appetizer::Soup;
    let order2 = back_of_house3::Appetizer::Salad;
}

mod front_of_house4 {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }
}

use crate::front_of_house4::hosting;

pub fn eat_at_restaurant4() {
    hosting::add_to_waitlist();
}

mod front_of_house5 {
    pub mod hosting5 {
        pub fn add_to_waitlist() {}
    }
}

use crate::front_of_house5::hosting5;

mod customer {
    pub fn eat_at_restaurant() {
        // hosting5::add_to_waitlist(); // error by scope of hosting5
        super::hosting5::add_to_waitlist();
    }
}

use rand::Rng;

fn rng_1to100() {
    rand::thread_rng().gen_range(1..=100);
}