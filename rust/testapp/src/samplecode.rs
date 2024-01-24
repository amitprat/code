use std::fs::File;
use std::io::{self, BufRead};

/// This module contains all different way to print.
pub mod helloworld {
    pub fn sayhello() {
        println!("{}, {}!", "Hello", "world"); // Hello, world!
        println!("{0}, {1}!", "Hello", "world"); // Hello, world!
        println!("{greeting}, {name}!", greeting = "Hello", name = "world"); // Hello, world!

        let (greeting, name) = ("Hello", "world"); // 💡 Two Variable bindings declare & initialize in one line.
        println!("{greeting}, {name}!"); // Hello, world!

        println!("{:?}", [1, 2, 3]); // [1, 2, 3] - Debug print
        println!("{:#?}", [1, 2, 3]); // Debug print

        // 🔎 The format! macro is used to store the formatted string.
        let x = format!("{}, {}!", "Hello", "world");
        println!("{}", x); // Hello, world!

        // 💡 Rust has a print!() macro as well
        print!("Hello, world!"); // Without new line
        println!(); // A new line

        print!("Hello, world!\n"); // With new line
    }

    #[cfg(test)]
    mod tests {
        use super::sayhello;

        #[test]
        fn test_hello() {
            sayhello();
        }
    }
}

pub mod variablebinding {
    const PI: f64 = 3.14159265359;

    #[cfg(test)]
    mod tests {
        #[test]
        fn validate_variable_assignment() {
            let a;
            a = 6;
            assert_eq!(a, 6);

            let b: i8;
            b = 10;
            assert_eq!(b, 10);

            let t = true;
            let f: bool = false;
            assert_eq!(true, t);
            assert_eq!(false, f);

            let (x, y) = (1, 2); // tuple
            assert_eq!(x, 1);
            assert_eq!(y, 2);
            println!("x={x}, y={y}");

            #[warn(unused_assignments)]
            let mut x = 10; // update value of x
            x = 20;
            assert_eq!(x, 20);

            let z = { x + y };
            assert_eq!(z, 22);

            let z = {
                let x = 10;
                let y = 20;
                x + y
            }; // reassign value to z allowed
            assert_eq!(30, z);

            // The const keyword is used to define constants and after the assignment their values are not allowed to change.
            // They live for the entire lifetime of a program but has no fixed address in the memory.
            const N: i32 = 100;
            println!("N={N}");

            // The static keyword is used to define a "global variable" type facility.
            // There is only one instance for each value, and it’s at a fixed location in memory.
            static M: i32 = 200;

            // variable shadowing
            let x: f64 = -20.48; // float
            let x: i64 = x.floor() as i64; // int
            println!("{}", x); // -21

            let s: &str = "hello"; // &str
            let s: String = s.to_uppercase(); // String
            println!("{}", s); // HELLO

            println!("π value is {}", super::PI);
        }
    }
}

pub mod data_types {
    pub fn data_types() {
        let mut vec1: Vec<i32> = Vec::with_capacity(2); // capacity is 2 but length is still 0.
        vec1.push(0);
        vec1.push(1);
        vec1[0] = 1;
        vec1[1] = 2;
        println!("vec1:{:?}", vec1);

        let mut vec2 = Vec::new();
        vec2.push(10);
        vec2.push(20);
        vec2.pop();
        vec2.remove(0);
        println!("vec2:{:#?}", vec2);

        let mut vec3: Vec<i32> = vec![1, 2, 3];
        vec3[0] = 0;
        vec3[1] = 2;
        vec3[2] = 2;
        println!("{:?}", vec3);

        let mut vec4 = Vec::new();
        for i in 0..10 {
            vec4.push(i);
        }

        let print_vec = || {
            println!("{:?}", vec4);
        };
        print_vec();

        for i in &mut vec4 {
            *i = *i * 2;
        }
        println!("{:?}", vec4);
    }

    #[cfg(test)]
    mod tests {
        #[test]
        fn test() {
            super::data_types();
        }
    }
}

pub mod struct_test {
    #[derive(Debug)]
    struct Color {
        red: u8,
        green: u8,
        blue: u8,
    }

    pub fn structs() {
        let mut black = Color {
            red: 0,
            blue: 0,
            green: 0,
        };
        println!("black: {:?}", black);
        println!(
            "black: red:{0},blue:{1},green:{2}",
            black.red, black.blue, black.green
        );
        black.red = 255;

        // tuple struct
        struct Color2(u8, u8, u8);
        let Color2(r, g, b) = Color2(200, 200, 200);
        println!("Black = rgb({}, {}, {})", r, g, b);
    }

    #[cfg(test)]
    mod tests {
        #[test]
        pub fn test1() {
            super::structs();
        }
    }
}

pub mod enum_tests_mod {
    #[derive(Debug)]
    enum Day {
        SUNDAY,
        MONDAY,
    }

    enum FlashMessage {
        Success,
        Warning { category: i32, message: String },
        Error(String),
    }

    pub fn enum_tests() {
        let day = Day::MONDAY;
        println!("day={:?}", day);

        let mut msg = FlashMessage::Success;
        print_msg(msg);

        msg = FlashMessage::Warning {
            category: 1,
            message: String::from("Undefined"),
        };
        print_msg(msg);

        msg = FlashMessage::Error(String::from("Critical Error"));
        print_msg(msg);
    }

