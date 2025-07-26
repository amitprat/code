fn apply<F>(f: F) where F:FnOnce() {
    f();
}

fn apply_to_3<F>(f: F) -> i32 where F:Fn(i32) -> i32 {
    f(3)
}

fn main() {
    use std::mem;

    let greeting = "Hello";
    let mut farewell = "goodbye".to_owned();
    let diary = || {
        println!("I said {}.", greeting);

        farewell.push_str("!!!");
        println!("Then i screamed {}.", farewell);
        println!("Now i can sleep.");

        mem::drop(farewell);
    };

    apply(diary);

    let double = |x| 2*x;
    println("3 double={}.", apply_to_3(double));
}