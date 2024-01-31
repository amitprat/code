#pragma once
#include <random>

#include "../header.h"

using Number = unsigned long long;
static Number highest = 0;
class TinyUrl {
    class Database {
       private:
        string orginalUrl;
        string encodedUrl;

       public:
        struct Node {
            int createdAt;
            short duration;

            string to_string() {
                stringstream ss;
                ss << "{";
                ss << "created_at:";
                ss << createdAt << ", ";
                ss << "duration:";
                ss << duration;
                ss << "}";

                return ss.str();
            }
        };

       private:
        using Key = string;
        using Value = pair<string, shared_ptr<Node>>;
        unordered_map<Key, Value> originalUrlToEncodedUrlMap;
        unordered_map<Key, Value> encodedUrlToOriginalUrlMap;

        typedef std::shared_mutex Lock;
        typedef std::unique_lock<Lock> WriteLock;  // C++ 11
        typedef std::shared_lock<Lock> ReadLock;   // C++ 14
        Lock lock;

       public:
        bool insert(Key originalUrl, string encodedUrl, const Node& properties) {
            WriteLock writeLock(lock);
            shared_ptr<Node> node = make_shared<Node>(properties);
            originalUrlToEncodedUrlMap.insert({originalUrl, {encodedUrl, node}});
            encodedUrlToOriginalUrlMap.insert({encodedUrl, {originalUrl, node}});

            return true;
        }

        bool get_by_url(Key originalUrl, string& encodedUrl, Node& properties) {
            ReadLock writeLock(lock);
            if (originalUrlToEncodedUrlMap.find(originalUrl) == originalUrlToEncodedUrlMap.end()) {
                return false;
            }

            encodedUrl = originalUrlToEncodedUrlMap[originalUrl].first;
            properties = *originalUrlToEncodedUrlMap[originalUrl].second;

            return true;
        }

        bool get_by_key(Key encodedUrl, string& originalUrl, Node& properties) {
            ReadLock readLock(lock);
            if (encodedUrlToOriginalUrlMap.find(encodedUrl) == encodedUrlToOriginalUrlMap.end()) {
                return false;
            }

            originalUrl = encodedUrlToOriginalUrlMap[encodedUrl].first;
            properties = *encodedUrlToOriginalUrlMap[encodedUrl].second;

            return true;
        }
    };
    class DatabaseTester {
       public:
        static void test() {
            Database db;
            db.insert("google.com", "id1", Database::Node{1, 30});
            db.insert("yahoo.com", "id2", Database::Node{2, 30});

            {
                string originalUrl = "google.com";
                string encodedUrl;
                Database::Node properties;
                bool found = db.get_by_url(originalUrl, encodedUrl, properties);
                if (found) {
                    cout << format("Url=[{}] found in database, id=[{}], Properties=[{}]", originalUrl, encodedUrl, properties.to_string()) << endl;
                }

                assert(false == db.get_by_url("msn.com", encodedUrl, properties));
            }

            {
                string originalUrl;
                string encodedUrl = "id1";
                Database::Node properties;
                bool found = db.get_by_key(encodedUrl, originalUrl, properties);
                if (found) {
                    cout << format("Id=[{}] found in database, url=[{}], Properties=[{}]", encodedUrl, originalUrl, properties.to_string()) << endl;
                }

                assert(false == db.get_by_key("id3", originalUrl, properties));
            }
        }
    };

    class Base62EncodedDecoder {
        inline static const string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

       public:
        static string base62Encode(Number number) {
            string base62;
            while (number) {
                base62 += chars[(number % 62)];
                number /= 62;
            }

            std::reverse(base62.begin(), base62.end());

            return base62.substr(0, 7);
        }

        static Number base62Decode(const string& encodedStr) {
            Number result = 0;
            for (auto ch : encodedStr) {
                int current = 0;
                if (ch >= '0' && ch <= '9')
                    current = ch - '0';
                else if (ch >= 'a' && ch <= 'z')
                    current = 10 + (ch - 'a');
                else if (ch >= 'A' && ch <= 'Z')
                    current = 36 + (ch - 'A');

                result = result * 62 + current;
            }

            return result;
        }
    };

    class Utils {
        std::random_device rd;
        std::mt19937_64 eng;
        std::uniform_int_distribution<unsigned long long> distr;

       public:
        Utils() {
            eng = std::mt19937_64(rd());
        }

        Number get_random_number() {
            return distr(eng);
        }

