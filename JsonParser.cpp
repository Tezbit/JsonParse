//
// Created by ashoreDove on 2023/3/16.
//

#include "JsonParser.h"

using namespace json;

std::optional<Node> JsonParser::parse() {
    //跳过空白字符
    parse_whitespace();
    auto value = parse_value();
    if (!value) {
        return {};
    }
    return Node{*value};
}

void JsonParser::parse_whitespace() {
    while (pos < json_str.size() && std::isspace(json_str[pos])) {
        ++pos;
    }
}

std::optional<Value> JsonParser::parse_value() {
    parse_whitespace();
    switch (json_str[pos]) {
        case 'n':
            return parse_null();
        case 't':
            return parse_true();
        case 'f':
            return parse_false();
        case '"':
            return parse_string();
        case '[':
            return parse_array();
        case '{':
            return parse_object();
        default:
            return parse_number();
    }
}

std::optional<Value> JsonParser::parse_null() {
    if (json_str.substr(pos, 4) == "null") {
        pos += 4;
        return Null{};
    }
    return {};
}

std::optional<Value> JsonParser::parse_true() {
    if (json_str.substr(pos, 4) == "true") {
        pos += 4;
        return true;
    }
    return {};
}

std::optional<Value> JsonParser::parse_false() {
    if (json_str.substr(pos, 5) == "false") {
        pos += 5;
        return false;
    }
    return {};
}

std::optional<Value> JsonParser::parse_string() {
    pos++;
    size_t endpos = pos;
    while (pos < json_str.size() && json_str[endpos] != '"') {
        endpos++;
    }
    std::string str = std::string{json_str.substr(pos, endpos - pos)};
    pos = endpos + 1;
    return str;
}

std::optional<Value> JsonParser::parse_array() {
    pos++;// [
    Array arr;
    while (pos < json_str.size() && json_str[pos] != ']') {
        auto value = parse_value();
        arr.emplace_back(value.value());
        parse_whitespace();
        if (pos < json_str.size() && json_str[pos] == ',') {
            pos++;// ,
        }
        parse_whitespace();
    }
    pos++;// ]
    return arr;
}

std::optional<Value> JsonParser::parse_object() {
    pos++;// {
    Object obj;
    while (pos < json_str.size() && json_str[pos] != '}') {
        auto key = parse_value();
        parse_whitespace();
        //该variant中是否有string类型
        if (!std::holds_alternative<String>(key.value())) {
            return {};
        }
        if (pos < json_str.size() && json_str[pos] == ':') {
            pos++;// ,
        }
        parse_whitespace();
        auto val = parse_value();
        obj[std::get<String>(key.value())] = val.value();
        parse_whitespace();
        if (pos < json_str.size() && json_str[pos] == ',') {
            pos++;// ,
        }
        parse_whitespace();
    }
    pos++;// }
    return obj;
}

std::optional<Value> JsonParser::parse_number() {
    size_t endpos = pos;
    while (endpos < json_str.size() && (
            std::isdigit(json_str[endpos]) ||
            json_str[endpos] == 'e' ||
            json_str[endpos] == '.')) {
        endpos++;
    }
    std::string number = std::string{json_str.substr(pos, endpos - pos)};
    pos = endpos;
    static auto is_Float = [](std::string &number) {
        return number.find('.') != std::string::npos ||
               number.find('e') != std::string::npos;
    };
    if (is_Float(number)) {
        try {
            Float ret = std::stod(number);
            return ret;
        }
        catch (...) {
            return {};
        }
    } else {
        try {
            Int ret = std::stoi(number);
            return ret;
        }
        catch (...) {
            return {};
        }
    }
}
