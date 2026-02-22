// server.cpp
#include "httplib.h"
#include "bucket_storage.h"
#include <unordered_map>
#include <memory>

std::unordered_map<std::string, std::unique_ptr<BucketStorage>> buckets;

BucketStorage& get_bucket(const std::string& id) {
    if (!buckets[id]) {
        buckets[id] = std::make_unique<BucketStorage>(id);
    }
    return *buckets[id];
}

int main() {
    httplib::Server server;

    // Upload image
    server.Post("/upload", [](const httplib::Request& req, httplib::Response& res) {
        auto bucket = req.get_param_value("bucket");
        auto image  = req.get_param_value("image");

        auto& storage = get_bucket(bucket);
        std::vector<char> data(req.body.begin(), req.body.end());

        storage.put(image, data);
        res.set_content("OK\n", "text/plain");
    });

    // Download image
    server.Get("/download", [](const httplib::Request& req, httplib::Response& res) {
        auto bucket = req.get_param_value("bucket");
        auto image  = req.get_param_value("image");

        auto& storage = get_bucket(bucket);
        auto data = storage.get(image);

        res.set_content_provider(
            data.size(),
            "image/jpeg",
            [data](size_t offset, size_t length, httplib::DataSink& sink) {
                sink.write(data.data() + offset, length);
                return true;
            }
        );
    });

    server.listen("0.0.0.0", 8080);
}
