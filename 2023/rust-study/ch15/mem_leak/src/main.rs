use std::cell::RefCell;
use std::rc::{Rc, Weak};

#[derive(Debug)]
struct Node {
    val: i32,
    child: RefCell<Vec<Rc<Node>>>,
    parent: RefCell<Weak<Node>>,
}

fn main() {
    let leaf = Rc::new(Node {
        val: 3, 
        child: RefCell::new(vec![]), 
        parent: RefCell::new(Weak::new()),
    });

    println!("leaf parent : {:?}", leaf.parent.borrow().upgrade());

    let branch = Rc::new(Node {
        val: 5, 
        child: RefCell::new(vec![Rc::clone(&leaf)]),
        parent: RefCell::new(Weak::new()),
    });

    *leaf.parent.borrow_mut() = Rc::downgrade(&branch);

    println!("leaf parent : {:?}", leaf.parent.borrow().upgrade());
}