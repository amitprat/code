fn main() {
    fizzbuzz_to(10);
}

fn fizzbuzz_to(n: u32) {
    for n in 1..=n {
        fizzbuzz(n);
    }
}

fn fizzbuzz(n: u32) {
    if is_divisible(n, 15) {
        println!("fizbizz");
    } else if is_divisible(n, 5) {
        println!("fizz");
    } else if is_divisible(n, 3) {
        println!("buzz");
    } else {
        println!("{}", n);
    }
}

fn is_divisible(n: u32, m:u32) -> bool {
    if m == 0 {
        return false;
    }

    return n%m == 0;
}