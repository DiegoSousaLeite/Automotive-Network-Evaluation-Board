#ifndef LOADSERIALPORTSMENU_H
#define LOADSERIALPORTSMENU_H

#include "MainMenu.h"

class LoadSerialPortsMenu : public MainMenu {
public:
    static LoadSerialPortsMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();

private:
    LoadSerialPortsMenu();  // Construtor privado para o padrão Singleton
    static LoadSerialPortsMenu* instance;
};

#endif // LOADSERIALPORTSMENU_H
