#include <stdexcept>
#include <sstream>
#include "watersample.hpp"
#include "dataset.hpp"
#include <fstream>

using namespace std;

std::ostream& operator<<(std::ostream& out, const WaterSample& sample) {
    return out << "Sampling Point: " << sample.getSamplingPoint()
    << "\nDate/Time: " << sample.getDateTime()
    << "\nDeterminand: " << sample.getDeterminandLabel()
    << "\nResult: " << sample.getResult() << " " << sample.unitLabel
    << "\nCompliance Status: " << (sample.getCompliance() ? "Compliant" : "Non-Compliant")
    << "\nEasting: " << sample.getEasting()
    << "\nNorthing: " << sample.getNorthing() << std::endl;
}

void WaterQualityDataset::loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, samplingPointLabel, samplingPointNotation, dateTime, determinandLabel, determinandDefinition,
            determinandNotation, resultQualifier, codedResultInterpretation, unitLabel, sampledMaterialType,
            purposeLabel;
        double result, easting, northing;
        bool isComplianceSample;

        // Parse each line and create a WaterSample
        std::getline(ss, id, ',');
        std::getline(ss, samplingPointLabel, ',');
        std::getline(ss, samplingPointNotation, ',');
        std::getline(ss, samplingPointLabel, ',');
        std::getline(ss, dateTime, ',');
        std::getline(ss, determinandLabel, ',');
        std::getline(ss, determinandDefinition, ',');
        std::getline(ss, determinandNotation, ',');
        std::getline(ss, resultQualifier, ',');
        ss >> result; ss.ignore();
        std::getline(ss, codedResultInterpretation, ',');
        std::getline(ss, unitLabel, ',');
        std::getline(ss, sampledMaterialType, ',');
        ss >> isComplianceSample; ss.ignore();
        std::getline(ss, purposeLabel, ',');
        ss >> easting; ss.ignore();
        ss >> northing; ss.ignore();

        // Create a WaterSample object and add it to the dataset
        WaterSample sample(id, samplingPointLabel, samplingPointNotation, samplingPointLabel, dateTime, determinandLabel,
                           determinandDefinition, determinandNotation, resultQualifier, result, codedResultInterpretation,
                           unitLabel, sampledMaterialType, isComplianceSample, purposeLabel, easting, northing);
        data.push_back(sample);  // Assuming data is a vector<WaterSample>
    }

    file.close();
}
