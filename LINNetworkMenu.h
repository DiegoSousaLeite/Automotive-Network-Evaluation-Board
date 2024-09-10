#ifndef LINNETWORKMENU_H
#define LINNETWORKMENU_H

#include "MainMenu.h"

class LINNetworkMenu : public MainMenu {
public:
    static LINNetworkMenu* getInstance();

    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    LINNetworkMenu();  // Construtor privado para o padrão Singleton
    static LINNetworkMenu* instance;
};

#endif // LINNETWORKMENU_H
