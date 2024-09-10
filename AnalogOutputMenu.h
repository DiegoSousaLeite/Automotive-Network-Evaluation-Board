#ifndef ANALOGOUTPUTMENU_H
#define ANALOGOUTPUTMENU_H

#include "MainMenu.h"

class AnalogOutputMenu : public MainMenu {
public:
    static AnalogOutputMenu* getInstance();

    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    AnalogOutputMenu();
    static AnalogOutputMenu* instance;
};

#endif // ANALOGOUTPUTMENU_H
