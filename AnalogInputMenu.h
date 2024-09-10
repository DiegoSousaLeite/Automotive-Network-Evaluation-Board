#ifndef ANALOGINPUTMENU_H
#define ANALOGINPUTMENU_H

#include "MainMenu.h"

class AnalogInputMenu : public MainMenu {
public:
    static AnalogInputMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    AnalogInputMenu();  // Construtor privado para o padrão Singleton
    static AnalogInputMenu* instance;
};

#endif // ANALOGINPUTMENU_H
