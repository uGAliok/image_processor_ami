#include "Filters.h"

const std::vector<std::vector<double>> SHARP_MATRIX{{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

void Sharpening::Process(Image& image) {
    std::vector<std::vector<RGB>> new_image(image.Height(), std::vector<RGB>(image.Width()));
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            RGB new_pixel = image.ApplyMatrixToPixel(i, j, SHARP_MATRIX);
            new_image[i][j] = new_pixel;
        }
    }
    image.ChangePixels(new_image);
}
