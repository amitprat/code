pub mod simple_closure {
    pub fn test_closures() {
        let print = || println!("Say hello from closure!");
        print();
    }
}
