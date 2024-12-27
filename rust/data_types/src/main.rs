use std::io;

fn main() {
    pass_variable();
}

fn type_specify() {
    let guess: u32 = "42".parse().expect("Not a number!");
    let tup = (500, 6.4, 1);
    let (x, y, z) = tup;
    println!("x={}, y={}, z={}", x, y, z);
    println!("x={}, y={}, z={}", tup.0, tup.1, tup.2);
}

fn array_ex() {
    let a = [1, 2, 3, 4, 5];
    println!("Enter array index:");

    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line.");

    let mut index: usize = input.trim().parse().expect("Not a valid number");

    let element = a[index];
    println!("Value at index={} is {}", index, element)
}

fn pass_variable() {
    let mut var:u32 = 10;
    process(&var);

    println!("Variable {}", var);

    var = 20;
    println!("Variable {}", var);
}

fn process(mut input: &u32) {
    println!("Input = {}", input);

    input = &30;
    println!("Updated = {}", input);
}