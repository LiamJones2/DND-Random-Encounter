#include "CreateEncounterTypePage.h"

namespace CreateEncounterTypePage {
    // Each item is an item made on the ui
    QGroupBox* creatEncounterTypeBox = nullptr;
    QLabel* createSingleEncounterWallpaper = nullptr;
    QPushButton* backToEncounterTypes = nullptr;
    QPushButton* createEncounterTypeButton = nullptr;
    QLineEdit* createEncounterTypeNameInput = nullptr;
    QLabel* createEncounterTypeImageInput = nullptr;
    QPushButton* uploadEncounterTypeImage = nullptr;
}

// Sets all pointers to the UI items on single encounters type page
void CreateEncounterTypePage::SetUIItemsCreateEncounterType(QWidget& mainWindow) {
    creatEncounterTypeBox = mainWindow.findChild<QGroupBox*>("CreateEncounterTypePageBox");
    createSingleEncounterWallpaper = mainWindow.findChild<QLabel*>("CreateEncounterTypeWallpaper");
    createEncounterTypeNameInput = mainWindow.findChild<QLineEdit*>("CreateEncounterTypeNameInput");
    createEncounterTypeImageInput = mainWindow.findChild<QLabel*>("CreateEncounterTypeImageInput");
    createEncounterTypeButton = mainWindow.findChild<QPushButton*>("CreateEncounterTypeButton");
    backToEncounterTypes = mainWindow.findChild<QPushButton*>("BackToEncounterType");
    uploadEncounterTypeImage = mainWindow.findChild<QPushButton*>("UploadEncounterTypeImage");
}

// Resizes everything in the encounter types page when the window is resized
void CreateEncounterTypePage::ResizeCreateEncounterType(QResizeEvent* event) {
    // Width of each button size
    int buttonWidth = 500;

    creatEncounterTypeBox->setFixedSize(event->size());
    // Sets wallpaper and page groupbox to full size of window
    createSingleEncounterWallpaper->setFixedSize(event->size());

    int backToEncounterTypesWidth = (createSingleEncounterWallpaper->width() - backToEncounterTypes->width()) * 0.3;
    int backToEncounterTypesHeight = (createSingleEncounterWallpaper->height() - backToEncounterTypes->height()) * 0.1;
    backToEncounterTypes->setFixedSize(backToEncounterTypesWidth, backToEncounterTypesHeight);

    int backToEncounterTypesX = (createSingleEncounterWallpaper->width() - backToEncounterTypes->width()) * 0.05;
    int backToEncounterTypesY = (createSingleEncounterWallpaper->height() - backToEncounterTypes->height()) * 0.05;
    backToEncounterTypes->move(backToEncounterTypesX, backToEncounterTypesY);

    int backToEncounterTypesFontSize = static_cast<int>(backToEncounterTypes->width() * 0.05);

    QFont backToEncounterTypesFont("Arial", backToEncounterTypesFontSize, QFont::Bold);

    backToEncounterTypes->setFont(backToEncounterTypesFont);


    int createEncounterTypeButtonWidth = (createSingleEncounterWallpaper->width() - createEncounterTypeButton->width()) * 0.3;
    int createEncounterTypeButtonHeight = (createSingleEncounterWallpaper->height() - createEncounterTypeButton->height()) * 0.1;
    createEncounterTypeButton->setFixedSize(createEncounterTypeButtonWidth, createEncounterTypeButtonHeight);

    int createEncounterTypeButtonX = (createSingleEncounterWallpaper->width() - createEncounterTypeButton->width()) * 0.5;
    int createEncounterTypeButtonY = (createSingleEncounterWallpaper->height() - createEncounterTypeButton->height()) * 0.9;
    createEncounterTypeButton->move(createEncounterTypeButtonX, createEncounterTypeButtonY);

    int createEncounterTypeButtonFontSize = static_cast<int>(createEncounterTypeButton->width() * 0.05);

    QFont createEncounterTypeButtonFont("Arial", createEncounterTypeButtonFontSize, QFont::Bold);

    createEncounterTypeButton->setFont(createEncounterTypeButtonFont);


    int createEncounterTypeNameInputWidth = (createSingleEncounterWallpaper->width() - createEncounterTypeNameInput->width()) * 0.3;
    int createEncounterTypeNameInputHeight = (createSingleEncounterWallpaper->height() - createEncounterTypeNameInput->height()) * 0.05;
    createEncounterTypeNameInput->setFixedSize(createEncounterTypeNameInputWidth, createEncounterTypeNameInputHeight);

    int createEncounterTypeNameInputX = (createSingleEncounterWallpaper->width() - createEncounterTypeNameInput->width()) * 0.5;
    int createEncounterTypeNameInputY = (createSingleEncounterWallpaper->height() - createEncounterTypeNameInput->height()) * 0.2;
    createEncounterTypeNameInput->move(createEncounterTypeNameInputX, createEncounterTypeNameInputY);
}

void CreateEncounterTypePage::ChangeEncounterTypeImage(QWidget& mainWindow) {
    try {
        QString fileName = QFileDialog::getOpenFileName(&mainWindow, QObject::tr("Choose"), "", QObject::tr("Images (*.png *.jpg *.jpeg *.webp)"));

        if (!fileName.isEmpty()) {
            qDebug() << "Selected file:" << fileName;

            QImage image;
            bool valid = image.load(fileName);

            if (valid) {
                qDebug() << "Image loaded successfully.";
                createEncounterTypeImageInput->setPixmap(QPixmap::fromImage(image));
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

bool CreateEncounterTypePage::CheckEncounterTypeImageValidation() {
    QPixmap pixmap = createEncounterTypeImageInput->pixmap();

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

bool CreateEncounterTypePage::CheckEncounterTypeNameValidation() {
    qDebug() << createEncounterTypeNameInput->text().length();
    if (createEncounterTypeNameInput->text().length() > 0) return true;
    else return false;
}

bool CreateEncounterTypePage::CheckEncounterTypeValidation() {
    bool valid = true;
    if (CheckEncounterTypeImageValidation() == false) valid = false;
    if (CheckEncounterTypeNameValidation() == false) valid = false;

    return valid;
}

void CreateEncounterTypePage::RegisterEncounterType() {
    if (CheckEncounterTypeValidation()) {
        QString inputName = createEncounterTypeNameInput->text();

        QPixmap imagePixmap = createEncounterTypeImageInput->pixmap();
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        imagePixmap.save(&buffer, "PNG");
        Database::InsertEncounterTypeToTable(inputName, byteArray);
    }
}