use std::env;
use std::io;
use std::fs::File;
use std::io::Read;
use std::io::ErrorKind;

#[warn(dead_code)]
fn read_to_string(filename: &str) -> io::Result<String> {
    let mut file = File::open(&filename)?;
    let mut text = String::new();
    file.read_to_string(&mut text)?;
    Ok(text)
}

fn file_error_handling(filename: &str) {
    let file = File::open(&filename);

    let greeting_file = match file {
        Ok(file) => file,
        Err(error) => match error.kind() {
            ErrorKind::NotFound => match File::create(filename) {
                Ok(file) => file,
                Err(e) => panic!("Error occurred while creating file: {e:?}")
            },
            _=> panic!("Error opening file")
        }
    };

    greeting_file.write_at("hellow", 0).unwrap();
}

fn main() {
    file_error_handling("test");

    let first = env::args().nth(1).expect("please supply a filename");

    let mut file = File::open(&first).expect("can't open the file");

    let mut text = String::new();
    file.read_to_string(&mut text).expect("can't read the file");

    println!("file had {} bytes", text.len());

    println!("{}", text);
}