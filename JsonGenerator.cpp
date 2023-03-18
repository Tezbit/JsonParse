//
// Created by ashoreDove on 2023/3/17.
//

#include "JsonGenerator.h"

using namespace json;

std::string JsonGenerator::generate(const Node &node) {
    return std::visit(
            [](auto &&arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Null>) {
                    return "null";
                } else if constexpr (std::is_same_v<T, Bool>) {
                    return arg ? "true" : "false";
                } else if constexpr (std::is_same_v<T, Int>) {
                    return std::to_string(arg);
                } else if constexpr (std::is_same_v<T, Float>) {
                    return std::to_string(arg);
                } else if constexpr (std::is_same_v<T, String>) {
                    return generate_string(arg);
                } else if constexpr (std::is_same_v<T, Array>) {
                    return generate_array(arg);
                } else if constexpr (std::is_same_v<T, Object>) {
                    return generate_object(arg);
                }
            },
            node.value);
}

std::string JsonGenerator::generate_object(const Object &object) {
    std::string json_str = "{";
    for (const auto &[key, node]: object) {
        json_str += generate_string(key);
        json_str += ':';
        json_str += generate(node);
        json_str += ',';
    }
    if (!object.empty()) json_str.pop_back();
    json_str += '}';
    return json_str;
}

std::string JsonGenerator::generate_array(const Array &array) {
    std::string json_str = "[";
    for (const auto &node: array) {
        json_str += generate(node);
        json_str += ',';
    }
    if (!array.empty()) json_str.pop_back();
    json_str += ']';
    return json_str;
}

std::string JsonGenerator::generate_string(const String &str) {
    std::string json_str = "\"";
    json_str += str;
    json_str += '"';
    return json_str;
}
