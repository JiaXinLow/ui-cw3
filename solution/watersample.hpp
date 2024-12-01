#pragma once

#include <string>
#include <iostream>

// WaterSample struct definition
struct WaterSample {
    std::string id;                    // Sample ID
    std::string samplingPoint;         // Sampling point (ID or URL)
    std::string samplingPointNotation; // Sampling point notation (e.g., NE-40000385)
    std::string samplingPointLabel;    // Sampling point label (e.g., MALHAM TARN)
    std::string dateTime;              // Date and time of the sample (e.g., "2024-12-01T14:08:00")
    std::string determinandLabel;      // Determinand label (e.g., Endrin)
    std::string determinandDefinition; // Determinand definition (e.g., Endrin)
    std::string determinandNotation;  // Determinand notation (e.g., 0562)
    std::string resultQualifier;       // Result qualifier (e.g., "<")
    double result;                     // Measurement result (e.g., 0.0001)
    std::string codedResultInterpretation; // Coded result interpretation (empty in dataset example)
    std::string unitLabel;             // Unit label (e.g., ug/l)
    std::string sampledMaterialType;   // Sampled material type (e.g., POND / LAKE / RESERVOIR WATER)
    bool isComplianceSample;           // Whether it's a compliance sample (true/false)
    std::string purposeLabel;          // Sample purpose (e.g., ENVIRONMENTAL MONITORING STATUTORY (EU DIRECTIVES))
    double easting;                    // Easting coordinate of the sampling point
    double northing;                   // Northing coordinate of the sampling point

    // Constructor definition
    WaterSample(const std::string& id, const std::string& samplingPoint, const std::string& samplingPointNotation, 
                const std::string& samplingPointLabel, const std::string& dateTime, const std::string& determinandLabel, 
                const std::string& determinandDefinition, const std::string& determinandNotation, 
                const std::string& resultQualifier, double result, const std::string& codedResultInterpretation, 
                const std::string& unitLabel, const std::string& sampledMaterialType, bool isComplianceSample, 
                const std::string& purposeLabel, double easting, double northing)
        : id(id), samplingPoint(samplingPoint), samplingPointNotation(samplingPointNotation), samplingPointLabel(samplingPointLabel),
          dateTime(dateTime), determinandLabel(determinandLabel), determinandDefinition(determinandDefinition), 
          determinandNotation(determinandNotation), resultQualifier(resultQualifier), result(result),
          codedResultInterpretation(codedResultInterpretation), unitLabel(unitLabel), sampledMaterialType(sampledMaterialType),
          isComplianceSample(isComplianceSample), purposeLabel(purposeLabel), easting(easting), northing(northing) {}

    // Getters for each field
    std::string getId() const { return id; }
    std::string getSamplingPoint() const { return samplingPointLabel; }
    std::string getSamplingPointNotation() const { return samplingPointNotation; }
    std::string getSamplingPointLabel() const { return samplingPointLabel; }
    std::string getDateTime() const { return dateTime; }
    std::string getDeterminandLabel() const { return determinandLabel; }
    std::string getDeterminandDefinition() const { return determinandDefinition; }
    std::string getDeterminandNotation() const { return determinandNotation; }
    std::string getResultQualifier() const { return resultQualifier; }
    double getResult() const { return result; }
    std::string getCodedResultInterpretation() const { return codedResultInterpretation; }
    std::string getUnitLabel() const { return unitLabel; }
    std::string getSampledMaterialType() const { return sampledMaterialType; }
    bool getCompliance() const { return isComplianceSample; }
    std::string getPurposeLabel() const { return purposeLabel; }
    double getEasting() const { return easting; }
    double getNorthing() const { return northing; }

    // Overload the output stream operator to print a WaterSample
    friend std::ostream& operator<<(std::ostream& out, const WaterSample& sample);
};