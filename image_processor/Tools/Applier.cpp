#include "Applier.h"

Applier::Applier(const std::vector<FilterParameters>& options) {
    MakeFilters(options);
}

Applier::~Applier() {
    for (size_t i = 0; i < filters_.size(); ++i) {
        delete filters_[i];
    }
}

void Applier::MakeFilters(const std::vector<FilterParameters>& parameters) {
    for (const FilterParameters& option : parameters) {
        switch (option.filter_name) {
            case CROP: {
                CropParameters* crop_params = reinterpret_cast<CropParameters*>(option.parameters);
                filters_.push_back(new Crop(crop_params));
            } break;
            case GREYSCALE: {
                filters_.push_back(new Grayscale());
            } break;
            case NEGATIVE: {
                filters_.push_back(new Negative());
            } break;
            case SHARPENING: {
                filters_.push_back(new Sharpening());
            } break;
            case EDGEDETECTION: {
                EdgeDetectionParameters* edge_parameter = reinterpret_cast<EdgeDetectionParameters*>(option.parameters);
                filters_.push_back(new EdgeDetection(edge_parameter));
            } break;
            case GAUSSIANBLUR: {
                BlurParameters* blur_parameter = reinterpret_cast<BlurParameters*>(option.parameters);
                filters_.push_back(new Blur(blur_parameter));
            } break;
            case FISHEYE: {
                FishEyeParameters* fish_parameter = reinterpret_cast<FishEyeParameters*>(option.parameters);
                filters_.push_back(new FishEye(fish_parameter));
            } break;
            default: {
                throw std::logic_error("Unknown filter name");
            }
        }
    }
}

void Applier::ApplyFilters(Image& image) {
    for (AbstractFilter* const filter : filters_) {
        filter->Process(image);
    }
}
