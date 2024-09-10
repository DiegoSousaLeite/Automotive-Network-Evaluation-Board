#ifndef DIGITALINPUTMENU_H
#define DIGITALINPUTMENU_H

#include "MainMenu.h"

class DigitalInputMenu : public MainMenu {
public:
    static DigitalInputMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    DigitalInputMenu();  // Construtor privado para o padrão Singleton
    static DigitalInputMenu* instance;
};

#endif // DIGITALINPUTMENU_H
