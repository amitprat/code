pub mod name_helpers {
    pub fn get_name(first: String, last: String) -> String {
        return format!("{} {}", first, last);
    }
}

pub mod condition_helpers {
    pub fn test_if() {
        let age_limit: u8 = 25;

        println!("Enter person age:");
        let mut str_buf = String::new();
        std::io::stdin().read_line(&mut str_buf).unwrap();
        let input_age = str_buf.trim().parse::<u8>().unwrap();

        if input_age >= age_limit {
            println!("Can get license");
        } else {
            println!(
                "Wait for {} years to get license. Age limit for license is {}.",
                age_limit - input_age,
                age_limit
            );
        }
    }

    pub fn test_while() {
        let age_limit: u8 = 25;

        let mut cur_age = 18;

        while cur_age < age_limit {
            println!("Waiting...");
            cur_age += 1;
        }

        println!(
            "Congrats! Your new age {} is eligible to get license.",
            cur_age
        );
    }

    pub fn test_loop() {
        let mut x: u8 = 1;
        loop {
            println!("hello from rust");

            if x > 5 {
                break;
            }

            x += 1;
        }

        println!("x = {}", x);
    }

    pub fn test_for() {
        let ages: [i32; 5] = [1, 2, 3, 4, 5];

        for val in ages {
            println!("current age: {}", val)
        }
    }
}
