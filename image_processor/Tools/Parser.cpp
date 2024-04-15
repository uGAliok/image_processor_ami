#include "Parser.h"

static constexpr std::string_view HELP =
    "Usage:\n\n"
    "   ./image_processor {path to input file} {path to output file}\n"
    "   [-{filter name 1} [filter parameter 1] [filter parameter 2] ...]\n"
    "   [-{filter name 2} [filter parameter 1] [filter parameter 2] ...]\n"
    "   ...\n";

Parser::Parser(int size, char** query) {
    ParseQuery(size, query);
}

Parser::~Parser() {
    for (size_t i = 0; i < parameters_.size(); ++i) {
        delete parameters_[i].parameters;
    }
}

void Parser::ParseQuery(int size, char* query[]) {
    if (size == 1) {
        std::cout << HELP << std::endl;
        return;
    }
    if (size < 3) {
        throw std::runtime_error("ERROR: Not enough arguments");
    }
    input_path_ = std::string(query[1]);
    output_path_ = std::string(query[2]);
    for (size_t i = 3; i < size;) {
        std::string filter = query[i];
        if (filter == "-crop") {
            if (i + 2 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -crop");
            }
            if (!(std::stoi(query[i + 1]) >= 0 && std::stoi(query[i + 2]) >= 0)) {
                throw std::runtime_error("ERROR: Wrong argument for -crop");
            }
            size_t arg1 = std::stoi(query[i + 1]);
            size_t arg2 = std::stoi(query[i + 2]);
            if (arg1 == 0 || arg2 == 0) {
                arg1 = arg2 = 0;
            }
            parameters_.push_back(FilterParameters(FilterName::CROP, new CropParameters(arg1, arg2)));
            i += 3;
        } else if (filter == "-gs") {
            parameters_.push_back(FilterParameters(FilterName::GREYSCALE, new GrayscaleParameters()));
            ++i;
        } else if (filter == "-neg") {
            parameters_.push_back(FilterParameters(FilterName::NEGATIVE, new NegativeParameters()));
            ++i;
        } else if (filter == "-sharp") {
            parameters_.push_back(FilterParameters(FilterName::SHARPENING, new SharpeningParameters()));
            ++i;
        } else if (filter == "-edge") {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -edge");
            }
            if (std::stod(query[i + 1]) < 0) {
                throw std::runtime_error("ERROR: Wrong argument for -edge");
            }
            double arg1 = std::stod(query[i + 1]);
            parameters_.push_back(FilterParameters(FilterName::EDGEDETECTION, new EdgeDetectionParameters(arg1)));
            i += 2;
        } else if (filter == "-blur") {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -blur");
            }
            if (std::stod(query[i + 1]) <= 0) {
                throw std::runtime_error("ERROR: Wrong argument for -blur");
            }
            double arg1 = std::stod(query[i + 1]);
            parameters_.push_back(FilterParameters(FilterName::GAUSSIANBLUR, new BlurParameters(arg1)));
            i += 2;
        } else if (filter == "-fisheye") {
            if (i + 1 >= size) {
                throw std::runtime_error("ERROR: Not enough arguments for -fisheye");
            }
            if (std::stod(query[i + 1]) < 0) {
                throw std::runtime_error("ERROR: Wrong argument for -fisheye");
            }
            double arg1 = std::stod(query[i + 1]);
            parameters_.push_back(FilterParameters(FilterName::FISHEYE, new FishEyeParameters(arg1)));
            i += 2;
        } else {
            throw std::logic_error("ERROR: Wrong filter name");
        }
    }
}

std::string Parser::GetInputPath() {
    return input_path_;
}

std::string Parser::GetOutputPath() {
    return output_path_;
}

std::vector<FilterParameters> Parser::GetParameters() {
    return parameters_;
}
