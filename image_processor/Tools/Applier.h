#pragma once
#include "../Filters/Filters.h"

class Applier {
public:
    Applier() = default;
    explicit Applier(const std::vector<FilterParameters>& options);
    ~Applier();

    void MakeFilters(const std::vector<FilterParameters>& options);
    void ApplyFilters(Image& image);

private:
    std::vector<AbstractFilter*> filters_;
};
