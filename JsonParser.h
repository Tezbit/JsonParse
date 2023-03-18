//
// Created by ashoreDove on 2023/3/16.
//

#ifndef JSONPARSE_JSONPARSER_H
#define JSONPARSE_JSONPARSER_H

#include <string_view>
#include <optional>

#include "universal.h"
/*
 * 字符串转Json
 */
namespace json {
    class JsonParser {
    public:
        explicit JsonParser(std::string_view _json_str) : json_str(_json_str) {}

        std::optional<Node> parse();

    private:
        void parse_whitespace();

        std::optional<Value> parse_value();

        std::optional<Value> parse_null();

        std::optional<Value> parse_true();

        std::optional<Value> parse_false();

        std::optional<Value> parse_string();

        std::optional<Value> parse_array();

        std::optional<Value> parse_object();

        std::optional<Value> parse_number();

        std::string_view json_str;
        size_t pos = 0;
    };
}

#endif //JSONPARSE_JSONPARSER_H
