use std::{fs, env};
pub mod file;

pub struct Config<'a> {
    pub query: &'a str,
    pub file_path: &'a str,
    pub ignore_case: bool
}

pub struct Config2 {
    pub query: String,
    pub file_path: String,
    pub ignore_case: bool
}

impl<'a> Config<'a> {
    pub fn new(args: &'a [String]) -> Config<'a> {
        if args.len() < 3 {
            panic!("not enough arguments.");
        }

        let query = args[1].as_str();
        let file_path = args[2].as_str();
        let ignore_case = env::var("IGNORE_CASE").is_ok();

        Config {query, file_path, ignore_case}
    }

    pub fn build(args: &'a [String]) -> Result<Config<'a>, &'static str> {
        if args.len() < 3 {
            return Err("not enough arguments.");
        }

        let ignore_case = env::var("IGNORE_CASE").is_ok();
        Ok(Config {query: args[1].as_str(), file_path: args[2].as_str(), ignore_case})
    }

    pub fn build2(mut args: impl Iterator<Item=String>)->Result<Config2, &'static str> {
        args.next();

        let query = match args.next() {
            Some(arg) => arg,
            None => return Err("No query provided")
        };
        
        let file_path = match args.next() {
            Some(arg) => arg,
            None => return Err("No file_path provided")
        };

        let ignore_case = env::var("IGNORE_CASE").is_ok();

        Ok(Config2 {query, file_path, ignore_case})
    }
}

pub fn run(config: &Config) -> Result<(), Box<dyn std::error::Error>> {
    let content = fs::read_to_string(config.file_path)?;

    let results = if config.ignore_case {
        search_case_insensative(config.query, &content)
    } else {
        search(config.query, &content)
    };

    for line in results {
        println!("{line}");
    }

    Ok(())
}

pub fn run(config: &Config2) -> Result<(), Box<dyn std::error::Error>> {
    let content = fs::read_to_string(config.file_path)?;

    let results = if config.ignore_case {
        search_case_insensative(&config.query, &content)
    } else {
        search(&config.query, &content)
    };

    for line in results {
        println!("{line}");
    }

    Ok(())
}

pub fn search<'a>(query: &str, content: &str) -> Vec<&'a str> {
    content.line().filter(|line| line.contains(query)).collect()
}

pub fn search<'a>(query: &str, content: &'a str) -> Vec<&'a str> {
    let mut result = Vec::new();

    for line in content.lines() {
        if line.contains(query) {
            result.push(line.trim());
        }
    }

    result
}

pub fn search_case_insensative<'a>(query: &str, content: &'a str) -> Vec<&'a str> {
    let mut result = Vec::new();

    for line in content.lines() {
        if line.to_lowercase().contains(&query.to_lowercase()) {
            result.push(line.trim());
        }
    }

    result
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn one_result() {
        let query = "duct";
        let content = "\
                        Rust:
                        safe, fast, productive.
                        Pick three.";

        assert_eq!(vec!["safe, fast, productive."], search(query, content));
    }

    #[test]
    fn two_result() {
        let query = "duct";
        let content = "\
                        Rust:
                        safe, fast, productive.
                        Pick three.";

        assert_eq!(vec!["safe, fast, productive."], search_case_insensative(query, content));
    }
}