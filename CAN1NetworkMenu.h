#ifndef CAN1NETWORKMENU_H
#define CAN1NETWORKMENU_H

#include "MainMenu.h"

class CAN1NetworkMenu : public MainMenu {
public:
    static CAN1NetworkMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    CAN1NetworkMenu();  // Construtor privado para o padrão Singleton
    static CAN1NetworkMenu* instance;
};

#endif // CAN1NETWORKMENU_H
