#include <QtWidgets>
#include "window.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    WaterQualityWindow window; // Updated to reflect the water quality application
    window.show();

    return app.exec();
}
