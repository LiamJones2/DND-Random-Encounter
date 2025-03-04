#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QFileDialog>
#include <QObject>
#include <qbuffer.h>
#include "Database.h"
#include "DNDRandomEncounter.h"

#ifndef CREATEENCOUNTERTYPE_H_
#define CREATEENCOUNTERTYPE_H_

// Stores all aspects of Encounter Types page
namespace CreateEncounterTypePage {
    extern QGroupBox* creatEncounterTypeBox;
    extern QLabel* createSingleEncounterWallpaper;
    extern QPushButton* backToEncounterTypes;
    extern QPushButton* createEncounterTypeButton;
    extern QLineEdit* createEncounterTypeNameInput;
    extern QLabel* createEncounterTypeImageInput;
    extern QPushButton* uploadEncounterTypeImage;

    // Sets all pointers to the UI items on encounter types page
    void SetUIItemsCreateEncounterType(QWidget& mainWindow);

    // Resizes everything in the encounter types page when the window is resized
    void ResizeCreateEncounterType(QResizeEvent* event);

    void ChangeEncounterTypeImage(QWidget& mainWindow);

    bool CheckEncounterTypeNameValidation();

    bool CheckEncounterTypeImageValidation();

    bool CheckEncounterTypeValidation();

    void RegisterEncounterType();
}

#endif // CREATEENCOUNTERTYPE_H_