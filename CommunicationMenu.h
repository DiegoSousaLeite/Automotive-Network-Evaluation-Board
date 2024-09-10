#ifndef COMMUNICATIONMENU_H
#define COMMUNICATIONMENU_H

#include "MainMenu.h"

class CommunicationMenu : public MainMenu {
public:
    static CommunicationMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    CommunicationMenu();  // Construtor privado para o padrão Singleton
    static CommunicationMenu* instance;
};

#endif // COMMUNICATIONMENU_H
