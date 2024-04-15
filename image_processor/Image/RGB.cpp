#include "RGB.h"

RGB::RGB() : r_(0), g_(0), b_(0) {
}

RGB::RGB(const RGB& other) {
    r_ = other.r_;
    g_ = other.g_;
    b_ = other.b_;
}

RGB::RGB(const uint8_t r, const uint8_t g, const uint8_t b) : r_(r), g_(g), b_(b) {
}

uint8_t RGB::R() const {
    return r_;
}

uint8_t RGB::G() const {
    return g_;
}

uint8_t RGB::B() const {
    return b_;
}

void RGB::SetR(const uint8_t r) {
    r_ = r;
}
void RGB::SetG(const uint8_t g) {
    g_ = g;
}
void RGB::SetB(const uint8_t b) {
    b_ = b;
}
