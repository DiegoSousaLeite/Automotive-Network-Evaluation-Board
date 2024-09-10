#ifndef ECUUPLOADMENU_H
#define ECUUPLOADMENU_H

#include "MainMenu.h"

class EcuUploadMenu : public MainMenu {
public:
    static EcuUploadMenu* getInstance();

    void printOptionMenu();
    void printEcuProcessorMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();
    void printReportTestMenu();

private:
    EcuUploadMenu();  // Construtor privado para o padrão Singleton
    static EcuUploadMenu* instance;
};

#endif // ECUUPLOADMENU_H
