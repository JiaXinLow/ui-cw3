#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "csv.hpp"
#include "watersample.hpp"  // Include the WaterSample header

using namespace std;

// WaterQualityDataset class implementation
class WaterQualityDataset {
public:
    void loadData(const string& filename);  // Load data from CSV file
    WaterSample highestResult() const;      // Get the sample with the highest result
    double meanResult() const;              // Get the mean result of all samples
    size_t complianceSampleCount() const;   // Count how many compliance samples exist

private:
    vector<WaterSample> data;  // Container to store water samples
    void checkDataExists() const;  // Check if data is available
};

// Implementation of checkDataExists method
void WaterQualityDataset::checkDataExists() const {
    if (data.empty()) {
        throw runtime_error("No data available in dataset.");
    }
}

// Implementation of highestResult method
WaterSample WaterQualityDataset::highestResult() const {
    checkDataExists();  // Ensure that there is data before proceeding

    auto maxSample = *max_element(data.begin(), data.end(),
                                  [](const WaterSample& a, const WaterSample& b) {
                                      return a.getResult() < b.getResult();  // Compare the result values
                                  });

    return maxSample;
}

// Implementation of meanResult method
double WaterQualityDataset::meanResult() const {
    checkDataExists();  // Ensure that there is data before proceeding

    double total = accumulate(data.begin(), data.end(), 0.0,
                              [](double sum, const WaterSample& sample) {
                                  return sum + sample.getResult();  // Sum the result values
                              });

    return total / data.size();  // Return the mean
}

// Implementation of complianceSampleCount method
size_t WaterQualityDataset::complianceSampleCount() const {
    checkDataExists();  // Ensure that there is data before proceeding

    return count_if(data.begin(), data.end(),
                    [](const WaterSample& sample) { return sample.getCompliance(); });
}
