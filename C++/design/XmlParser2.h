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

};
class XmlParser {
private:
    Element* root = nullptr;
    StringParser parser;
public:
    bool isValidXml() {
        return true;
    }
    void parse(string xmlString) {
        parser.init(xmlString);
        root = parseInternal(parser);
    }

private:
    Element* parseInternal(StringParser parser) {
        Element* node = nullptr;
        while (parser.hasNext()) {
            node = new Element();
            if (parser.isEndTag()) return node;
            node->tagName = parser.getTagName();
            node->attributes = parser.getAttributes();
            if (!parser.getValue().empty()) node->value = parser.getValue();
            else {
                auto child = parseInternal(parser);
                while (child != nullptr) {
                    node->children.push_back(child);
                    child = parseInternal(parser);
                }
            }
        }
        return node;
    }
};

class XmlParserTest {

};