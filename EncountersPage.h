#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <random>
#include "Encounter.h"
#include "Main.h"

#ifndef ENCOUNTERS_H_
#define ENCOUNTERS_H_

// Stores all aspects of Encounters (multiple encounters) page
namespace EncountersPage {
    extern QPushButton* backToEncounterTypesPageButton;
    extern QLabel* encountersBackgroundWallpaper;
    extern QGroupBox* encountersGroupBox;
    extern QGroupBox* encountersBox;
    extern QGroupBox* encounters;
    extern QPushButton* getRandomEncounterButton;
    extern QPushButton* switchToCreateEncounterButton;
    extern QScrollBar* encountersScrollBar;

    // All encounters for the encounter types
    extern std::vector<Encounter> listOfEncounters;

    // Stores all buttons of encounters
    extern std::vector<QPushButton*> listOfEncountersButtons;

    // Sets all pointers to the UI items on encounters page
    void SetUIItemsEncounters(QWidget& mainWindow);

    // Resizes encounters page 
    void ResizeEncounters(QResizeEvent* event);

    void SetupScrollBar();

    void ResizeEncountersButtons(QResizeEvent* event);

    void GetRandomEncounter();
}

#endif // ENCOUNTERS_H_