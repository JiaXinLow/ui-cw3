#pragma once

#include <QDialog>

class QLineEdit;
class QPushButton;

class StatsDialog : public QDialog
{
  public:
    StatsDialog(QWidget* parent);
    void update(double avgConcentration, int sampleCount);

  private:
    QLineEdit* meanConcentration;
    QLineEdit* totalSamples;
    QPushButton* closeButton;

    void createWidgets();
    void arrangeWidgets();
};
