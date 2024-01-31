use futures::executor::block_on;

mod webserver2;

fn main() {
    block_on(crate::webserver2::test_webserver());
}
