#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDebug>
#include <QString>

class MainMenu {
public:
    MainMenu();
    static MainMenu* getInstance();

    void printHeaderMenu();
    void printMainMenu();
    void printCheckConnectionsMenu();
    void printWarningMessageMenu();

private:
    static MainMenu* instance;
};

#endif // MAINMENU_H
