use reqwest;

pub async fn get_two_sites_async() {
    let future_one = download_async("https://google.com");
    let future_two = download_async("https://google.com");

    let _ = tokio::try_join!(future_one, future_two).map_err(|err| err.to_string());
}

async fn download_async(url: &str) -> Result<(), reqwest::Error> {
    let response = reqwest::get(url).await?;

    if response.status().is_success() {
        let body = response.text().await?;
        println!("{}", body);
    } else {
        println!(
            "Failed to fetch page with status code {}",
            response.status()
        );
    }

    return Ok(());
}
