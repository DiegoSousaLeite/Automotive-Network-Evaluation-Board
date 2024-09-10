#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "ui_mainwindow.h"
#include "virtual_io.h"
#include "SystemDefinition.h"
#include "PersistenceController.h"
#include "McuBusinessController.h"
#include "EcuBusinessController.h"
#include "EcuFrameController.h"
#include "McuFrameController.h"
#include "RCWebcam.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeDevice(); //Main do PersistenceController,EcuBusinessController e McuBusinessController

private:
    Ui::MainWindow *ui;
    Virtual_IO *virtualIOWidget;  // Instância da interface de I/O Virtual
    static QTextBrowser *staticConsole;  // Referência estática ao console
    EcuFrameController *ecuFmController;

    void setupButtonStyles();  // Método para configurar os estilos dos botões
    void resetButtonStyles(const QString &defaultStyle);  // Método para resetar os estilos dos botões
    void showVirtualIO();
    void onFirmwareUpdateButtonClicked();
    void onMasterResetButtonClicked();
    void onECU3CANBusButtonClicked();
    void onECU4CANBusButtonClicked();
    void onLoadWebCamButtonClicked();
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg); // Método para configurar o console


    void onCleanConsoleButtonClicked();

signals:
    //IDEIAS
    void resetFinished();
    void ecu3CANBusFinished();
    void ecu4CANBusFinished();
    void firmwareUploadFinished();

public slots:
    void pageFirmware();
    void pageVirtual();
    void updateComboBoxCommPortList();
};



#endif // MAINWINDOW_H
