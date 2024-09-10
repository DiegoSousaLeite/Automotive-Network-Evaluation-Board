#ifndef REPORTTESTMENUS_H
#define REPORTTESTMENUS_H

#include "MainMenu.h"

class ReportTestMenus : public MainMenu {
public:
    static ReportTestMenus* getInstance();

    void printReportMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();


private:
    ReportTestMenus();  // Construtor privado para o padrão Singleton
    static ReportTestMenus* instance;
};

#endif // REPORTTESTMENUS_H
