fn main() {
    return_transfer_ownership();
}

fn string_test() {
    let mut s1 = String::new();
    s1.push_str("Hello world!");

    println!("{s1}");

    let mut s2 = String::from("Hello");
    s2.push_str(" world!");

    println!("{s2}");

    {
        let mut s3 = s2;
        s3.push_str(" Welcome to rust.");

        println!("{s3}");
    }

    // Error after move
    // println!("{s2}");

    let s4 = String::from("Hello");
    let mut s5 = s4.clone();
    s5.push_str(" world!");
    println!("{s4}");
    println!("{s5}");
}

fn stack_data_copy() {
    let s1 = 5;
    let s2 = s1; // stack data types are automatically copied

    println!("{s1}, {s2}");
}

fn ownership_vs_copy() {
    let s = String::from("hello");  // s comes into scope

    takes_ownership(s);             // s's value moves into the function...
                                    // ... and so is no longer valid here

    let x = 5;                      // x comes into scope

    makes_copy(x);                  // x would move into the function,
                                    // but i32 is Copy, so it's okay to still
                                    // use x afterward

} // Here, x goes out of scope, then s. But because s's value was moved, nothing
  // special happens.

fn takes_ownership(some_string: String) { // some_string comes into scope
    println!("{some_string}");
} // Here, some_string goes out of scope and `drop` is called. The backing
  // memory is freed.

fn makes_copy(some_integer: i32) { // some_integer comes into scope
    println!("{some_integer}");
} // Here, some_integer goes out of scope. Nothing special happens.

fn return_transfer_ownership() {
    let s1 = gives_ownership();
    let s2 = String::from("Hello world!");
    let s3 = takes_and_gives_back(s2);

    println!("{s1}, {s3}");
}

fn gives_ownership() -> String {
    let s1 = String::from("Welcome!");
    return s1;
}

fn takes_and_gives_back(s : String) -> String {
    return s;
}

fn returning_tuple() {
    let s1 = String::from("hello");

    let (s2, len) = calculate_length(s1);

    println!("The length of '{s2}' is {len}.");
}

fn calculate_length(s: String) -> (String, usize) {
    let length = s.len(); // len() returns the length of a String

    (s, length)
}