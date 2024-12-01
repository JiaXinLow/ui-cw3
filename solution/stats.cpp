#include <QtWidgets>
#include "stats.hpp"

StatsDialog::StatsDialog(QWidget* parent) : QDialog(parent)
{
    createWidgets();
    arrangeWidgets();
    setWindowTitle("Water Quality Stats");
}

void StatsDialog::update(double avgConcentration, int sampleCount)
{
    meanConcentration->setText(QString::number(avgConcentration, 'f', 2)); // Two decimal places for precision
    totalSamples->setText(QString::number(sampleCount));
}

void StatsDialog::createWidgets()
{
    meanConcentration = new QLineEdit("?");
    meanConcentration->setMaxLength(10);
    meanConcentration->setReadOnly(true);

    totalSamples = new QLineEdit("?");
    totalSamples->setMaxLength(10);
    totalSamples->setReadOnly(true);

    closeButton = new QPushButton("Close");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void StatsDialog::arrangeWidgets()
{
    QFormLayout* form = new QFormLayout();
    form->addRow("Mean Concentration (mg/L):", meanConcentration);
    form->addRow("Total Samples:", totalSamples);

    QVBoxLayout* box = new QVBoxLayout();
    box->addLayout(form);
    box->addWidget(closeButton);

    setLayout(box);
}
