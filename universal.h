//
// Created by ashoreDove on 2023/3/15.
//

#ifndef JSONPARSE_UNIVERSAL_H
#define JSONPARSE_UNIVERSAL_H

#include <utility>
#include <variant>
#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace json {
    struct Node;
    using Null = std::monostate;
    using Bool = bool;
    using Int = int64_t;
    using Float = double;
    using String = std::string;
    using Array = std::vector<Node>;
    using Object = std::map<std::string, Node>;
    using Value = std::variant<Null, Bool, Int, Float, String, Array, Object>;

    struct Node {
        Value value;

        //这里应该允许隐式转换
        Node(Value v) : value(std::move(v)) {}

        Node() : value(Null{}) {}

//        auto &operator[](const std::string &key) {
//            if (auto object = std::get_if<Object>(&value)) {
//                return (*object)[key];
//            }
//            throw std::runtime_error("not an object");
//        }
//
//        auto operator[](size_t index) {
//            if (auto array = std::get_if<Array>(&value)) {
//                return array->at(index);
//            }
//            throw std::runtime_error("not an array");
//        }
//
//        void push(const Node &rhs) {
//            if (auto array = std::get_if<Array>(&value)) {
//                array->push_back(rhs);
//            }
//        }

    };
}
#endif //JSONPARSE_UNIVERSAL_H
