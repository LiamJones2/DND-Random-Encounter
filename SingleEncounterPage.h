#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include "EncounterType.h"
#include "Encounter.h"

#ifndef SINGLEENCOUNTER_H_
#define SINGLEENCOUNTER_H_

// Stores all aspects of Encounter Types page
namespace SingleEncounterPage {
    extern QLabel* singleEncounterBackgroundWallpaper;
    extern QGroupBox* singleEncounterBox;
    extern QLabel* encounterName;
    extern QLabel* encounterDescription;
    extern QLabel* encounterImage;
    extern QPushButton* backToEncountersPageButton;

    // Sets all pointers to the UI items on single encounter page
    void setSingleEncounterUIItems(QWidget& mainWindow);

    // Sets UI items to show certain encounter info 
    void setupSingleEncounterPage();

    // Resizes UI items when window size changes
    void resizeSingleEncounter(QResizeEvent* event);
}

#endif // SINGLEENCOUNTER_H_