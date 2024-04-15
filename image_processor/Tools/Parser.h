#pragma once
#include "../Filters/Filters.h"
#include <string_view>

class Parser {
public:
    Parser() = default;
    Parser(int size, char** query);
    ~Parser();

    std::string GetInputPath();
    std::string GetOutputPath();
    std::vector<FilterParameters> GetParameters();

    void ParseQuery(int size, char* query[]);

private:
    std::string input_path_;
    std::string output_path_;
    std::vector<FilterParameters> parameters_;
};
