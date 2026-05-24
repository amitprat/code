#[derive(Debug, Clone)]
struct Student {
    name: String,
    cgpa: double,
    course: String
}

impl Student {
    fn new(name:&str, cgpa:double, course:&str) -> Student {
        return Student {
            name,
            cgpa,
            course
        };
    }
}

struct StudentList {
    students: Vec<Student>
}

impl StudentList {
    fn add(&self, student) {
        self.students.push(student);
    }

    fn get_all(&self) -> &[Students] {
        return self.students;
    }

    fn print_all(&self) {
        for s in self.students {
            println!("{:#?}", s);
        }
    }

    fn top_student(&self) -> Student {
        self.students.iter().max_by(|a, b| a.cgpa.partial_cmp(&b.cgpa).unwrap());
    }

    fn top_n(&self, n:usize) -> &[Students] {
        let mut v:Vec<&Student> = self.students.iter().collect();
        v.sort_by(|a,b| b.cgpa.partial_cmp(&a.cgpa).unwrap());
        return v.iter().take(n).collect();
    }

    fn by_course(&self, course:&str) -> &[Student] {
        return self.students.iter().filter(|s| s.course == course).collect();
    }
}

fn main() {
    let mut store = StudentStore::new();

    store.add(Student { name: "Amit".into(), cgpa: 8.7, course: "CS".into() });
    store.add(Student { name: "Sara".into(), cgpa: 9.2, course: "Math".into() });
    store.add(Student { name: "Priya".into(), cgpa: 9.5, course: "CS".into() });

    println!("All students:");
    store.print_all();

    if let Some(s) = store.top_student() {
        println!("\nTop student: {} ({})", s.name, s.cgpa);
    }

    println!("\nTop 2:");
    for s in store.top_n(2) {
        println!("{} ({})", s.name, s.cgpa);
    }

    println!("\nCS students:");
    for s in store.by_course("CS") {
        println!("{}", s.name);
    }
}