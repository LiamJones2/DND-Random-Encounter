#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include "DNDRandomEncounter.h"

/*
    Stores items on the main menu page
    Used to change of each when the window size changes
*/

#ifndef MAINMENU_H_
#define MAINMENU_H_

namespace MainMenuPage {
    // UI items on QT ui page
    extern QGroupBox* mainMenu;
    extern QLabel* backgroundWallpaper;
    extern QLabel* titleBackground;
    extern QLabel* titleText;
    extern QPushButton* closeButton;
    extern QPushButton* startButton;

    // Sets all pointers to the UI items on main menu
    void SetMainMenuUIItems(QWidget& mainWindow);

    // resizes menu when window size changes
    void ResizeMainMenu(QResizeEvent* event);
}

#endif // MAINMENU_H_