trait Animal {
    fn speak(&self);
}
struct Cat;
struct Dog;

impl Animal for Cat {
    fn speak(&self) {
        println!("Meow");
    }
}

impl Animal for Dog {
    fn speak(&self) {
        println!("Woof");
    }
}

fn main() {
    let animals : Vec<Box<dyn Animal>> = vec![
        Box::new(Cat),
        Box::new(Dog)
    ];
    for animal in animals {
        animal.speak();
    }
}