#pragma once
#include "RGB.h"
#include <vector>

class Image {
private:
    size_t width_;
    size_t height_;
    std::vector<std::vector<RGB>> pixels_;

public:
    Image();
    Image(size_t width, size_t height);

    void ChangePixel(RGB rgb, size_t x, size_t y);
    void ChangePixels(std::vector<std::vector<RGB>>& pixels);
    RGB ApplyMatrixToPixel(const size_t i, const size_t j, const std::vector<std::vector<double>>& matrix);

    size_t Width() const;
    size_t Height() const;
    RGB GetRgb(size_t x, size_t y) const;

    void Save(const std::string path);
    void Read(const std::string path);
};
