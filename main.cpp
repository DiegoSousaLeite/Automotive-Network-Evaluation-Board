#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    mainWindow.initializeDevice();  // Inicia a configuração do dispositivo

    return app.exec();
}

//#include <QCoreApplication>
//#include "JigaView.h"
//#include "EcuFrameController.h"
//#include "McuFrameController.h"

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    // Criação dos controladores
//    EcuFrameController ecuController;
//    McuFrameController mcuController;

//    // Criação da view e configuração dos controladores
//    JigaView jigaView;
//    jigaView.setEcuFrameController(&ecuController);
//    jigaView.setMcuFrameController(&mcuController);

//    // Inicia o loop principal
//    jigaView.start();

//    return a.exec();  // Mantém a aplicação rodando
//}
