#include "EncounterTypesPage.h"

namespace EncounterTypesPage {
    // Each item is an item made on the ui
    QGroupBox* encounterTypes = nullptr;
    QLabel* encounterTypesWallpaper = nullptr;
    QGroupBox* encounterTypesGroupBox = nullptr;
    QGroupBox* encounterTypesBox = nullptr;
    QPushButton* backToMainMenu = nullptr;
    QPushButton* switchToCreateEncounterType = nullptr;
    QPushButton* encounterTypesSwipeButton = nullptr;
    QScrollBar* encounterTypesScrollBar = nullptr;

    // Width of each button size
    int buttonWidth = 500;

    // Stores an EncounterType version of each encounter type loaded from the DB at the start of the application
    std::vector<EncounterType> encounterTypesFromDB;

    /*
        Stores a pointer to each encounter type button made for each EncounterType from the DB
        Stored so resizing is possible
    */
    std::vector<QPushButton*> encounterTypesButtons;

    std::vector<QPixmap> buttonPixmaps;
}

// Sets all pointers to the UI items on single encounters type page
void EncounterTypesPage::SetUIItemsEncounterTypes(QWidget& mainWindow) {
    encounterTypes = mainWindow.findChild<QGroupBox*>("EncounterTypes");
    encounterTypesWallpaper = mainWindow.findChild<QLabel*>("EncounterTypesWallpaper");
    encounterTypesGroupBox = mainWindow.findChild<QGroupBox*>("EncounterTypesGroupBox");
    encounterTypesBox = mainWindow.findChild<QGroupBox*>("EncounterTypesBox");
    encounterTypesSwipeButton = mainWindow.findChild<QPushButton*>("EncounterTypesSwipeButton");
    switchToCreateEncounterType = mainWindow.findChild<QPushButton*>("SwitchToCreateEncounterType");
    backToMainMenu = mainWindow.findChild<QPushButton*>("BackToMainMenu");
    encounterTypesScrollBar = mainWindow.findChild<QScrollBar*>("EncounterTypesScrollBar");

    encounterTypesScrollBar->setMaximum(encounterTypesGroupBox->width());
}

void EncounterTypesPage::SetupEncounterTypesPixmap() {
    for (const auto& encounterType : encounterTypesFromDB) {
        QPixmap pixmap;
        pixmap.loadFromData(encounterType.imageData);
        buttonPixmaps.push_back(pixmap);
    }
}

// Resizes everything in the encounter types page when the window is resized
void EncounterTypesPage::resizeEncounterTypes(QResizeEvent* event) {
    QSize newSize = event->size();

    // Resize wallpaper and encounterTypes to match window size
    encounterTypes->setFixedSize(newSize);
    encounterTypesWallpaper->setFixedSize(newSize);

    // Calculate dimensions based on the new size
    int groupBoxWidth = static_cast<int>(newSize.width() * 0.9);
    int groupBoxHeight = static_cast<int>(newSize.height() * 0.5);

    // Set size and position of encounterTypesBox
    encounterTypesBox->setFixedSize(groupBoxWidth, groupBoxHeight);
    encounterTypesBox->move((newSize.width() - groupBoxWidth) / 2, (newSize.height() - groupBoxHeight) / 1.2);

    encounterTypesGroupBox->setFixedSize(encounterTypesFromDB.size() * 500 + 500, groupBoxHeight);

    // Calculate button dimensions
    int buttonHeight = static_cast<int>(groupBoxHeight * 0.9);

    // Set size and position of backToMainMenu button
    int backToMainMenuButtonWidth = static_cast<int>(newSize.width() * 0.3);
    int backToMainMenuButtonHeight = static_cast<int>(newSize.height() * 0.1);
    backToMainMenu->setFixedSize(backToMainMenuButtonWidth, backToMainMenuButtonHeight);
    backToMainMenu->move(static_cast<int>(newSize.width() * 0.05), static_cast<int>(newSize.height() * 0.05));

    // Set font size for backToMainMenu button
    backToMainMenu->setFont(QFont("Arial", static_cast<int>(backToMainMenuButtonWidth * 0.05), QFont::Bold));

    // Set size and position of switchToCreateEncounterType button
    switchToCreateEncounterType->setFixedSize(static_cast<int>(newSize.width() * 0.07), static_cast<int>(newSize.height() * 0.07));
    switchToCreateEncounterType->move(static_cast<int>(newSize.width() * 0.875), static_cast<int>(newSize.height() * 0.325));
    switchToCreateEncounterType->setFont(QFont("Arial", static_cast<int>(backToMainMenuButtonWidth * 0.07), QFont::Bold));

    int encounterTypesScrollBarWidth = static_cast<int>(newSize.width() * 0.9);

    encounterTypesScrollBar->setFixedWidth(encounterTypesScrollBarWidth);
    encounterTypesScrollBar->move((newSize.width() - encounterTypesScrollBar->width()) / 2, (newSize.height() - encounterTypesScrollBar->height()) * 0.9);

    encounterTypesScrollBar->setMaximum((encounterTypesFromDB.size() * buttonWidth) - encounterTypesBox->width());

    qDebug() << encounterTypesScrollBar->maximum() << "Maximum";
    qDebug() << encounterTypesGroupBox->width() << "Width";
    qDebug() << encounterTypesBox->width() << "Width";
    qDebug() << encounterTypesButtons[0]->width() << "Width";
    qDebug() << encounterTypesScrollBar->value() << "Value";

    UpdateEachEncounterTypeButtonPixmap();
}

