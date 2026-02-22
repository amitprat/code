#include "../header.h"

class EncodeDecode {
   public:
    static void test() {
        vector<vector<string>> inputs = {
            {},
            {""},
            {"", ""},
            {"Hello"},
            {"Hello", ""},
            {"", "World", "!"},
            {"Hello", "World"}};
        EncodeDecode obj;

        for (auto& input : inputs) {
            cout << "-----------------------" << endl;
            cout << "Original: " << input << endl;
            auto encoded = obj.trieEncode(input);
            cout << "Encoded: " << encoded << endl;

            auto decoded = obj.trieDecode(encoded);
            cout << "Decoded: " << decoded << endl;

            assert(obj.decodeNormal1(obj.encodeNormal1(input)) == input);
            assert(obj.decodeNormal2(obj.encodeNormal2(input)) == input);
            assert(obj.prefixDecode(obj.prefixEncode(input)) == input);
            assert(obj.dictionaryDecode(obj.dictionaryEncode(input)) == input);
            // assert(obj.trieDecode(obj.trieEncode(input)) == input);
            cout << "-----------------------" << endl;
        }
    }

   public:
    string encodeNormal1(vector<string>& strs) {
        stringstream ss;
        for (auto& str : strs) {
            ss << str.size();
            ss << "#";
            ss << str;
        }

        return ss.str();
    }

    vector<string> decodeNormal1(string s) {
        vector<string> result;
        string cur;
        for (int i = 0; i < s.length(); i++) {
            auto ch = s[i];
            if (ch == '#') {
                int l = stoi(cur);
                cur.clear();
                for (int j = i + 1; j < i + l + 1; j++) cur += s[j];
                result.push_back(cur);
                cur.clear();
                i += l;
            } else {
                cur += ch;
            }
        }

        return result;
    }

   public:
    static void writeU32(string& out, uint32_t v) {
        out.append(reinterpret_cast<char*>(&v), sizeof(v));
    }

    static uint32_t readU32(const string& in, size_t& pos) {
        uint32_t v;
        memcpy(&v, in.data() + pos, sizeof(v));
        pos += sizeof(v);
        return v;
    }

    string encodeNormal2(vector<string> input) {
        string out;
        out.push_back('L');
        writeU32(out, input.size());

        for (auto& s : input) {
            writeU32(out, s.size());
            out.append(s);
        }
        return out;
    }

    vector<string> decodeNormal2(string encoded) {
        size_t pos = 0;
        if (encoded[pos++] != 'L') throw runtime_error("bad format");

        uint32_t n = readU32(encoded, pos);
        vector<string> out;
        out.reserve(n);

        for (uint32_t i = 0; i < n; i++) {
            uint32_t len = readU32(encoded, pos);
            out.emplace_back(encoded.substr(pos, len));
            pos += len;
        }
        return out;
    }

   public:
    string prefixEncode(vector<string> input) {
        if (input.empty()) return "F";

        sort(input.begin(), input.end());

        string out;

        // write the total size
        out.push_back('F');
        writeU32(out, input.size());

        // write first string
        writeU32(out, input[0].size());
        out.append(input[0]);

        for (size_t i = 1; i < input.size(); i++) {
            // skip prefix
            size_t j = 0;
            while (j < input[i].size() && j < input[i - 1].size() && input[i][j] == input[i - 1][j]) j++;

            // write prefix length
            writeU32(out, j);

            // write remaining length
            writeU32(out, input[i].size() - j);

            // write remaining string
            out.append(input[i].substr(j));
        }
        return out;
    }

    vector<string> prefixDecode(string encoded) {
        size_t pos = 0;
        if (encoded[pos++] != 'F') throw runtime_error("bad format");

        // read total length
        uint32_t n = readU32(encoded, pos);
        vector<string> out;
        if (n == 0) return out;

        // read first string
        uint32_t len = readU32(encoded, pos);
        out.emplace_back(encoded.substr(pos, len));
        pos += len;

        for (uint32_t i = 1; i < n; i++) {
            // read common prefix
            uint32_t prefix = readU32(encoded, pos);

            // read suffix length and string. append suffix.
            uint32_t suffixLen = readU32(encoded, pos);
            string s = out.back().substr(0, prefix);
            s.append(encoded.substr(pos, suffixLen));

            pos += suffixLen;
            out.emplace_back(std::move(s));
        }

        return out;
    }

   public:
    string dictionaryEncode(vector<string> input) {
        unordered_map<string, uint32_t> map;
        vector<string> dict;
        vector<uint32_t> ids;

        for (auto& s : input) {
            auto it = map.find(s);
            if (it == map.end()) {
                uint32_t id = dict.size();
                map[s] = id;
                dict.push_back(s);
                ids.push_back(id);
            } else {
                ids.push_back(it->second);
            }
        }

        string out;
        out.push_back('D');

        writeU32(out, dict.size());
        for (auto& s : dict) {
            writeU32(out, s.size());
            out.append(s);
        }

        writeU32(out, ids.size());
        for (auto id : ids)
            writeU32(out, id);

        return out;
    }

    vector<string> dictionaryDecode(string encoded) {
        size_t pos = 0;
        if (encoded[pos++] != 'D') throw runtime_error("bad format");

        uint32_t dictSize = readU32(encoded, pos);
        vector<string> dict(dictSize);

        for (uint32_t i = 0; i < dictSize; i++) {
            uint32_t len = readU32(encoded, pos);
            dict[i] = encoded.substr(pos, len);
            pos += len;
        }

        uint32_t n = readU32(encoded, pos);
        vector<string> out;
        out.reserve(n);

        for (uint32_t i = 0; i < n; i++) {
            uint32_t id = readU32(encoded, pos);
            out.push_back(dict[id]);
        }
        return out;
    }

   public:
    struct Node {
        bool terminal = false;
        map<char, int> next;
    };

    string trieEncode(vector<string> input) {
        vector<Node> nodes(1);  // root

        for (auto& s : input) {
            int cur = 0;
            for (char c : s) {
                if (!nodes[cur].next.count(c)) {
                    nodes[cur].next[c] = nodes.size();
                    nodes.push_back(Node());
                }
                cur = nodes[cur].next[c];
            }
            nodes[cur].terminal = true;
        }

        string out;
        out.push_back('T');
        writeU32(out, nodes.size());

        for (auto& n : nodes) {
            out.push_back(n.terminal ? 1 : 0);
            writeU32(out, n.next.size());
            for (auto& [c, idx] : n.next) {
                out.push_back(c);
                writeU32(out, idx);
            }
        }
        return out;
    }

    vector<string> trieDecode(string encoded) {
        size_t pos = 0;
        if (encoded[pos++] != 'T') throw runtime_error("bad format");

        uint32_t n = readU32(encoded, pos);
        vector<bool> terminal(n);
        vector<vector<pair<char, int>>> next(n);

        for (uint32_t i = 0; i < n; i++) {
            terminal[i] = encoded[pos++];
            uint32_t k = readU32(encoded, pos);
            for (uint32_t j = 0; j < k; j++) {
                char c = encoded[pos++];
                uint32_t idx = readU32(encoded, pos);
                next[i].push_back({c, idx});
            }
        }

        vector<string> out;
        function<void(int, string&)> dfs = [&](int u, string& cur) {
            if (terminal[u]) out.push_back(cur);
            for (auto& [c, v] : next[u]) {
                cur.push_back(c);
                dfs(v, cur);
                cur.pop_back();
            }
        };

        string cur;
        dfs(0, cur);
        return out;
    }
};