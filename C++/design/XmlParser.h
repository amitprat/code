#pragma once
#include "../header.h"

class Attribute {
public:
    string tagName;
    string value;

    Attribute(string tagName, string value) : tagName(tagName), value(value) {}

    string to_string() {
        return "(" + tagName + ":" + value + ")";
    }
};
class Element {
public:
    string tagName;
    string value;
    list<Attribute*> attributes;
    list<Element*> children;

    Element(string tagName, vector<pair<string, string>> attr, string val) {
        this->tagName = tagName;
        for (auto& p : attr) {
            attributes.push_back(new Attribute(p.first, p.second));
        }
        this->value = value;
    }

    string to_string() {
        stringstream ss;
        ss << "{";
        ss << "Tag:" << tagName << "; ";
        if (!value.empty()) ss << "Value:" << value << "; ";
        if (!attributes.empty()) {
            ss << "Attributes:{";
            for (auto& a : attributes)
                ss << a->to_string();
            ss << "}";
        }
        ss << "}";
        return ss.str();
    }
};
class StringParser {
    string str;
    string cur;
    int start = 0;
public:
    class Line {
    public:
        string tagName;
        bool isEnd = false;
        string value;
        vector<pair<string, string>> attrs;
    };
    StringParser(string str) {
        this->str = str;
    }
    bool hasNext() {
        cur.clear();
        auto pos = str.find('\n', start);
        if (pos == string::npos) return false;
        cur = str.substr(start, pos);
        if (cur.empty()) return false;
        start = pos + 1;
        return true;
    }
    Line next() {
        Line line(parse(cur));
        return line;
    }

private:
    Line parse(string cur) {
        Line line;
        if (cur.empty()) return line;
        vector<string> parts = split(cur, " ");
        if (parts.empty()) throw exception("Invalid XML");
        line.tagName = getStartTag(parts[0]);
        for (int i = 1; i < parts.size(); i++) {
            line.attrs.push_back(splitPart(parts[i], "="));
        }
        if (!line.attrs.empty()) {
            string lastVal = line.attrs.back().second;
            auto npos = lastVal.find('>');
            if (npos != string::npos) {
                line.attrs[line.attrs.size() - 1].second = lastVal.substr(0, npos);
                lastVal = lastVal.substr(npos + 1);
                npos = lastVal.find("</");
                if (npos != string::npos) {
                    line.value = lastVal.substr(0, npos);
                }
            }
        }
        return line;
    }

    vector<string> split(string cur, string delim) {
        vector<string> result;
        int start = 0;
        int pos = 0;
        while ((pos = cur.find(delim, start)) != string::npos) {
            result.push_back(cur.substr(start, pos - start));
            start = pos + 1;
        }
        result.push_back(cur.substr(start));
        return result;
    }

    pair<string, string> splitPart(string cur, string delim) {
        auto pos = cur.find(delim);
        if (pos == string::npos) throw exception("Invalid XML");
        return { cur.substr(0, pos), cur.substr(pos + 1) };
    }

    string getStartTag(string cur) {
        if (cur.empty() || cur[0] != '<') throw exception("Invalid xml");
        return cur.substr(1);
    }

    string getEndTag(string cur, bool& end) {
        if (cur.empty()) throw exception("Invalid xml");
        int l = cur.length();
        if (cur.substr(l - 2) == "/>") {
            end = true; cur = cur.substr(l - 2);
        }
        return cur;
    }
};
class XmlParser {
private:
    Element* root = nullptr;
public:
    void parse(const string& str) {
        StringParser parser(str);
        root = parseInternal(parser);
    }

    string to_string() {
        string result;
        to_string(root, result, 0);
        return result;
    }

    const Element* getElement() {
        return root;
    }

private:
    Element* parseInternal(StringParser& parser) {
        Element* node = nullptr;
        if (parser.hasNext()) {
            StringParser::Line cur = parser.next();
            if (cur.isEnd) return nullptr;
            if (node == nullptr) node = new Element(cur.tagName, cur.attrs, cur.value);
            if (!cur.isEnd) {
                auto child = parseInternal(parser);
                while (child != nullptr) {
                    node->children.push_back(child);
                    child = parseInternal(parser);
                }
            }
        }
        return node;
    }

    void to_string(Element* cur, string& result, int indent) {
        if (cur) {
            std::string fill(indent, ' ');
            result += fill + cur->to_string();
            result += "\n";
            for (auto& child : cur->children) {
                to_string(child, result, indent + 4);
            }
            result += "\n";
        }
    }
};

class XmlEncoder {
public:
    void encode(const Element* element) {

    }

    string to_string() {
        return "";
    }
};

class XmlParserTest {
public:
    static void test() {
        XmlParser parser;
        XmlEncoder encoder;
        string str = "<family lastName=McDowell state=CA>\n"
            "<person firstName=Gayle>\n"
            "<age>12</age>"
            "</person>\n"
            "</family>";
        parser.parse(str);
        cout << "XML Value:" << endl;
        cout << parser.to_string() << endl;
        //encoder.encode(parser.getElement());
        //cout << "Encoding: " << endl;
        //cout << encoder.to_string() << endl;
    }
};