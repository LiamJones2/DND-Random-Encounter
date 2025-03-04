#include "SingleEncounterPage.h"

// Stores all aspects of Encounter Types page
namespace SingleEncounterPage {
	QLabel* singleEncounterBackgroundWallpaper;
	QGroupBox* singleEncounterBox;
	QLabel* encounterName;
	QLabel* encounterDescription;
	QLabel* encounterImage;
	QPushButton* backToEncountersPageButton;
}

// Sets all pointers to the UI items on single encounter page
void SingleEncounterPage::setSingleEncounterUIItems(QWidget& mainWindow) {
	singleEncounterBackgroundWallpaper = mainWindow.findChild<QLabel*>("SingleEncounterBackgroundWallpaper");
	singleEncounterBox = mainWindow.findChild<QGroupBox*>("SingleEncounterBox");
	backToEncountersPageButton = mainWindow.findChild<QPushButton*>("BackToEncountersPageButton");
	encounterName = mainWindow.findChild<QLabel*>("EncounterName");
	encounterDescription = mainWindow.findChild<QLabel*>("EncounterDescription");
	encounterImage = mainWindow.findChild<QLabel*>("EncounterImage");
}

// Changes UI items to show certain encounter info 
void SingleEncounterPage::setupSingleEncounterPage() {
	SingleEncounterPage::encounterName->setText(SelectedEncounterNamespace::selectedEncounter.name);
	SingleEncounterPage::encounterDescription->setText(SelectedEncounterNamespace::selectedEncounter.description);

	QPixmap pixmap;
	pixmap.loadFromData(SelectedEncounterNamespace::selectedEncounter.imageData);
	SingleEncounterPage::encounterImage->setPixmap(pixmap);
	SingleEncounterPage::encounterImage->setScaledContents(true);
}

// Resizes UI items when window size changes
void SingleEncounterPage::resizeSingleEncounter(QResizeEvent* event) {
	singleEncounterBackgroundWallpaper->setFixedSize(event->size());
	singleEncounterBox->setFixedSize(event->size());

	int nameWidth = static_cast<int>(singleEncounterBackgroundWallpaper->width() * 0.2);
	int nameHeight = static_cast<int>(singleEncounterBackgroundWallpaper->height() * 0.05);
	encounterName->setFixedSize(nameWidth, nameHeight);

	int nameX = (singleEncounterBackgroundWallpaper->width() - nameWidth) / 2;
	int nameY = (singleEncounterBackgroundWallpaper->height() - nameHeight) / 14;
	encounterName->setGeometry(nameX, nameY, singleEncounterBackgroundWallpaper->width(), singleEncounterBackgroundWallpaper->height() * 0.2);

	int newNameFontSize = static_cast<int>(singleEncounterBackgroundWallpaper->width() * 0.01);
	QFont nameFont("Arial", newNameFontSize, QFont::Bold);
	encounterName->setFont(nameFont);

	int descriptionWidth = static_cast<int>(singleEncounterBackgroundWallpaper->width() * 0.4);
	int descriptionHeight = static_cast<int>(singleEncounterBackgroundWallpaper->height() * 0.6);
	encounterDescription->setGeometry(descriptionWidth, descriptionHeight, singleEncounterBackgroundWallpaper->width() * 0.4, singleEncounterBackgroundWallpaper->height() * 0.6);

	int newDescriptionFontSize = static_cast<int>(singleEncounterBackgroundWallpaper->width() * 0.01);
	QFont descriptionFont("Arial", newDescriptionFontSize);
	encounterDescription->setFont(descriptionFont);

	int descriptionX = (singleEncounterBackgroundWallpaper->width() - nameWidth) / 8;
	int descriptionY = (singleEncounterBackgroundWallpaper->height() - nameHeight) / 5;
	encounterDescription->move(descriptionX, descriptionY);

	int imageWidth = static_cast<int>(singleEncounterBackgroundWallpaper->width() * 0.3);
	int imageHeight = static_cast<int>(singleEncounterBackgroundWallpaper->height() * 0.7);
	encounterImage->setFixedSize(imageWidth, imageHeight);

	int imageX = (singleEncounterBackgroundWallpaper->width() - nameWidth) / 1.4;
	int imageY = (singleEncounterBackgroundWallpaper->height() - nameHeight) / 6;
	encounterImage->move(imageX, imageY);

	int backToEncountersPageButtonX = (singleEncounterBackgroundWallpaper->width() - backToEncountersPageButton->width()) * 0.05;
	int backToEncountersPageButtonY = (singleEncounterBackgroundWallpaper->height() - backToEncountersPageButton->height()) * 0.05;
	backToEncountersPageButton->move(backToEncountersPageButtonX, backToEncountersPageButtonY);

	int backToEncountersPageButtonWidth = (singleEncounterBackgroundWallpaper->width() - backToEncountersPageButton->width()) * 0.3;
	int backToEncountersPageButtonHeight = (singleEncounterBackgroundWallpaper->height() - backToEncountersPageButton->height()) * 0.1;
	backToEncountersPageButton->setFixedSize(backToEncountersPageButtonWidth, backToEncountersPageButtonHeight);

	int backToEncountersPageButtonFontSize = static_cast<int>(backToEncountersPageButton->width() * 0.05);

	QFont backToEncountersPageButtonFont("Arial", backToEncountersPageButtonFontSize, QFont::Bold);

	backToEncountersPageButton->setFont(backToEncountersPageButtonFont);
}