#include <iostream>
#include<string>
#include<fstream>
#include <sstream>
#include <experimental/filesystem>
#include "tiny_json.h"

using namespace json;
int main() {
//    std::cout<<std::experimental::filesystem::current_path();
    std::ifstream fin( "../test.json");
    std::stringstream ss;
    ss << fin.rdbuf();
    std::string s{ss.str()};
    auto x = parser(s).value();

    std::cout << x << std::endl;
}