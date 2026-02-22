# upload.py
import requests

with open("im1.jpg", "rb") as f:
    r = requests.post(
        "http://localhost:8080/upload",
        params={"bucket": "bucket1", "image": "image1"},
        data=f.read()
    )

print(r.text)
