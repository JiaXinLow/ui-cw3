#include "model.hpp"

void WaterQualityModel::clear() {
    dataset.clear();  // Clear the dataset
}

void WaterQualityModel::updateFromFile(const QString& filename) {
    beginResetModel();   // Notify the model about the reset
    clear();             // Clear any existing data
    dataset.loadData(filename.toStdString());  // Load the new data from the file
    endResetModel();     // Notify the model that the data has been updated
}

QVariant WaterQualityModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        const WaterSample& sample = dataset[index.row() + 1];   //skip first row (column header)
        switch (index.column()) {
        case 0: return QVariant(sample.getId().c_str());
        case 1: return QVariant(sample.getSamplingPointLabel().c_str());
        case 2: return QVariant(sample.getDeterminandLabel().c_str());
        case 3: return QVariant(sample.getResult());
        case 4: return QVariant(sample.getUnitLabel().c_str());
        case 5: return QVariant(sample.getCompliance() ? "Compliant" : "Non-Compliant");
        case 6: return QVariant(sample.getEasting());
        case 7: return QVariant(sample.getNorthing());
        case 8: return QVariant(sample.getDateTime().c_str());
        default: return QVariant();
        }
    }

    return QVariant();
}

QVariant WaterQualityModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Vertical) {
        return QVariant(section + 1);
    }

    switch (section) {
    case 0: return QString("Sample ID");
    case 1: return QString("Sampling Point");
    case 2: return QString("Determinand");
    case 3: return QString("Concentration");
    case 4: return QString("Unit Label");
    case 5: return QString("Compliance Status");
    case 6: return QString("Easting");
    case 7: return QString("Northing");
    case 8: return QString("Date & Time");
    default: return QVariant();
    }
}
