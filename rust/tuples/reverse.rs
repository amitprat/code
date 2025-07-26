fn reverse(pair: (i32, bool)) -> (bool, i32) {
    let (val, flag) = pair;
    (flag, val)
}

fn main() {
    let val = (1, false);
    let reversed_val = reverse(val);

    println!("val: {val:?}, reversed_val: {reversed_val:?}");
}