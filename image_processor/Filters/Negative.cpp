#include "Filters.h"

void Negative::Process(Image& image) {
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            uint8_t r = std::max(MIN_VALUE, std::min(MAX_VALUE, image.GetRgb(i, j).R()));
            uint8_t g = std::max(MIN_VALUE, std::min(MAX_VALUE, image.GetRgb(i, j).G()));
            uint8_t b = std::max(MIN_VALUE, std::min(MAX_VALUE, image.GetRgb(i, j).B()));
            RGB pixel(MAX_VALUE - r, MAX_VALUE - g, MAX_VALUE - b);
            image.ChangePixel(pixel, i, j);
        }
    }
}
