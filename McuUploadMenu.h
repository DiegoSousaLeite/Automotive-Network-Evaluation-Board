#ifndef MCUUPLOADMENU_H
#define MCUUPLOADMENU_H

#include "MainMenu.h"

class McuUploadMenu : public MainMenu {
public:
    static McuUploadMenu* getInstance();

    void printOptionMenu();
    void printWarningMessageMenu();
    void printStartedTestMenu();
    void printFinishedTestMenu();

private:
    McuUploadMenu();  // Construtor privado para o padrão Singleton
    static McuUploadMenu* instance;
};

#endif // MCUUPLOADMENU_H
