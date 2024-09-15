#ifndef ANEB_H
#define ANEB_H

#include <QWidget>
#include <QSerialPort>
#include "ui_aneb.h"
#include "SystemDefinition.h"
#include "PersistenceController.h"
#include "McuBusinessController.h"
#include "EcuBusinessController.h"
#include "EcuFrameController.h"
#include "McuFrameController.h"
#include "DashboardWidget.h"

namespace Ui {
class ANEB;
}

class ANEB : public QWidget
{
    Q_OBJECT

public:
    explicit ANEB(QWidget *parent = nullptr); // Construtor que aceita um ponteiro para o widget pai
    ~ANEB(); // Destrutor para liberar recursos

    static ANEB *instance; // Ponteiro estático para a instância da classe ANEB

    void setEcuFrameController(EcuFrameController *controller); // Define o controlador de frame ECU
    void setMcuFrameController(McuFrameController *controller); // Define o controlador de frame MCU

    void initializeDevice(); // Inicializa o dispositivo e os componentes do PersistenceController, EcuBusinessController e McuBusinessController

private slots:

    // Slot para limpar o console
    void onCleanConsoleButtonClicked();

    // Slot para troca de página no QStackedWidget
    void onChangePage(int page, int pageIndex);

    // Slot para execução de testes de comunicação
    void onExecuteTest(int tipo, int id);

private:
    Ui::ANEB *ui; // Ponteiro para a interface de usuário gerada pelo Qt Designer
    QTextBrowser* console1; // Ponteiro para o primeiro console de log
    QTextBrowser* console2; // Ponteiro para o segundo console de log

    EcuFrameController *ecuFmController; // Ponteiro para o controlador de frame ECU
    McuFrameController *mcuFmController; // Ponteiro para o controlador de frame MCU
    DashboardWidget *dashboardWidget; // Ponteiro para o widget do dashboard
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg); // Método estático para manipulação personalizada de mensagens de log
};

#endif // ANEB_H
