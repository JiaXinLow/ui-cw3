#pragma once

#include <QAbstractTableModel>
#include "dataset.hpp"  // Include the header for WaterQualityDataset class

class WaterQualityModel : public QAbstractTableModel
{
    Q_OBJECT  // Enable Qt's signal/slot mechanism

public:
    WaterQualityModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void updateFromFile(const QString&);
    bool hasData() const { return dataset.size() > 0; }
    int rowCount(const QModelIndex& index = QModelIndex()) const override { return dataset.size(); }
    int columnCount(const QModelIndex& index = QModelIndex()) const override { return 9; }
    QVariant data(const QModelIndex&, int) const override;
    QVariant headerData(int, Qt::Orientation, int) const override;
    double averageResult() const { return dataset.meanResult(); }
    double maxResult() const { return dataset.highestResult().getResult(); }

    // Clears the dataset and resets the model
    void clear();

private:
    WaterQualityDataset dataset;  // Ensure this class is defined in waterqualitydataset.hpp
};
