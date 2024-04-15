#pragma once
#include "../Image/Image.h"
#include <iostream>

// ABSTRACT

enum FilterName { CROP, GREYSCALE, NEGATIVE, SHARPENING, EDGEDETECTION, GAUSSIANBLUR, FISHEYE };

struct AbstractParameters {};

struct FilterParameters {
    FilterParameters(FilterName arg1, AbstractParameters* arg2) : filter_name(arg1), parameters(arg2) {
    }
    ~FilterParameters() = default;
    FilterName filter_name;
    AbstractParameters* parameters;
};

class AbstractFilter {
public:
    virtual void Process(Image& image) = 0;
    virtual ~AbstractFilter() = default;
};

// CROP

struct CropParameters : AbstractParameters {
    CropParameters(size_t arg1, size_t arg2);
    size_t new_width;
    size_t new_height;
};

class Crop : public AbstractFilter {
public:
    Crop() = default;
    explicit Crop(CropParameters*& parameters);
    ~Crop() override = default;
    void Process(Image& image) override;

private:
    size_t new_width_;
    size_t new_height_;
};

// GRAYSCALE

struct GrayscaleParameters : AbstractParameters {};

class Grayscale : public AbstractFilter {
public:
    Grayscale() = default;
    ~Grayscale() override = default;
    void Process(Image& image) override;
};

// NEGATIVE

struct NegativeParameters : AbstractParameters {};

class Negative : public AbstractFilter {
public:
    Negative() = default;
    ~Negative() override = default;
    void Process(Image& image) override;
};

// SHARPENING

struct SharpeningParameters : AbstractParameters {};

class Sharpening : public AbstractFilter {
public:
    Sharpening() = default;
    ~Sharpening() override = default;
    void Process(Image& image) override;
};

//  EDGEDETECTION

struct EdgeDetectionParameters : GrayscaleParameters {
    explicit EdgeDetectionParameters(double arg1);
    double threshold;
};

class EdgeDetection : public Grayscale {
public:
    EdgeDetection() = default;
    explicit EdgeDetection(EdgeDetectionParameters*& parameter);
    ~EdgeDetection() override = default;

    void Process(Image& image) override;

private:
    double threshold_;
};

//  GAUSSIAN BLUR

struct BlurParameters : AbstractParameters {
    explicit BlurParameters(double arg1);
    double sigma;
};

class Blur : public AbstractFilter {
public:
    Blur() = default;
    explicit Blur(BlurParameters*& parameter);
    ~Blur() override = default;

    void Process(Image& image) override;
    double ConstCount(int32_t c0, int32_t c) const;

private:
    double sigma_;
};

//  FISHEYE

struct FishEyeParameters : AbstractParameters {
    explicit FishEyeParameters(double arg1);
    double sigma;
};

class FishEye : public AbstractFilter {
public:
    FishEye() = default;
    explicit FishEye(FishEyeParameters*& parameter);
    ~FishEye() override = default;

    void Process(Image& image) override;

private:
    double sigma_;
};
