use std::fs::File;
use std::io::{self, ErrorKind, Read};

fn main() {
    /* let file_result = File::open("hello.txt");

    let file = match file_result {
        Ok(file) => file,
        Err(error) => panic!("error : {:?}", error),
    }; */

    /* let file_result = File::open("hello.txt");
    let file = match file_result {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => match File::create("hello.txt") {
                Ok(fc) => fc,
                Err(err) => panic!("create error : {:?}", err),
            },
            other_error => {
                panic!("open error : {:?}", other_error);
            },
        },
    };

    println!("{:?}", file); */

    let file = File::open("hello.txt").unwrap_or_else(|error| {
        if error.kind() == ErrorKind::NotFound {
            File::create("hello.txt").unwrap_or_else(|error| {
                panic!("create error : {:?}", error);
            })
        } else {
            panic!("open error : {:?}", error);
        }
    });
}

fn read_username_from_file() -> Result<String, io::Error> {
    let username_file_result = File::open("hello.txt");
    let mut username_file = match username_file_result {
        Ok(file) => file,
        Err(err) => return Err(err),
    };

    let mut username = String::new();
    match username_file.read_to_string(&mut username) {
        Ok(_) => Ok(username),
        Err(err) => Err(err),
    }
}