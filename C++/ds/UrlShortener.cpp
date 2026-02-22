#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace std::chrono;

/* ================= Base62 Encoding ================= */
const string BASE62 = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

string encodeBase62(uint64_t num) {
    if (num == 0) return "0";
    string s;
    while (num > 0) {
        s = BASE62[num % 62] + s;
        num /= 62;
    }
    return s;
}

/* ================= Snowflake ID Generator ================= */
class Snowflake {
   private:
    uint64_t lastTimestamp;
    uint16_t machineId;
    uint16_t sequence;
    mutex mtx;

    static uint64_t currentMillis() {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    uint64_t waitNextMillis(uint64_t lastTs) {
        uint64_t ts = currentMillis();
        while (ts <= lastTs) {
            ts = currentMillis();
        }
        return ts;
    }

   public:
    Snowflake(uint16_t machineId_) : lastTimestamp(0), machineId(machineId_), sequence(0) {}

    uint64_t nextId() {
        lock_guard<mutex> lock(mtx);
        uint64_t ts = currentMillis();
        if (ts == lastTimestamp) {
            sequence++;
            if (sequence >= 4096) {  // 12-bit sequence max
                ts = waitNextMillis(lastTimestamp);
                sequence = 0;
            }
        } else {
            sequence = 0;
        }
        lastTimestamp = ts;

        // 41 bits timestamp | 10 bits machine id | 12 bits sequence
        uint64_t id = ((ts & 0x1FFFFFFFFFF) << 22) | ((machineId & 0x3FF) << 12) | (sequence & 0xFFF);
        return id;
    }
};

/* ================= URL Shortener ================= */

struct URLRecord {
    string originalUrl;
    uint64_t timestamp;
};

class URLShortener {
   private:
    unordered_map<string, URLRecord> shortToUrl;
    unordered_map<string, string> urlToShort;
    mutex db_mtx;

    Snowflake snowflakeGen;
    milliseconds retentionWindow;

   public:
    URLShortener(uint16_t machineId, int retentionSeconds)
        : snowflakeGen(machineId), retentionWindow(retentionSeconds * 1000) {}

    // Shorten URL
    string shorten(const string& url) {
        lock_guard<mutex> lock(db_mtx);

        // If already shortened, return existing
        if (urlToShort.count(url)) return urlToShort[url];

        uint64_t id = snowflakeGen.nextId();
        string shortUrl = encodeBase62(id);

        shortToUrl[shortUrl] = {url, currentMillis()};
        urlToShort[url] = shortUrl;

        cout << "[SHORTEN] " << url << " -> " << shortUrl << "\n";
        return shortUrl;
    }

    // Expand URL
    string fetch(const string& shortUrl) {
        lock_guard<mutex> lock(db_mtx);
        if (!shortToUrl.count(shortUrl)) return "NOT FOUND";

        URLRecord& rec = shortToUrl[shortUrl];
        auto now = currentMillis();

        if (now - rec.timestamp > retentionWindow.count()) {
            // Expired
            shortToUrl.erase(shortUrl);
            urlToShort.erase(rec.originalUrl);
            return "NOT FOUND (expired)";
        }

        return rec.originalUrl;
    }

    // Cleanup expired URLs
    void cleanup() {
        lock_guard<mutex> lock(db_mtx);
        auto now = currentMillis();
        vector<string> toErase;
        for (auto& [shortUrl, rec] : shortToUrl) {
            if (now - rec.timestamp > retentionWindow.count())
                toErase.push_back(shortUrl);
        }
        for (auto& shortUrl : toErase) {
            string orig = shortToUrl[shortUrl].originalUrl;
            shortToUrl.erase(shortUrl);
            urlToShort.erase(orig);
            cout << "[CLEANUP] Removed " << shortUrl << " -> " << orig << "\n";
        }
    }

    // Debug: print DB
    void printDB() {
        lock_guard<mutex> lock(db_mtx);
        cout << "--- DB State ---\n";
        for (auto& [s, rec] : shortToUrl) {
            cout << s << " -> " << rec.originalUrl << " | age(ms)=" << currentMillis() - rec.timestamp << "\n";
        }
        cout << "----------------\n";
    }

    static uint64_t currentMillis() {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
};

/* ================= Demo ================= */

int main() {
    URLShortener shortener(1, 5);  // retention window 5 seconds

    // Shorten URLs
    string s1 = shortener.shorten("https://www.google.com");
    string s2 = shortener.shorten("https://www.github.com");
    string s3 = shortener.shorten("https://www.openai.com");

    // Fetch immediately
    cout << "[FETCH] " << s1 << " -> " << shortener.fetch(s1) << "\n";
    cout << "[FETCH] " << s2 << " -> " << shortener.fetch(s2) << "\n";

    shortener.printDB();

    // Sleep for 6 seconds to expire URLs
    cout << "Sleeping 6 seconds to simulate expiration...\n";
    this_thread::sleep_for(seconds(6));

    // Fetch again
    cout << "[FETCH] " << s1 << " -> " << shortener.fetch(s1) << "\n";
    cout << "[FETCH] " << s3 << " -> " << shortener.fetch(s3) << "\n";

    // Cleanup expired
    shortener.cleanup();
    shortener.printDB();

    return 0;
}
