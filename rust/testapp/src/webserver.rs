use hyper::service::{make_service_fn, service_fn};
use hyper::{Body, Request, Response, Server};
use std::convert::Infallible;
use std::fs;
use tokio::runtime::Runtime;

pub fn start_web_server_sync() {
    // Create a new tokio runtime
    let rt = Runtime::new().unwrap();

    // Block on the async function completion
    rt.block_on(async {
        start_web_server().await;
    });

    // Continue with other main code
    println!("Main function continues after async function completes.");
}
async fn start_web_server() {
    // Create a service to handle incoming connections
    let make_svc =
        make_service_fn(|_conn| async { Ok::<_, Infallible>(service_fn(serve_static_files)) });

    // Configure the server
    let addr = ([127, 0, 0, 1], 3000).into();
    let server = Server::bind(&addr).serve(make_svc);

    println!("Server running on http://{}", addr);

    // Run the server
    if let Err(e) = server.await {
        eprintln!("server error: {}", e);
    }
}

async fn serve_static_files(_: Request<Body>) -> Result<Response<Body>, Infallible> {
    // Load the static file into a byte vector
    let contents = match fs::read("C:\\code\\rust\\testapp\\src\\index.html") {
        Ok(c) => c,
        Err(_) => {
            return Ok(Response::builder()
                .status(404)
                .body(Body::from("File not found"))
                .unwrap())
        }
    };

    Ok(Response::new(Body::from(contents)))
}
