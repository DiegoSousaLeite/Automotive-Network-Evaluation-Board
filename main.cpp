#include "mainwindow.h"
#include "aneb.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include "EcuFrameController.h"
#include "McuFrameController.h"
#include "radialbar.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //Registro do tipo "RadialBar" para ser acessível no QML sob o namespace "CustomControls"
    qmlRegisterType<RadialBar>("CustomControls", 1, 0, "RadialBar");
    // Conexão para encerrar a aplicação se a interface não puder ser criada
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    // Carrega a interface QML a partir da URL especificada
    engine.load(url);
    // Criação dos controladores
        EcuFrameController ecuController;
        McuFrameController mcuController;

    // Carregar o arquivo QSS
    QFile file(":/style/styles.qss");  // Caminho para o arquivo .qss
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = file.readAll();  // Ler o conteúdo do arquivo
        app.setStyleSheet(styleSheet);        // Aplicar o estilo QSS à aplicação inteira
        file.close();  // Fechar o arquivo depois de ler
    } else {
        qWarning("Não foi possível carregar o arquivo de estilo.");
    }

    ANEB mainWindow;
    mainWindow.setEcuFrameController(&ecuController);
    mainWindow.setMcuFrameController(&mcuController);
    mainWindow.show();

   //mainWindow.initializeDevice();  // Inicia a configuração do dispositivo

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
