#include "Filters.h"

const std::vector<std::vector<double>> EDGE_MATRIX{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

EdgeDetectionParameters::EdgeDetectionParameters(double arg1) : threshold(arg1) {
}

EdgeDetection::EdgeDetection(EdgeDetectionParameters*& parameter) : threshold_(parameter->threshold) {
}

void EdgeDetection::Process(Image& image) {
    Grayscale greyscale;
    greyscale.Process(image);
    std::vector<std::vector<RGB>> new_image(image.Height(), std::vector<RGB>(image.Width()));
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            RGB new_pixel = image.ApplyMatrixToPixel(i, j, EDGE_MATRIX);
            if (new_pixel.R() > static_cast<uint8_t>(threshold_ * MAX_VALUE)) {
                new_image[i][j] = RGB(MAX_VALUE, MAX_VALUE, MAX_VALUE);
            } else {
                new_image[i][j] = {MIN_VALUE, MIN_VALUE, MIN_VALUE};
            }
        }
    }
    image.ChangePixels(new_image);
}
