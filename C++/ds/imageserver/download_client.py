# download.py
import requests

r = requests.get(
    "http://localhost:8080/download",
    params={"bucket": "bucket1", "image": "image1"}
)

with open("downloaded_img1.jpg", "wb") as f:
    f.write(r.content)
