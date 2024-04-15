#include "Filters.h"

CropParameters::CropParameters(size_t arg1, size_t arg2) : new_width(arg1), new_height(arg2) {
}

Crop::Crop(CropParameters*& parameters) : new_width_(parameters->new_width), new_height_(parameters->new_height) {
}

void Crop::Process(Image& image) {
    size_t new_width = std::max(static_cast<size_t>(0), std::min(static_cast<size_t>(image.Width()), new_width_));
    size_t new_height = std::max(static_cast<size_t>(0), std::min(static_cast<size_t>(image.Height()), new_height_));
    std::vector<std::vector<RGB>> result(new_height, std::vector<RGB>(new_width));
    for (size_t i = 0; i < new_height; ++i) {
        for (size_t j = 0; j < new_width; ++j) {
            result[i][j] = image.GetRgb(i, j);
        }
    }
    image.ChangePixels(result);
}