       public:
        static int get_last_set_bit_pos(Number num) {
            int msb = 0;
            while (num) {
                num /= 10;
                msb++;
            }

            return msb;
        }
    };

    class KeyGeneratorService {
        Utils utils;
        mutex m;

       public:
        vector<string> get_next_keys(int count) {
            Number start, end;
            {
                lock_guard lock(m);
                start = highest;
                end = highest + count - 1;
                highest += count;
            }

            vector<string> result;
            for (start; start <= end; start++) {
                Number next = get_next_number(start);
                result.push_back(Base62EncodedDecoder::base62Encode(next));
            }

            return result;
        }

       private:
        Number get_next_number(Number start) {
            Number random = utils.get_random_number();
            int bits_count = Utils::get_last_set_bit_pos(start);
            Number msb_number = ~((1 << bits_count) - 1);

            Number combined = (random & msb_number) | start;

            return combined;
        }
    };

   public:
    static void test() {
        TinyUrl tinyUrl;

        string user;
        srand(time(nullptr));

        auto start = tinyUrl.get_current_time();
        auto max = 100000;
        string prefix_url = "https://www.google.com/";
        for (Number num = 0; num < max; num++) {
            try {
                string generated_url = prefix_url + tinyUrl.gen_random(100);
                string encodedUrl = tinyUrl.encode(generated_url);
                string decodeUrl = tinyUrl.decode(encodedUrl);

                assert(generated_url == decodeUrl);
            } catch (exception e) {
                cout << e.what();
            }
        }
        auto end = tinyUrl.get_current_time();
        cout << format("Total duration in seconds to generated [{}] is [{}].", max, tinyUrl.elapsed_time_in_seconds(start, end)) << endl;

        // cout << "Encoded url: " << encodedUrl << endl;
        // cout << "Decoded url: " << tinyUrl.decode(encodedUrl) << endl;
    }

   private:
    inline static const string PREFIX = "https://tinyurl.com/";
    Database db;
    vector<string> keys;
    atomic<int> keys_size = 0;
    atomic<int> available_index = 0;

    atomic<bool> done = false;
    std::future<void> keys_renew_thread;

    typedef std::shared_mutex Lock;
    typedef std::unique_lock<Lock> WriteLock;  // C++ 11
    typedef std::shared_lock<Lock> ReadLock;   // C++ 14
    Lock lock;

    static const int SET_SIZE = 10000;
    KeyGeneratorService kgs;

    atomic<int> logical_time = 0;

   public:
    TinyUrl() {
        {
            vector<string> new_keys = kgs.get_next_keys(SET_SIZE);

            WriteLock writeLock(lock);
            keys.insert(keys.end(), new_keys.begin(), new_keys.end());
            keys_size = keys.size();
        }

        keys_renew_thread = std::async(std::launch::async, [this]() {
            while (!done) {
                if (available_index >= keys_size / 2) {
                    vector<string> new_keys = kgs.get_next_keys(SET_SIZE);

                    {
                        WriteLock writeLock(lock);
                        keys.insert(keys.end(), new_keys.begin(), new_keys.end());
                        keys_size = keys.size();
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }

    ~TinyUrl() {
        done = true;
        keys_renew_thread.get();
    }

    string encode(const string& url) {
        string original_url;
        Database::Node properties;
        if (db.get_by_url(url, original_url, properties)) throw runtime_error("Url already encoded");

        string key;
        {
            auto index = 0;
            {
                WriteLock writeLock(lock);
                index = available_index.load();
                available_index++;

                if (index >= keys_size) throw runtime_error("Ran out of keys.");
                key = keys[index];
            }
        }

        auto time = logical_time.load();
        logical_time++;

        db.insert(url, key, {time, 20});

        return key;
    }

    string decode(const string& id) {
        string originalUrl;
        Database::Node properties;
        if (!db.get_by_key(id, originalUrl, properties)) throw runtime_error("id not exists");

        return originalUrl;
    }

   private:
    std::string gen_random(const int len) {
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        std::string tmp_s;
        tmp_s.reserve(len);

        for (int i = 0; i < len; ++i) {
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return tmp_s;
    }

    chrono::system_clock::time_point get_current_time() {
        return std::chrono::system_clock::now();
    }

    std::chrono::seconds elapsed_time_in_seconds(
        chrono::system_clock::time_point startTime,
        chrono::system_clock::time_point endTime) {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

        return elapsed;
    }
};