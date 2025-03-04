#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include "EncounterType.h"
#include "DNDRandomEncounter.h"

#ifndef ENCOUNTERTYPES_H_
#define ENCOUNTERTYPES_H_

// Stores all aspects of Encounter Types page
namespace EncounterTypesPage {
    extern QGroupBox* encounterTypes;
    extern QLabel* encounterTypesWallpaper;
    extern QGroupBox* encounterTypesGroupBox;
    extern QGroupBox* encounterTypesBox;
    extern QPushButton* backToMainMenu;
    extern QPushButton* switchToCreateEncounterType;
    extern QPushButton* encounterTypesSwipeButton;
    extern QScrollBar* encounterTypesScrollBar;

    // Width of each button size
    extern int buttonWidth;

    // Stores all encounter types
    extern std::vector<EncounterType> encounterTypesFromDB;

    // Stores all buttons for the encounter types
    extern std::vector<QPushButton*> encounterTypesButtons;

    extern std::vector<QPixmap> buttonPixmaps;

    // Sets all pointers to the UI items on encounter types page
    void SetUIItemsEncounterTypes(QWidget& mainWindow);

    void SetupEncounterTypesPixmap();

    void UpdateEachEncounterTypeButtonPixmap();

    // Resizes everything in the encounter types page when the window is resized
    void resizeEncounterTypes(QResizeEvent* event);

    void AddNewEncounterTypeButton(QString name, QByteArray imageDat);
}

#endif // ENCOUNTERTYPES_H_