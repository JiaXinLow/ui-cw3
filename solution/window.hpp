#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include "model.hpp"  // Assuming model.hpp contains your data model

class StatsDialog;  // Forward declaration of StatsDialog class, assuming it's defined elsewhere

class WaterQualityWindow : public QMainWindow
{
    Q_OBJECT

public:
    WaterQualityWindow(QWidget* parent = nullptr);  // Constructor, you might want to use QWidget* parent

private:
    void createMainWidget();
    void createFileSelectors();
    void createButtons();
    void createToolBar();
    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();

    WaterQualityModel waterQualityModel;  // Data model used by the table
    QString dataLocation;                 // Location of CSV data files
    QComboBox* countryFilter;             // Selector for country (Y or WT)
    QComboBox* yearFilter;                // Selector for year (2018-2024)
    QPushButton* loadButton;             // Button to load a new CSV file
    QPushButton* statsButton;            // Button to display dataset stats
    QTableView* table;                   // Table of water quality data
    QLabel* fileInfo;                    // Status bar info on current file
    StatsDialog* statsDialog;            // Dialog to display stats

private slots:
    void setDataLocation();
    void openCSV();
    void displayStats();
    void about();
};
