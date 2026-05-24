use rand::Rng;
use std::cmp::Ordering;
use std::io::{self, Write};

fn main() {
    let secret_number: i32 = rand::thread_rng().gen_range(1, 100);

    loop {
        print!("Guess the number: ");
        io::stdout().flush().expect("Failed to flush!");

        let mut guess = String::new();
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line!");
        let guess: i32 = guess.trim().parse().expect("Failed to parse number!");
        println!("Guessed number: {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Small"),
            Ordering::Greater => println!("Big"),
            Ordering::Equal => {
                println!("Guessed correct, exiting game!");
                break;
            }
        }
    }
}
