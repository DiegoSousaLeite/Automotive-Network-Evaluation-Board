#ifndef MCUINTERFACEMENU_H
#define MCUINTERFACEMENU_H

#include "MainMenu.h"

class MCUInterfaceMenu : public MainMenu {
public:
    static MCUInterfaceMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();

private:
    MCUInterfaceMenu();  // Construtor privado para o padrão Singleton
    static MCUInterfaceMenu* instance;
};

#endif // MCUINTERFACEMENU_H
