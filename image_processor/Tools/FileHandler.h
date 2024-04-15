#pragma once
#include "../Image/Image.h"
#include <cstdint>

struct FileHeader {
    uint16_t header_field __attribute__((packed));
    uint32_t size __attribute__((packed));
    uint16_t specific_first __attribute__((packed));
    uint16_t specific_second __attribute__((packed));
    uint32_t offset __attribute__((packed));
};

struct InfoHeader {
    uint32_t size __attribute__((packed));
    int32_t width __attribute__((packed));
    int32_t height __attribute__((packed));
    int16_t planes __attribute__((packed));
    int16_t bits_per_pixel __attribute__((packed));
    uint32_t compression __attribute__((packed));
    uint32_t size_bitmap __attribute__((packed));
    int32_t x_resolution __attribute__((packed));
    int32_t y_resolution __attribute__((packed));
    uint32_t number_colors __attribute__((packed));
    uint32_t important __attribute__((packed));
};
