#include "Filters.h"

static constexpr double R_COEFFICIENT = 0.299;  // NOLINT
static constexpr double G_COEFFICIENT = 0.587;  // NOLINT
static constexpr double B_COEFFICIENT = 0.114;  // NOLINT

void Grayscale::Process(Image& image) {
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            uint8_t current_r = image.GetRgb(i, j).R();
            uint8_t current_g = image.GetRgb(i, j).G();
            uint8_t current_b = image.GetRgb(i, j).B();
            uint8_t gs_pixel =
                static_cast<uint8_t>(R_COEFFICIENT * current_r + G_COEFFICIENT * current_g + B_COEFFICIENT * current_b);
            gs_pixel = std::max(MIN_VALUE, std::min(MAX_VALUE, gs_pixel));
            RGB pixel(gs_pixel, gs_pixel, gs_pixel);
            image.ChangePixel(pixel, i, j);
        }
    }
}
