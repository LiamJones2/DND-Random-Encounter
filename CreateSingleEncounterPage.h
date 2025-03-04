#pragma once

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QFileDialog>
#include <QObject>
#include <qbuffer.h>
#include "Database.h"
#include "DNDRandomEncounter.h"

#ifndef CREATESINGLEENCOUNTERTYPE_H_
#define CREATESINGLEENCOUNTERTYPE_H_

// Stores all aspects of Encounter Types page
namespace CreateSingleEncounterPage {
    extern QGroupBox* createSingleEncounterBox;
    extern QLabel* createSingleEncounterWallpaper;
    extern QPushButton* backToEncountersButton;
    extern QPushButton* createSingleEncounterButton;
    extern QLineEdit* createSingleEncounterNameInput;
    extern QLabel* createSingleEncounterImageInput;
    extern QPushButton* uploadSingleEncounterImage;

    // Sets all pointers to the UI items on encounter types page
    void SetUIItemsCreateSingleEncounter(QWidget& mainWindow);

    // Resizes everything in the encounter types page when the window is resized
    void ResizeCreateSingleEncounter(QResizeEvent* event);

    void ChangeSingleEncounterImage(QWidget& mainWindow);

    bool CheckSingleEncounterNameValidation();

    bool CheckSingleEncounterImageValidation();

    bool CheckSingleEncounterValidation();

    void RegisterSingleEncounter();
}

#endif // CREATESINGLEENCOUNTERTYPE_H_