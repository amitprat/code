use std::panic;

pub fn data_types() {
    let tuple = ("amit", "pratap", "singh", 36);
    println!("Tuple: {:?}", tuple);

    let mut str: &str = "amit pratap singh";
    println!("String reference: {0}", str);

    str = "singh";
    println!("Updated string reference: {0}", str);

    let mut str_type: String = String::from("Amit Pratap Singh");
    println!("String data type: {0}", str_type);

    str_type = String::from("Hello World");
    println!("Mutated String datatype: {0}", str_type);

    #[derive(Debug)]
    struct Student<'a> {
        age: u8,
        name: &'a str,
    }

    fn consume_box(my_box: Box<Student>) {
        println!("Moved Student ownership to function: {:?}", my_box);
    }

    fn consume_student(student: Student) {
        println!("Moved Student ownership to function: {:?}", student);
    }

    let box_type: Box<Student> = Box::new(Student {
        age: 32,
        name: "Amit Singh",
    });
    println!("Heap allocated Student struct: {:?}", box_type);

    consume_box(box_type);

    let student: Student = Student {
        age: 24,
        name: "Amit Singh",
    };
    println!("Stack allocated student: {:?}", student);

    consume_student(student);

    let student1: Option<Student> = None;
    println!("Student1: {:?}", student1);

    let student2: Option<Student> = Some(Student {
        age: 34,
        name: "Singh",
    });
    println!("Student2: {:?}", student2);

    let arr: [&str; 3] = ["amit", "pratap", "singh"];
    println!("array: {:?}", arr);

    let result = panic::catch_unwind(|| {
        let age_slice: &[&str] = &arr[1..4];
        return age_slice;
    });

    match result {
        Ok(out) => println!("Result: {:?}", out),
        Err(_) => println!("Caught exception"),
    }
    println!("Program ends");

    let mut vec_arr: Vec<i8> = vec![1, 2, 3, 4, 5];
    vec_arr.push(6);
    vec_arr.remove(0);

    println!("{:?}", vec_arr);

    for x in &mut vec_arr {
        *x = *x * 2;
    }

    println!("{:?}", vec_arr)
}
