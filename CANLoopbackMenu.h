#ifndef CANLOOPBACKMENU_H
#define CANLOOPBACKMENU_H

#include "MainMenu.h"

class CANLoopbackMenu : public MainMenu {
public:
    static CANLoopbackMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    CANLoopbackMenu();  // Construtor privado para o padrão Singleton
    static CANLoopbackMenu* instance;
};

#endif // CANLOOPBACKMENU_H
