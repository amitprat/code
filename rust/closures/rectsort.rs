#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32
}

fn main() {
    let mut list = vec![
        Rectangle { width: 10, height: 1 },
        Rectangle { width: 3, height: 5 },
        Rectangle { width: 7, height: 12 },
        Rectangle {width: 1, height: 2},
        Rectangle {width: 0, height: 1},
        Rectangle {width: 10, height: 8}
    ];

    list.sort_by_key(|r| r.width);
    println!("{list:#?}");
}