    fn print_msg(m: FlashMessage) {
        match m {
            FlashMessage::Success => println!("Success"),
            FlashMessage::Warning { category, message } => {
                println!("Warning, category={category}, message={message}");
            }
            FlashMessage::Error(err) => println!("Error: {err}"),
        }
    }

    #[cfg(test)]
    mod tests {
        #[test]
        fn test1() {
            super::enum_tests();
        }
    }
}

pub mod generic_tests_mod {
    use std::fmt;
    use std::fmt::Formatter;

    fn take_one_arg<T>(x: T) {}

    fn take_two_arg_of_same_type<T>(x: T, y: T) {}

    fn take_two_arg_of_different_type<T, U>(x: T, y: U) {}

    struct Point<T> {
        x: T,
        y: T,
    }

    /*
    impl<T> ToString for Point<T> where T: ToString {
        fn to_string(&self) -> String {
            format!("[{x}, {y}]")
        }
    }
    */

    impl<T> fmt::Display for Point<T>
    where
        T: fmt::Display,
    {
        fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
            write!(f, "[{0},{1}]", self.x, self.y)
        }
    }

    pub fn generic_tests() {
        let point: Point<i32> = Point { x: 1, y: 2 };
        println!("point={}", point);
    }

    /*
    lazy_static! {
        static ref dict: HashMap<&'static str, i32> = {
            let mut map = HashMap::new();
            map.insert("one", 1);
            map
        };
    }
    */

    mod file_words_count {
        use std::io::BufRead;
        use tokio::io::AsyncBufReadExt;

        fn get_word_count(filename: &str) -> Result<u32, &str> {
            //let file = ::std::fs::File::open(filename);
            //let reader = std::io::BufReader::new(file);
            //let lines = reader.buffer().lines();

            let mut word_count: u32 = 0;
            //for line in  lines {
            //    let line = line.unwrap();
            //    word_count += line.split_whitespace().count();
            //}

            Ok(word_count)
        }

        pub fn test() {
            let filename = "testfile.txt";
            let word_count = get_word_count(filename);
            match word_count {
                Ok(count) => println!("Words count {count}."),
                Err(e) => println!("Error occurred reading file."),
            }
        }
    }

    #[cfg(test)]
    mod tests {
        #[test]
        fn test1() {
            super::generic_tests();
        }

        #[test]
        fn test2() {
            super::file_words_count::test();
        }
    }
}

pub mod traits {
    struct Person {
        firstname: String,
        lastname: String,
        age: u8,
    }

    struct Employee {
        title: String,
        level: u8,
    }

    struct Engineer {
        person: Person,
        employee: Employee,
    }

    trait FullName {
        fn get_full_name(&self) -> String;
    }

    trait Designation {
        fn get_designation(&self) -> String;
    }

    trait Display: FullName + Designation {
        fn get_string(&self) -> String {
            return format!(
                "Name={0}, Designation={1}",
                self.get_full_name(),
                self.get_designation()
            );
        }
    }

    impl FullName for Engineer {
        fn get_full_name(&self) -> String {
            return format!(
                "{0} {1} {2}",
                self.person.firstname, self.person.lastname, self.person.age
            );
        }
    }

    impl Designation for Engineer {
        fn get_designation(&self) -> String {
            return format!("{0}_L{1}", self.employee.title, self.employee.level);
        }
    }

    impl Display for Engineer {}

    // static methods
    impl Person {
        fn new(firstname: String, lastname: String, age: u8) -> Person {
            Person {
                firstname,
                lastname,
                age,
            }
        }
    }

    impl Employee {
        fn new(title: String, level: u8) -> Employee {
            Employee { title, level }
        }
    }

    impl Engineer {
        fn new(firstname: String, lastname: String, age: u8, title: String, level: u8) -> Engineer {
            Engineer {
                person: Person::new(firstname, lastname, age),
                employee: Employee::new(title, level),
            }
        }
    }

    pub fn test() {
        let engineer = Engineer::new(
            String::from("Amit"),
            String::from("Singh"),
            25,
            String::from("Software Engineer"),
            5,
        );
        println!("Engineer={}", engineer.get_string());
    }

    struct Cat {
        sound: String,
    }

    struct Dog {
        sound: String,
    }

    trait GetSound {
        fn get_sound(&self) -> String;
    }

    impl GetSound for Cat {
        fn get_sound(&self) -> String {
            return self.sound.clone();
        }
    }

    impl GetSound for Dog {
        fn get_sound(&self) -> String {
            return self.sound.clone();
        }
    }

    fn make_sound<T: GetSound>(t: &T) {
        println!("{0}!", t.get_sound())
    }

    pub fn test1() {
        let cat = Cat {
            sound: "Meow".to_string(),
        };
        let dog = Dog {
            sound: "Ding Dong".to_string(),
        };

        make_sound(&cat);
        make_sound(&dog);
    }

    #[cfg(test)]
    mod tests {
        #[test]
        fn test1() {
            super::test();
        }

        #[test]
        fn test2() {
            super::test1();
        }
    }
}
