use std::{fs};
use std::io::{Write};

pub fn read_file(file_path: &str) -> String {
    let content = fs::read_to_string(file_path).expect("should be able to read file");
    content
}

pub fn create_file(file_path: &str) -> std::io::Result<()>{
    let _ = fs::File::create(file_path)?;

    Ok(())
}

pub fn write_file(file_path: &str) -> std::io::Result<()> {
    let mut file = fs::File::create(file_path)?;
    file.write_all(b"Hello world!")?;

    Ok(())
}