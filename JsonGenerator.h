//
// Created by ashoreDove on 2023/3/17.
//

#ifndef JSONPARSE_JSONGENERATOR_H
#define JSONPARSE_JSONGENERATOR_H

#include <string>

#include "universal.h"
/*
 * Json转可用输出
 */
namespace json {
    class JsonGenerator {
    public:
        static std::string generate(const Node &node);

    private:
        static std::string generate_object(const Object &object);

        static std::string generate_array(const Array &array);

        static std::string generate_string(const String &str);
    };

}

#endif //JSONPARSE_JSONGENERATOR_H
