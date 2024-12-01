#include <QtWidgets>
#include "window.hpp"
#include "stats.hpp"

static const int MIN_WIDTH = 620;

WaterQualityWindow::WaterQualityWindow(QWidget* parent) : QMainWindow(parent), statsDialog(nullptr)
{
    createMainWidget();
    createFileSelectors();
    createButtons();
    createToolBar();
    createStatusBar();
    addFileMenu();
    addHelpMenu();

    setMinimumWidth(MIN_WIDTH);
    setWindowTitle("Water Quality Tool");
}

void WaterQualityWindow::createMainWidget()
{
    table = new QTableView();
    table->setModel(&waterQualityModel);

    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    setCentralWidget(table);
}

void WaterQualityWindow::createFileSelectors()
{
    // Country filter options (Y for Yorkshire, WT for another country)
    QStringList countryOptions;
    countryOptions << "Y" << "WT";  // Add more countries if needed
    countryFilter = new QComboBox();
    countryFilter->addItems(countryOptions);

    // Year filter options (2018-2024)
    QStringList yearOptions;
    for (int i = 2018; i <= 2024; ++i) {
        yearOptions << QString::number(i);  // Add years from 2018 to 2024
    }
    yearFilter = new QComboBox();
    yearFilter->addItems(yearOptions);
}

void WaterQualityWindow::createButtons()
{
    loadButton = new QPushButton("Load");
    statsButton = new QPushButton("Stats");

    connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
    connect(statsButton, SIGNAL(clicked()), this, SLOT(displayStats()));
}

void WaterQualityWindow::createToolBar()
{
    QToolBar* toolBar = new QToolBar();

    QLabel* countryLabel = new QLabel("Country");
    countryLabel->setAlignment(Qt::AlignVCenter);
    toolBar->addWidget(countryLabel);
    toolBar->addWidget(countryFilter);

    QLabel* yearLabel = new QLabel("Year");
    yearLabel->setAlignment(Qt::AlignVCenter);
    toolBar->addWidget(yearLabel);
    toolBar->addWidget(yearFilter);

    toolBar->addSeparator();

    toolBar->addWidget(loadButton);
    toolBar->addWidget(statsButton);

    addToolBar(Qt::LeftToolBarArea, toolBar);
}

void WaterQualityWindow::createStatusBar()
{
    fileInfo = new QLabel("Current file: <none>");
    QStatusBar* status = statusBar();
    status->addWidget(fileInfo);
}

void WaterQualityWindow::addFileMenu()
{
    QAction* locAction = new QAction("Set Data &Location", this);
    locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
    connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

    QAction* closeAction = new QAction("Quit", this);
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(locAction);
    fileMenu->addAction(closeAction);
}

void WaterQualityWindow::addHelpMenu()
{
    QAction* aboutAction = new QAction("&About", this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    QAction* aboutQtAction = new QAction("About &Qt", this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    QMenu* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void WaterQualityWindow::setDataLocation()
{
    QString directory = QFileDialog::getExistingDirectory(
        this, "Data Location", ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (directory.length() > 0) {
        dataLocation = directory;
    }
}

void WaterQualityWindow::openCSV()
{
    if (dataLocation == "") {
        QMessageBox::critical(this, "Data Location Error",
                              "Data location has not been set!\n\n"
                              "You can specify this via the File menu."
                              );
        return;
    }

    // Get selected country and year from the dropdowns
    QString country = countryFilter->currentText();  // Get selected country (Y or WT)
    QString year = yearFilter->currentText();        // Get selected year (2018-2024)

    // Construct the filename based on selected country and year (Format: Y-2024.csv)
    auto filename = QString("%1-%2.csv")
                        .arg(country)                          // Use selected country (Y or WT)
                        .arg(year);                            // Use selected year

    auto path = dataLocation + "/" + filename;

    try {
        waterQualityModel.updateFromFile(path);  // Update the model with the correct file
    }
    catch (const std::exception& error) {
        QMessageBox::critical(this, "CSV File Error", error.what());
        return;
    }

    fileInfo->setText(QString("Current file: <kbd>%1</kbd>").arg(filename));
    table->resizeColumnsToContents();

    // Update the stats dialog if it is visible
    if (statsDialog != nullptr && statsDialog->isVisible()) {
        statsDialog->update(waterQualityModel.averageResult(), waterQualityModel.maxResult());
    }
}

void WaterQualityWindow::displayStats()
{
    if (waterQualityModel.hasData()) {
        if (statsDialog == nullptr) {
            statsDialog = new StatsDialog(this);
        }

        // Update with relevant statistics (mean pollutant concentration, max result)
        statsDialog->update(waterQualityModel.averageResult(), waterQualityModel.maxResult());

        statsDialog->show();
        statsDialog->raise();
        statsDialog->activateWindow();
    }
}

void WaterQualityWindow::about()
{
    QMessageBox::about(this, "About Water Quality Tool",
                       "Water Quality Tool displays and analyzes water quality data loaded from"
                       "CSV files containing sample information from various locations.\n\n"
                       "(c) 2024 Your Name");
}