void EncounterTypesPage::UpdateEachEncounterTypeButtonPixmap() {
    int groupBoxHeight = static_cast<int>(encounterTypesWallpaper->height() * 0.5);
    int buttonHeight = static_cast<int>(groupBoxHeight * 0.9);

    // Update each button
    for (int i = 0; i < encounterTypesButtons.size(); i++) {
        int xPos = i * (buttonWidth + 10) + 10;
        int yPos = static_cast<int>(groupBoxHeight * 0.02);

        // Set position and size of the button
        encounterTypesButtons[i]->move(xPos, yPos);
        encounterTypesButtons[i]->setFixedSize(buttonWidth, buttonHeight);

        // Set cached pixmap for button icon
        QIcon icon(buttonPixmaps[i]);
        QSize iconSize(buttonWidth * 2, buttonHeight * 2);
        icon.actualSize(iconSize);
        encounterTypesButtons[i]->setIcon(icon);
        encounterTypesButtons[i]->setIconSize(iconSize);
    }
}

void EncounterTypesPage::AddNewEncounterTypeButton(QString name, QByteArray imageData) {
    QPushButton* newButton = new QPushButton(name, encounterTypesGroupBox);

    // Load pixmap and set it as the button icon
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    QIcon icon(pixmap);
    QSize iconSize(buttonWidth * 2, newButton->height() * 2);  // Adjust as needed
    icon.actualSize(iconSize);
    newButton->setIcon(icon);
    newButton->setIconSize(iconSize);

    int selectedEncounterType = encounterTypesButtons.size() + 1;

    // Connect signals to slots for the new button
    Window::windowDNDRandomEncounter->connect(newButton, &QPushButton::pressed, Window::windowDNDRandomEncounter, &DNDRandomEncounter::ButtonPressed);
    Window::windowDNDRandomEncounter->connect(newButton, &QPushButton::released, Window::windowDNDRandomEncounter, [selectedEncounterType]() {
        // Handle released event for the new button
        // You can use 'name' to identify the specific encounter type
        Window::windowDNDRandomEncounter->ButtonReleased(selectedEncounterType);
        });

    newButton->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    QString imageStyleSheet = QString("QPushButton { "
        "border: none; "
        "background-image: url('data:image/png;base64,%1'); "
        "background-position: center; "
        "background-repeat: no-repeat; "
        "background-attachment: scroll; "
        "background-origin: content; "
        "background-clip: border; "
        "background-size: cover; "
        "background-color:#5F5D5C; "
        "}").arg(QString(imageData.toBase64()));
    newButton->setStyleSheet(imageStyleSheet);

    newButton->setMinimumSize(buttonWidth, encounterTypesGroupBox->height());


    // Set the geometry of the new button
    int xPos = encounterTypesButtons.empty() ? 10 : encounterTypesButtons.back()->x() + buttonWidth + 10;
    int yPos = encounterTypesGroupBox->height() * 0.05;
    newButton->setGeometry(xPos, yPos, buttonWidth, encounterTypesGroupBox->height() * 0.9);

    // Show the new button
    newButton->show();

    // Update the button lists
    encounterTypesButtons.push_back(newButton);
    buttonPixmaps.push_back(pixmap);

    // Create and add the new encounter type
    EncounterType newEncounterType;
    newEncounterType.SetID(selectedEncounterType);
    newEncounterType.SetName(name);
    newEncounterType.SetImage(imageData);
    encounterTypesFromDB.push_back(newEncounterType);

    // Adjust the scrollbar maximum
    encounterTypesScrollBar->setMaximum(encounterTypesGroupBox->width() - encounterTypesBox->width());

    UpdateEachEncounterTypeButtonPixmap();
}