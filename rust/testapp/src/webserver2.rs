use async_std::net::TcpListener;
use async_std::net::TcpStream;
use async_std::prelude::*;
use async_std::task;
use futures::stream::StreamExt;
use std::fs;
use std::time::Duration;

//https://rust-lang.github.io/async-book/09_example/02_handling_connections_concurrently.html

pub async fn test_webserver() {
    let listener = TcpListener::bind("127.0.0.1:9000").await.unwrap();
    listener
        .incoming()
        .for_each_concurrent(None, |tcpStream| async move {
            let tcpStream = tcpStream.unwrap();
            handle_connection(tcpStream).await;
        })
        .await;
}

async fn handle_connection(mut stream: TcpStream) {
    let mut request_buffer = [0; 1024];
    stream.read(&mut request_buffer).await.unwrap();

    let get = b"GET / HTTP/1.1\r\n";
    let sleep = b"GET /sleep HTTP/1.1\r\n";

    let (status_line, filename) = if request_buffer.starts_with(get) {
        (
            "HTTP/1.1 200 OK\r\n\r\n",
            "C:\\code\\rust\\testapp\\src\\index.html",
        )
    } else if request_buffer.starts_with(sleep) {
        task::sleep(Duration::from_secs(60)).await;
        (
            "HTTP/1.1 200 OK\r\n\r\n",
            "C:\\code\\rust\\testapp\\src\\sleep.html",
        )
    } else {
        (
            "HTTP/1.1 404 NOT FOUND\r\n\r\n",
            "C:\\code\\rust\\testapp\\src\\404.html",
        )
    };

    let contents = fs::read_to_string(filename).unwrap();
    let response = format!("{status_line}{contents}");

    stream.write(response.as_bytes()).await.unwrap();
    stream.flush().await.unwrap();
}
