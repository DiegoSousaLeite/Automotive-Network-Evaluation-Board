#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "virtual_io.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Virtual_IO *virtualIOWidget;  // Instância da interface de I/O Virtual
    static QTextBrowser *staticConsole;  // Referência estática ao console

    void setupButtonStyles();  // Método para configurar os estilos dos botões
    void resetButtonStyles(const QString &defaultStyle);  // Método para resetar os estilos dos botões
    void showVirtualIO();
    void onFirmwareUpdateButtonClicked();
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg); // Método para configurar o console


    void onCleanConsoleButtonClicked();
public slots:
    void pageFirmware();
    void pageVirtual();
};



#endif // MAINWINDOW_H
