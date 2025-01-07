#include "HeartlineApp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Create the QApplication object
    QApplication app(argc, argv);

    // Instantiate the HeartlineApp
    HeartlineApp mainWindow;
    mainWindow.show(); // Show the main application window

    // Run the application event loop
    return app.exec();
}
