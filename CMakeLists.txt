cmake_minimum_required(VERSION 3.16)
project(JsonParse)

set(CMAKE_CXX_STANDARD 17)
link_libraries(stdc++fs)
add_executable(JsonParse main.cpp universal.h universal.h JsonParser.cpp JsonParser.h JsonParser.h JsonGenerator.cpp JsonGenerator.h JsonGenerator.h tiny_json.h tiny_json.h)
