#[derive(Debug, PartialEq, Copy, Clone)]
enum ShirtColor {
    Red,
    Blue
}

struct Inventory {
    shirts: Vec<ShirtColor>
}

impl Inventory {
    fn giveaway(&self, user_preference: Option<ShirtColor>) -> ShirtColor {
        user_preference.unwrap_or_else(||{self.most_stocked()})
    }

    fn most_stocked(&self) -> ShirtColor {
        let mut num_red = 0;
        let mut num_blue = 0;

        for color in &self.shirts {
            match color {
                ShirtColor::Red => num_red += 1,
                ShirtColor::Blue => num_blue += 1,
            }
        } 

        if num_red > num_blue {
            ShirtColor::Red
        } else {
            ShirtColor::Blue
        }
    }
}

// let expensive_color = |num:u32| -> u32{
//     println!("calculating slowly....");
//     thread::sleep(Duration::from_secs(2));

//     num
// };

// fn add_one_v1 (x:u32) -> u32 {x+1}
// let add_one_v2 = |x:u32| -> u32 {x+1};
// let add_one_v3 = |x| {x+1};
// let add_one_v4 = |x| x+1;

fn borrow_immutable() {
    let list = vec![1,2,3];
    println!("Before defining closure: {list:?}");

    let only_borrows = || println!("From closure: {:?}", list);

    println!("Before calling closure: {list:?}");

    only_borrows();

    println!("After calling closure: {list:?}");
}

fn borrow_mutable() {
    let mut list = vec![1,2,3];

    println!("Before defining closure: {list:?}");

    let mut borrow_mutably = || list.push(4);

    borrow_mutably();

    println!("After calling closure: {list:?}");
}

fn move_to_thread() {
    let list = vec![1,2,3];
    thread.spawn(move || println!("From thread: {list:?}")).join().unwrap();
}

fn main() {
    let store = Inventory {
        shirts: vec![ShirtColor::Blue, ShirtColor::Red, ShirtColor::Blue]
    };

    let user_pref1 = Some(ShirtColor::Red);
    let giveaway1 = store.giveaway(user_pref1);

    println!("User with preference {:?} gets {:?}", user_pref1, giveaway1);

    let user_pref2 = None;
    let giveaway2 = store.giveaway(user_pref2);

    println!("User with preference {:?} gets {:?}", user_pref2, giveaway2);

    borrow_immutable();
    borrow_mutable();

    // let v1 = add_one_v1(1);
    // let v2 = add_one_v2(1);
    // let v3 = add_one_v3(1);
    // let v4 = add_one_v4(1);

    // println!("Value: {v1} {v2} {v3} {v4}");
}