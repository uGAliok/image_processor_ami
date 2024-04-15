#include "Filters.h"
#include <cmath>

static constexpr double EPS = 0.0000000001;

FishEyeParameters::FishEyeParameters(double arg1) : sigma(arg1) {
}

FishEye::FishEye(FishEyeParameters*& parameter) : sigma_(parameter->sigma) {
}

void FishEye::Process(Image& image) {
    const double center_x = static_cast<double>(static_cast<double>(image.Width()) / 2);
    const double center_y = static_cast<double>(static_cast<double>(image.Height()) / 2);
    const double max_distance = std::min(center_x, center_y);
    Image new_image(image);
    for (size_t y = 0; y < image.Height(); ++y) {
        for (size_t x = 0; x < image.Width(); ++x) {
            const double offset_x = static_cast<double>(x) - center_x;
            const double offset_y = static_cast<double>(y) - center_y;
            const double distance = hypot(offset_x, offset_y);
            if (max_distance - distance > EPS) {
                const double normalized_distance = distance / max_distance;
                double delta = 1. - pow(1. - normalized_distance, sigma_);
                int32_t x_to = static_cast<int32_t>(center_x + offset_x * delta);
                int32_t y_to = static_cast<int32_t>(center_y + offset_y * delta);
                if (x_to >= 0 && y_to >= 0 && x_to < image.Width() && y_to < image.Height()) {
                    new_image.ChangePixel(image.GetRgb(static_cast<size_t>(y_to), static_cast<size_t>(x_to)), y, x);
                }
            }
        }
    }
    image = new_image;
}
