#ifndef CANINITMENU_H
#define CANINITMENU_H

#include "MainMenu.h"

class CANInitMenu : public MainMenu {
public:
    static CANInitMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    CANInitMenu();  // Construtor privado para o padrão Singleton
    static CANInitMenu* instance;
};

#endif // CANINITMENU_H
