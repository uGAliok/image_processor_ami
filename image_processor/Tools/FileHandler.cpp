#include "FileHandler.h"
#include "fstream"

static constexpr uint16_t BIT_PER_PIXEL = 24;  // NOLINT
static constexpr size_t PIXEL_SEGMENTS = 3;    // NOLINT
static constexpr size_t BYTE_ALLIGNMENT = 4;   // NOLINT
static constexpr uint16_t BM = 0x4D42;         // NOLINT

static constexpr size_t FILE_HEADER_SIZE = sizeof(FileHeader);  // NOLINT
static constexpr size_t INFO_HEADER_SIZE = sizeof(InfoHeader);  // NOLINT

void Image::Read(const std::string path) {
    std::ifstream file;
    file.open(path, std::ios::binary | std::ios::in);

    // Checking for the opening a file
    if (!file) {
        throw std::runtime_error("ERROR: Wrong path to the file");
    }

    char file_header_buffer[FILE_HEADER_SIZE];
    file.read(file_header_buffer, FILE_HEADER_SIZE);
    FileHeader* file_header = reinterpret_cast<FileHeader*>(file_header_buffer);
    // Checking for the right image type
    if (file_header->header_field != BM) {
        file.close();
        throw std::runtime_error("ERROR: Wrong image type");
    }

    char info_header_buffer[INFO_HEADER_SIZE];
    file.read(info_header_buffer, INFO_HEADER_SIZE);
    InfoHeader* info_header = reinterpret_cast<InfoHeader*>(info_header_buffer);

    // Checking for the right bits per pixel
    if (info_header->bits_per_pixel != BIT_PER_PIXEL) {
        file.close();
        throw std::runtime_error("ERROR: Wrong BMP-image type");
    }

    width_ = info_header->width;
    height_ = info_header->height;

    if (width_ == 0 || height_ == 0) {
        width_ = height_ = 0;
    }

    const int padding =
        static_cast<int>((BYTE_ALLIGNMENT - PIXEL_SEGMENTS * (width_ % BYTE_ALLIGNMENT)) % BYTE_ALLIGNMENT);
    pixels_.assign(height_, std::vector<RGB>(width_));
    for (ssize_t i = static_cast<ssize_t>(height_ - 1); i >= 0; --i) {
        for (ssize_t j = 0; j < static_cast<ssize_t>(width_); ++j) {
            uint8_t pixel[3];
            file.read(reinterpret_cast<char*>(pixel), 3);
            pixels_[i][j] = RGB(pixel[2], pixel[1], pixel[0]);
        }
        file.ignore(padding);
    }
    file.close();
}

void Image::Save(const std::string path) {
    std::ofstream file;
    file.open(path, std::ios::binary | std::ios::out);
    if (!file) {
        throw std::runtime_error("ERROR: Wrong output path");
    }

    const int64_t padding =
        static_cast<int64_t>((BYTE_ALLIGNMENT - PIXEL_SEGMENTS * (width_ % BYTE_ALLIGNMENT)) % BYTE_ALLIGNMENT);

    FileHeader file_header;
    file_header.header_field = BM;
    file_header.size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + width_ * height_ * 3 + height_ * padding;
    file_header.specific_first = 0;
    file_header.specific_second = 0;
    file_header.offset = FILE_HEADER_SIZE + INFO_HEADER_SIZE;

    InfoHeader info_header;
    info_header.size = INFO_HEADER_SIZE;
    info_header.width = static_cast<int32_t>(width_);
    info_header.height = static_cast<int32_t>(height_);
    info_header.planes = 1;
    info_header.bits_per_pixel = BIT_PER_PIXEL;
    info_header.compression = 0;
    info_header.size_bitmap = 0;
    info_header.x_resolution = 0;
    info_header.y_resolution = 0;
    info_header.number_colors = 0;
    info_header.important = 0;

    file.write(reinterpret_cast<char*>(&file_header), FILE_HEADER_SIZE);
    file.write(reinterpret_cast<char*>(&info_header), INFO_HEADER_SIZE);
    uint8_t pad[3] = {0, 0, 0};
    for (ssize_t i = static_cast<ssize_t>(height_) - 1; i >= 0; --i) {
        for (size_t j = 0; j < width_; ++j) {
            uint8_t pixel[3] = {pixels_[i][j].B(), pixels_[i][j].G(), pixels_[i][j].R()};
            file.write(reinterpret_cast<char*>(pixel), 3);
        }
        if (padding != 0) {
            file.write(reinterpret_cast<char*>(pad), padding);
        }
    }
    file.close();
}
