#ifndef CAN2NETWORKMENU_H
#define CAN2NETWORKMENU_H

#include "MainMenu.h"

class CAN2NetworkMenu : public MainMenu {
public:
    static CAN2NetworkMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    CAN2NetworkMenu();  // Construtor privado para o padrão Singleton
    static CAN2NetworkMenu* instance;
};

#endif // CAN2NETWORKMENU_H
