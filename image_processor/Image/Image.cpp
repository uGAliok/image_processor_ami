#include "Image.h"

Image::Image() : width_(0), height_(0) {
}

Image::Image(size_t width, size_t height)
    : width_(width), height_(height), pixels_(height_, std::vector(width_, RGB())) {
}

size_t Image::Width() const {
    return width_;
}

size_t Image::Height() const {
    return height_;
}

RGB Image::GetRgb(const size_t x, const size_t y) const {
    return pixels_[x][y];
}

void Image::ChangePixel(RGB rgb, size_t x, size_t y) {
    if (!(x >= 0 && y >= 0 && x < height_ && y < width_)) {
        throw std::runtime_error("ERROR: Out of the image");
    }
    pixels_[x][y] = rgb;
}

void Image::ChangePixels(std::vector<std::vector<RGB>>& pixels) {
    pixels_ = pixels;
    height_ = pixels.size();
    if (height_ == 0) {
        width_ = 0;
    } else {
        width_ = pixels[0].size();
    }
}

RGB Image::ApplyMatrixToPixel(const size_t i, const size_t j, const std::vector<std::vector<double>>& matrix) {
    double red = 0;
    double green = 0;
    double blue = 0;
    const int32_t center_i = static_cast<int32_t>((matrix.size() - 1) / 2);
    const int32_t center_j = static_cast<int32_t>((matrix.size() - 1) / 2);
    for (size_t n = 0; n < matrix.size(); ++n) {
        for (size_t m = 0; m < matrix[n].size(); ++m) {
            if (matrix[n][m] == 0) {
                continue;
            }
            int32_t i_temporary = static_cast<int32_t>(i) + static_cast<int32_t>(n) - center_i;
            int32_t j_temporary = static_cast<int32_t>(j) + static_cast<int32_t>(m) - center_j;
            size_t i_to = std::min(static_cast<int32_t>(height_ - 1), std::max(static_cast<int32_t>(0), i_temporary));
            size_t j_to = std::min(static_cast<int32_t>(width_ - 1), std::max(static_cast<int32_t>(0), j_temporary));
            red += matrix[n][m] * static_cast<double>(pixels_[i_to][j_to].R());
            green += matrix[n][m] * static_cast<double>(pixels_[i_to][j_to].G());
            blue += matrix[n][m] * static_cast<double>(pixels_[i_to][j_to].B());
        }
    }
    red = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), red));
    green = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), green));
    blue = std::min(static_cast<double>(MAX_VALUE), std::max(static_cast<double>(0), blue));
    return RGB(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
}
