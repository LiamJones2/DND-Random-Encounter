#include "CreateSingleEncounterPage.h"

namespace CreateSingleEncounterPage {
	// Each item is an item made on the ui
	QGroupBox* createSingleEncounterBox = nullptr;
	QLabel* createSingleEncounterWallpaper = nullptr;
	QPushButton* backToEncountersButton = nullptr;
	QPushButton* createSingleEncounterButton = nullptr;
	QLineEdit* createSingleEncounterNameInput = nullptr;
	QLabel* createSingleEncounterImageInput = nullptr;
	QPushButton* uploadSingleEncounterImage = nullptr;
}

// Sets all pointers to the UI items on single encounters type page
void CreateSingleEncounterPage::SetUIItemsCreateSingleEncounter(QWidget& mainWindow) {
	createSingleEncounterBox = mainWindow.findChild<QGroupBox*>("CreateEncounterTypePageBox");
	createSingleEncounterWallpaper = mainWindow.findChild<QLabel*>("CreateEncounterTypeWallpaper");
	backToEncountersButton = mainWindow.findChild<QPushButton*>("BackToEncounterType");
	createSingleEncounterButton = mainWindow.findChild<QPushButton*>("createSingleEncounterButton");
	createSingleEncounterNameInput = mainWindow.findChild<QLineEdit*>("createSingleEncounterNameInput");
	createSingleEncounterImageInput = mainWindow.findChild<QLabel*>("createSingleEncounterImageInput");
	uploadSingleEncounterImage = mainWindow.findChild<QPushButton*>("UploadEncounterTypeImage");
}

// Resizes everything in the encounter types page when the window is resized
void CreateSingleEncounterPage::ResizeCreateSingleEncounter(QResizeEvent* event) {
	// Width of each button size
	int buttonWidth = 500;

	createSingleEncounterBox->setFixedSize(event->size());
	// Sets wallpaper and page groupbox to full size of window
	createSingleEncounterWallpaper->setFixedSize(event->size());

	int backToEncountersButtonWidth = (createSingleEncounterWallpaper->width() - backToEncountersButton->width()) * 0.3;
	int backToEncountersButtonHeight = (createSingleEncounterWallpaper->height() - backToEncountersButton->height()) * 0.1;
	backToEncountersButton->setFixedSize(backToEncountersButtonWidth, backToEncountersButtonHeight);

	int backToEncountersButtonX = (createSingleEncounterWallpaper->width() - backToEncountersButton->width()) * 0.05;
	int backToEncountersButtonY = (createSingleEncounterWallpaper->height() - backToEncountersButton->height()) * 0.05;
	backToEncountersButton->move(backToEncountersButtonX, backToEncountersButtonY);

	int backToEncountersButtonFontSize = static_cast<int>(backToEncountersButton->width() * 0.05);

	QFont backToEncountersButtonFont("Arial", backToEncountersButtonFontSize, QFont::Bold);

	backToEncountersButton->setFont(backToEncountersButtonFont);


	int createSingleEncounterButtonWidth = (createSingleEncounterWallpaper->width() - createSingleEncounterButton->width()) * 0.3;
	int createSingleEncounterButtonHeight = (createSingleEncounterWallpaper->height() - createSingleEncounterButton->height()) * 0.1;
	createSingleEncounterButton->setFixedSize(createSingleEncounterButtonWidth, createSingleEncounterButtonHeight);

	int createSingleEncounterButtonX = (createSingleEncounterWallpaper->width() - createSingleEncounterButton->width()) * 0.5;
	int createSingleEncounterButtonY = (createSingleEncounterWallpaper->height() - createSingleEncounterButton->height()) * 0.9;
	createSingleEncounterButton->move(createSingleEncounterButtonX, createSingleEncounterButtonY);

	int createSingleEncounterButtonFontSize = static_cast<int>(createSingleEncounterButton->width() * 0.05);
	QFont createSingleEncounterButtonFont("Arial", createSingleEncounterButtonFontSize, QFont::Bold);
	createSingleEncounterButton->setFont(createSingleEncounterButtonFont);

	int createSingleEncounterNameInputWidth = (createSingleEncounterWallpaper->width() - createSingleEncounterNameInput->width()) * 0.3;
	int createSingleEncounterNameInputHeight = (createSingleEncounterWallpaper->height() - createSingleEncounterNameInput->height()) * 0.05;
	createSingleEncounterNameInput->setFixedSize(createSingleEncounterNameInputWidth, createSingleEncounterNameInputHeight);

	int createSingleEncounterNameInputX = (createSingleEncounterWallpaper->width() - createSingleEncounterNameInput->width()) * 0.5;
	int createSingleEncounterNameInputY = (createSingleEncounterWallpaper->height() - createSingleEncounterNameInput->height()) * 0.2;
	createSingleEncounterNameInput->move(createSingleEncounterNameInputX, createSingleEncounterNameInputY);
}

void CreateSingleEncounterPage::ChangeSingleEncounterImage(QWidget& mainWindow) {
	try {
		QString fileName = QFileDialog::getOpenFileName(&mainWindow, QObject::tr("Choose"), "", QObject::tr("Images (*.png *.jpg *.jpeg *.webp)"));

		if (!fileName.isEmpty()) {
			qDebug() << "Selected file:" << fileName;

			QImage image;
			bool valid = image.load(fileName);

			if (valid) {
				qDebug() << "Image loaded successfully.";
				createSingleEncounterImageInput->setPixmap(QPixmap::fromImage(image));
			}
			else {
				qDebug() << "Failed to load image.";
			}
		}
		else {
			qDebug() << "User canceled the file dialog.";
		}
	}
	catch (const std::exception& e) {
		qDebug() << "Caught Error with getting file:" << e.what();
	}
}

bool CreateSingleEncounterPage::CheckSingleEncounterNameValidation() {
	qDebug() << createSingleEncounterNameInput->text().length();
	if (createSingleEncounterNameInput->text().length() > 0) return true;
	else return false;
}

bool CreateSingleEncounterPage::CheckSingleEncounterImageValidation() {
	QPixmap pixmap = createSingleEncounterImageInput->pixmap();

	if (!pixmap.isNull()) {
		qDebug() << "QLabel has a QPixmap.";
		return true;
	}
	else {
		// The QLabel does not have a QPixmap set
		qDebug() << "QLabel does not have a QPixmap.";
		return false;
	}
}

bool CreateSingleEncounterPage::CheckSingleEncounterValidation() {
	return !CheckSingleEncounterImageValidation() || !CheckSingleEncounterNameValidation();
}

void CreateSingleEncounterPage::RegisterSingleEncounter() {
	if (CheckSingleEncounterValidation()) {
		QString inputName = createSingleEncounterNameInput->text();

		QPixmap imagePixmap = createSingleEncounterImageInput->pixmap();
		QByteArray byteArray;
		QBuffer buffer(&byteArray);
		buffer.open(QIODevice::WriteOnly);
		imagePixmap.save(&buffer, "PNG");
		Database::InsertEncounterTypeToTable(inputName, byteArray);
	}
}