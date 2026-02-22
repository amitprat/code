```
Python client
   |
   |  PUT /upload
   |  GET /download
   v
C++ HTTP Server
   |
   |-- bucket_<id>.dat   (raw bytes)
   |-- bucket_<id>.idx   (offset + size)

```

Backend: C++ HTTP Server

We’ll use cpp-httplib (single-header, very common).

1️⃣ Download dependency
```
wget https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h
```

4️⃣ Build & Run
```
g++ -std=c++17 server.cpp -o image_server
./image_server
```

- Server running at:
    http://localhost:8080
