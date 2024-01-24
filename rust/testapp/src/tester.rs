mod async1;
mod closures_test;
mod helpers;
mod samplecode;

#[allow(dead_code)]
pub fn test() {
    samplecode::helloworld::sayhello();
}

#[allow(dead_code)]
fn test_closures() {
    closures_test::simple_closure::test_closures();
}

#[allow(dead_code)]
fn test_helpers() {
    let full_name = helpers::name_helpers::get_name(String::from("Amit"), String::from("Singh"));
    println!("{}", full_name);

    helpers::condition_helpers::test_if();

    helpers::condition_helpers::test_while();

    helpers::condition_helpers::test_loop();

    helpers::condition_helpers::test_for();
}

#[allow(dead_code)]
pub fn test_async() {
    match tokio::runtime::Runtime::new() {
        Ok(rt) => {
            rt.block_on(async1::get_two_sites_async());
        }
        Err(err) => println!("Failed to create tokio runtime, Error: {:?}", err),
    }
}
