#include "Filters.h"
#include <cmath>

BlurParameters::BlurParameters(double arg1) : sigma(arg1) {
}

Blur::Blur(BlurParameters*& parameter) : sigma_(parameter->sigma) {
}

double Blur::ConstCount(int32_t a_0, int32_t a) const {
    double delta_a = static_cast<double>(a_0) - static_cast<double>(a);
    double gauss_const = exp(-delta_a * delta_a / (2 * sigma_ * sigma_));
    gauss_const = gauss_const / sqrt(2 * M_PI * sigma_ * sigma_);
    return gauss_const;
}

void Blur::Process(Image& image) {
    std::vector<std::vector<RGB>> gauss_half(image.Height(), std::vector<RGB>(image.Width()));
    int32_t delta_sigma = static_cast<int32_t>(ceil(3 * sigma_));
    for (size_t x = 0; x < image.Height(); ++x) {
        for (size_t y = 0; y < image.Width(); ++y) {
            double red = 0;
            double green = 0;
            double blue = 0;
            int32_t y0_min = static_cast<int32_t>(y) - delta_sigma;
            int32_t y0_max = static_cast<int32_t>(y) + delta_sigma;
            for (int32_t y0 = y0_min; y0 <= y0_max; ++y0) {
                double gauss_const = ConstCount(y0, static_cast<int32_t>(y));
                size_t y0_right =
                    std::min(static_cast<int32_t>(image.Width() - 1), std::max(static_cast<int32_t>(0), y0));
                red += gauss_const * static_cast<double>(image.GetRgb(x, y0_right).R());
                green += gauss_const * static_cast<double>(image.GetRgb(x, y0_right).G());
                blue += gauss_const * static_cast<double>(image.GetRgb(x, y0_right).B());
            }
            red = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), red));
            green = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), green));
            blue = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), blue));
            gauss_half[x][y] = RGB(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
        }
    }
    std::vector<std::vector<RGB>> gauss_all(image.Height(), std::vector<RGB>(image.Width()));
    for (size_t y = 0; y < image.Width(); ++y) {
        for (size_t x = 0; x < image.Height(); ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;
            int32_t x0_min = static_cast<int32_t>(x) - delta_sigma;
            int32_t x0_max = static_cast<int32_t>(x) + delta_sigma;
            for (int32_t x0 = x0_min; x0 <= x0_max; ++x0) {
                double gauss_const = ConstCount(x0, static_cast<int32_t>(x));
                size_t x0_right =
                    std::min(static_cast<int32_t>(image.Height() - 1), std::max(static_cast<int32_t>(0), x0));
                red += gauss_const * static_cast<double>(gauss_half[x0_right][y].R());
                green += gauss_const * static_cast<double>(gauss_half[x0_right][y].G());
                blue += gauss_const * static_cast<double>(gauss_half[x0_right][y].B());
            }
            red = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), red));
            green = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), green));
            blue = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), blue));
            gauss_all[x][y] = RGB(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
        }
    }
    image.ChangePixels(gauss_all);
}
