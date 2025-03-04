#include "MainMenuPage.h"

namespace MainMenuPage {
    QGroupBox* mainMenu = nullptr;
    QLabel* backgroundWallpaper = nullptr;
    QLabel* titleBackground = nullptr;
    QLabel* titleText = nullptr;
    QPushButton* closeButton = nullptr;
    QPushButton* startButton = nullptr;
}

void MainMenuPage::SetMainMenuUIItems(QWidget& mainWindow) {
    mainMenu = mainWindow.findChild<QGroupBox*>("MainMenu");
    backgroundWallpaper = mainWindow.findChild<QLabel*>("BackgroundWallpaper");
    titleBackground = mainWindow.findChild<QLabel*>("TitleBackground");
    titleText = mainWindow.findChild<QLabel*>("TitleText");
    closeButton = mainWindow.findChild<QPushButton*>("exitButton");
    startButton = mainWindow.findChild<QPushButton*>("startButton");
}

void MainMenuPage::ResizeMainMenu(QResizeEvent* event) {
    mainMenu->setFixedSize(event->size());

    backgroundWallpaper->setFixedSize(event->size());

    MainMenuPage::titleBackground->move(MainMenuPage::backgroundWallpaper->width() * 0.65, MainMenuPage::titleBackground->y());
    MainMenuPage::titleBackground->setFixedSize(MainMenuPage::backgroundWallpaper->width() * 0.3, MainMenuPage::backgroundWallpaper->height() * 0.3);

    int centerX = MainMenuPage::titleBackground->x() + MainMenuPage::titleBackground->width() / 2;
    int centerY = MainMenuPage::titleBackground->y() + MainMenuPage::titleBackground->height() / 2;

    int textX = centerX - MainMenuPage::titleBackground->width() / 2;
    int textY = centerY - MainMenuPage::titleBackground->height() * 0.2 / 2;

    // Set the position and size of titleText
    MainMenuPage::titleText->setGeometry(textX, textY, MainMenuPage::titleBackground->width(), MainMenuPage::titleBackground->height() * 0.2);

    int newFontSize = static_cast<int>(MainMenuPage::titleBackground->width() * 0.05);

    QFont font("Arial", newFontSize, QFont::Bold);

    MainMenuPage::titleText->setFont(font);
}
