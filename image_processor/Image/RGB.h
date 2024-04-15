#pragma once
#include <cstdint>
#include <cstddef>
#include <stdexcept>

static constexpr uint8_t MIN_VALUE = 0;    // NOLINT
static constexpr uint8_t MAX_VALUE = 255;  // NOLINT

class RGB {
public:
    RGB();
    RGB(const RGB& other);
    RGB(const uint8_t r, const uint8_t g, const uint8_t b);
    ~RGB() = default;

    uint8_t R() const;
    uint8_t G() const;
    uint8_t B() const;

    void SetR(const uint8_t r);
    void SetG(const uint8_t g);
    void SetB(const uint8_t b);

private:
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
};
