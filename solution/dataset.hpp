#pragma once

#include <vector>
#include <string>
#include "watersample.hpp"  // Include the WaterSample header to access its members

class WaterQualityDataset {
public:
    WaterQualityDataset() {}
    WaterQualityDataset(const std::string& filename) { loadData(filename); }
    void loadData(const std::string& filename);
    int size() const { return data.size(); }
    WaterSample operator[](int index) const { return data.at(index); }
    WaterSample highestResult() const;
    double meanResult() const;
    size_t complianceSampleCount() const;
    void clear() { data.clear(); }

private:
    std::vector<WaterSample> data;
    void checkDataExists() const;
};
