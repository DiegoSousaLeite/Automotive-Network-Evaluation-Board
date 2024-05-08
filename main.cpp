#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    mainWindow.initializeDevice();  // Inicia a configuração do dispositivo

    return app.exec();
}
