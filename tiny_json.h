//
// Created by ashoreDove on 2023/3/17.
//

#ifndef JSONPARSE_TINY_JSON_H
#define JSONPARSE_TINY_JSON_H

#include "JsonParser.h"
#include "JsonGenerator.h"
/*
 * 对外暴露接口
 */
namespace json {
    std::optional<Node> parser(std::string_view json_str) {
        JsonParser p{json_str};
        return p.parse();
    }

    std::ostream &operator<<(std::ostream &out, const Node &t) {
        out << JsonGenerator::generate(t);
        return out;
    }
}
#endif //JSONPARSE_TINY_JSON_H
