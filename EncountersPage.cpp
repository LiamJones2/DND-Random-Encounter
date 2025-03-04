#include "EncountersPage.h"


// Stores all aspects of Encounters (multiple encounters) page
namespace EncountersPage {
    QPushButton* backToEncounterTypesPageButton = nullptr;
    QLabel* encountersBackgroundWallpaper = nullptr;
    QGroupBox* encountersGroupBox = nullptr;
    QGroupBox* encountersBox = nullptr;
    QGroupBox* encounters = nullptr;
    QPushButton* getRandomEncounterButton = nullptr;
    QPushButton* switchToCreateEncounterButton = nullptr;
    QScrollBar* encountersScrollBar = nullptr;

    // All encounters for the encounter types
    std::vector<Encounter> listOfEncounters;

    // Stores all buttons of encounters
    std::vector<QPushButton*> listOfEncountersButtons;
}

// Sets all pointers to the UI items on encounters page
void EncountersPage::SetUIItemsEncounters(QWidget& mainWindow) {
    encounters = mainWindow.findChild<QGroupBox*>("Encounters");
    backToEncounterTypesPageButton = mainWindow.findChild<QPushButton*>("BackToEncounterTypesPageButton");
    encountersBackgroundWallpaper = mainWindow.findChild<QLabel*>("EncountersBackgroundWallpaper");
    encountersGroupBox = mainWindow.findChild<QGroupBox*>("EncountersGroupBox");
    encountersBox = mainWindow.findChild<QGroupBox*>("EncountersBox");
    getRandomEncounterButton = mainWindow.findChild<QPushButton*>("GetRandomEncounter");
    switchToCreateEncounterButton = mainWindow.findChild<QPushButton*>("SwitchToCreateEncounterButton");
    encountersScrollBar = mainWindow.findChild<QScrollBar*>("EncountersScrollBar");

    /*encountersScrollBar->setValue(0);*/
    encountersGroupBox->setFixedSize(encountersBox->width(), encountersBox->height());

    Window::windowDNDRandomEncounter->connect(getRandomEncounterButton, &QPushButton::clicked, &mainWindow, &GetRandomEncounter);
}

// Resizes encounters page when window size changes
void EncountersPage::ResizeEncounters(QResizeEvent* event) {
    // Update the size of the encounters page
    encounters->resize(event->size());

    // Update the size of the background wallpaper
    encountersBackgroundWallpaper->resize(event->size());

    // Calculate the size of the encountersGroupBox
    int groupBoxWidth = static_cast<int>(encountersBackgroundWallpaper->width() * 0.9);
    int groupBoxHeight = static_cast<int>(encountersBackgroundWallpaper->height() * 0.8);
    encountersBox->setFixedSize(groupBoxWidth, groupBoxHeight);
    encountersGroupBox->setFixedSize(groupBoxWidth, listOfEncounters.size() * 100);

    // Calculate the position of the encountersGroupBox
    int groupBoxX = (encountersBackgroundWallpaper->width() - groupBoxWidth) / 2;
    int groupBoxY = (encountersBackgroundWallpaper->height() - groupBoxHeight) / 1.3;
    encountersBox->move(groupBoxX, groupBoxY);

    // Calculate the size and position of the backToEncounterTypesPageButton
    int buttonX = static_cast<int>(encountersBackgroundWallpaper->width() * 0.05);
    int buttonY = static_cast<int>(encountersBackgroundWallpaper->height() * 0.05);
    backToEncounterTypesPageButton->move(buttonX, buttonY);

    // Calculate the size and position of the encountersScrollBar
    encountersScrollBar->move(encountersBox->width() - encountersScrollBar->width(), 0);
    encountersScrollBar->setFixedHeight(static_cast<int>(encountersBox->height()));

    SetupScrollBar();

    // Resize the encounters buttons
    ResizeEncountersButtons(event);
}

void EncountersPage::SetupScrollBar() {
    encountersScrollBar->move(encountersBox->width() - encountersScrollBar->width(), 0);
    encountersScrollBar->setFixedHeight(static_cast<int>(encountersBox->height()));

    // Update the range of the scrollbar
    encountersScrollBar->setMaximum(encountersGroupBox->height() - encountersBox->height());
    encountersScrollBar->setMinimum(0);

    encountersScrollBar->setMinimumHeight(encountersScrollBar->width() * 0.6);
}

void EncountersPage::ResizeEncountersButtons(QResizeEvent* event) {
    for (int iteration = 0; iteration < listOfEncountersButtons.size(); iteration++) {
        int xPos = 0;
        int yPos = iteration * (100 + 100 * 0.045);

        int buttonHeight = 100;
        listOfEncountersButtons[iteration]->setGeometry(xPos, yPos, encountersGroupBox->width() - 10, buttonHeight);
    }
}


void EncountersPage::GetRandomEncounter() {
    if (listOfEncounters.size() > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, listOfEncounters.size() - 1);
        int v1 = distribution(gen);

        int encounterId = listOfEncounters[v1].ID;

        Window::windowDNDRandomEncounter->SwitchPageToEncounter(encounterId);
    }
}