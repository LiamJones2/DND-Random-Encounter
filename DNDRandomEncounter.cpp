#include "DNDRandomEncounter.h"

DNDRandomEncounter::DNDRandomEncounter(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	stackedWidget = findChild<QStackedWidget*>("stackedWidget");

	MainMenuPage::SetMainMenuUIItems(*this);
	SingleEncounterPage::setSingleEncounterUIItems(*this);
	EncounterTypesPage::SetUIItemsEncounterTypes(*this);
	EncountersPage::SetUIItemsEncounters(*this);
	CreateEncounterTypePage::SetUIItemsCreateEncounterType(*this);

	Database::ConnectDatabase();
	Database::GetEncounterTypes(*this);

	SetupEncounterTypes();
	EncounterTypesPage::SetupEncounterTypesPixmap();

	connect(MainMenuPage::closeButton, &QPushButton::clicked, this, &DNDRandomEncounter::CloseApp);
	connect(MainMenuPage::startButton, &QPushButton::clicked, this, &DNDRandomEncounter::SwitchPageToEncounterTypes);
	connect(EncountersPage::backToEncounterTypesPageButton, &QPushButton::clicked, this, &DNDRandomEncounter::SwitchPageToEncounterTypes);
	connect(CreateEncounterTypePage::backToEncounterTypes, &QPushButton::clicked, this, &DNDRandomEncounter::SwitchPageToEncounterTypes);
	connect(EncounterTypesPage::backToMainMenu, &QPushButton::clicked, this, &DNDRandomEncounter::SwitchPageToMainMenu);
	connect(EncounterTypesPage::encounterTypesSwipeButton, &QPushButton::clicked, this, &DNDRandomEncounter::OnGroupBoxClicked);
	connect(SingleEncounterPage::backToEncountersPageButton, &QPushButton::clicked, this, &DNDRandomEncounter::SwitchPageToSingleEncounterType);
	connect(EncounterTypesPage::switchToCreateEncounterType, &QPushButton::clicked, this, &DNDRandomEncounter::SwitchPageToCreateEncounterType);
	connect(CreateEncounterTypePage::createEncounterTypeButton, &QPushButton::clicked, this, &DNDRandomEncounter::SubmitInsertEncounterType);
	connect(CreateEncounterTypePage::uploadEncounterTypeImage, &QPushButton::clicked,
		this, [this]() { CreateEncounterTypePage::ChangeEncounterTypeImage(*this); });

	connect(&pressTimer, &QTimer::timeout, this, &DNDRandomEncounter::LongPressDetected);
	connect(EncounterTypesPage::encounterTypesScrollBar, &QScrollBar::valueChanged, this, [this]() { DNDRandomEncounter::UpdateEncounterTypesScrollBar(); });
	connect(EncountersPage::encountersScrollBar, &QScrollBar::valueChanged, this, [this]() { DNDRandomEncounter::UpdateEncountersScrollBar(); });
}

DNDRandomEncounter::~DNDRandomEncounter()
{}

void DNDRandomEncounter::OnGroupBoxClicked() {
	qDebug() << "QGroupBox clicked!";
}

void DNDRandomEncounter::resizeEvent(QResizeEvent* event) {
	stackedWidget->setFixedSize(event->size());

	MainMenuPage::ResizeMainMenu(event);
	EncounterTypesPage::resizeEncounterTypes(event);
	EncountersPage::ResizeEncounters(event);
	SingleEncounterPage::resizeSingleEncounter(event);
	CreateEncounterTypePage::ResizeCreateEncounterType(event);
}

void DNDRandomEncounter::UpdateEncounterTypesScrollBar() {
	int backToMainMenuButtonX = EncounterTypesPage::encounterTypesGroupBox->x();
	int backToMainMenuButtonY = EncounterTypesPage::encounterTypesScrollBar->value();

	EncounterTypesPage::encounterTypesGroupBox->move(backToMainMenuButtonX, -backToMainMenuButtonY);
}

void DNDRandomEncounter::UpdateEncountersScrollBar() {
	int backToMainMenuButtonX = EncountersPage::encountersGroupBox->x(); 
	int backToMainMenuButtonY = EncountersPage::encountersScrollBar->value();

	qDebug() << EncountersPage::encountersScrollBar->value() << "Value";

	EncountersPage::encountersGroupBox->move(backToMainMenuButtonX, -backToMainMenuButtonY);
}

void DNDRandomEncounter::SetupEncounterTypes() {
	int encounterTypeWidth = 500;

	for (int i = 0; i < EncounterTypesPage::encounterTypesFromDB.size(); ++i) {
		int xPos = i * (encounterTypeWidth + encounterTypeWidth * 0.045) + 10;
		int yPos = 0;

		QPushButton* button = new QPushButton("", EncounterTypesPage::encounterTypesGroupBox);
		button->setGeometry(xPos, yPos, encounterTypeWidth, EncounterTypesPage::encounterTypesGroupBox->height());

		QPixmap pixmap;
		pixmap.loadFromData(EncounterTypesPage::encounterTypesFromDB[i].imageData);

		button->setIcon(QIcon(pixmap));

		int selectedEncounterType = EncounterTypesPage::encounterTypesFromDB[i].encounterTypeID;

		connect(button, &QPushButton::pressed, this, &DNDRandomEncounter::ButtonPressed);
		connect(button, &QPushButton::released, this, [this, selectedEncounterType]() {
			ButtonReleased(selectedEncounterType);
			});

		button->show();

		button->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

		QString imageStyleSheet = QString("QPushButton { border: none; background-image: url('data:image/png;base64,%1'); background-position: center; background-repeat: no-repeat; background-attachment: scroll; background-origin: content; background-clip: border; background-size: cover; background-color:#5F5D5C; }").arg(QString(EncounterTypesPage::encounterTypesFromDB[i].imageData.toBase64()));
		button->setStyleSheet(imageStyleSheet);

		button->setMinimumSize(encounterTypeWidth, EncounterTypesPage::encounterTypesGroupBox->height());

		EncounterTypesPage::encounterTypesButtons.push_back(button);

		qDebug() << EncounterTypesPage::encounterTypesFromDB[i].name;
	}
}

void DNDRandomEncounter::SetupEncounters() {
	for (size_t i = 0; i < EncountersPage::listOfEncountersButtons.size(); i++)
	{
		EncountersPage::listOfEncountersButtons[i]->deleteLater();
	}

	EncountersPage::listOfEncountersButtons.clear();

	int encounterTypeWidth = EncountersPage::encountersGroupBox->width() - 20;

	for (int i = 0; i < EncountersPage::listOfEncounters.size(); ++i) {
		int xPos = 0;
		int yPos = i * (100 + 100 * 0.045);

		int buttonHeight = 100;

		QString buttonText = EncountersPage::listOfEncounters[i].name;

		QPushButton* button = new QPushButton("", EncountersPage::encountersGroupBox);
		button->setGeometry(xPos, yPos, encounterTypeWidth, buttonHeight);
		button->show();

		QVBoxLayout* layout = new QVBoxLayout(button);

		QLabel* nameLabel = new QLabel(EncountersPage::listOfEncounters[i].name, button);
		nameLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
		nameLabel->setStyleSheet("color:black;");

		QLabel* descriptionLabel = new QLabel(EncountersPage::listOfEncounters[i].description, button);
		descriptionLabel->setWordWrap(true);
		descriptionLabel->setStyleSheet("color:grey;");

		layout->addWidget(nameLabel);
		layout->addWidget(descriptionLabel);

		button->setLayout(layout);

		int encounterId = EncountersPage::listOfEncounters[i].ID;

		connect(button, &QPushButton::clicked, this, [this, encounterId]() {
			SwitchPageToEncounter(encounterId);
			});

		button->setStyleSheet("QPushButton {"
			"background-color: #fff;"
			"border: 1px solid #4169E1;"
			"color: white;"
			"}");

		button->setMinimumSize(0, 0);
		button->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
		button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		EncountersPage::listOfEncountersButtons.push_back(button);

	}


	EncountersPage::encountersGroupBox->setFixedSize(EncountersPage::encountersGroupBox->width(), EncountersPage::listOfEncountersButtons.size() * 100);

	qDebug() << EncountersPage::encountersGroupBox->x() << "x";
	qDebug() << EncountersPage::encountersGroupBox->y() << "y";
	qDebug() << EncountersPage::encountersBox->x() << "x";
	qDebug() << EncountersPage::encountersBox->y() << "y";
}

void DNDRandomEncounter::CloseApp() {
	QCoreApplication::quit();
}

void DNDRandomEncounter::SwitchPageToEncounterTypes() {
	stackedWidget->setCurrentIndex(1);
}

void DNDRandomEncounter::SwitchPageToMainMenu() {
	stackedWidget->setCurrentIndex(0);
}

void DNDRandomEncounter::SwitchPageToSingleEncounterType() {
	Database::GetEncounters();

	SetupEncounters();
	EncountersPage::SetupScrollBar();

	stackedWidget->setCurrentIndex(2);
}

void DNDRandomEncounter::SwitchPageToEncounter(int id) {
	Database::GetSingleEncounter(id);

	SingleEncounterPage::setupSingleEncounterPage();

	stackedWidget->setCurrentIndex(3);
}

void DNDRandomEncounter::SwitchPageToCreateEncounterType() {
	stackedWidget->setCurrentIndex(4);
}


void DNDRandomEncounter::ButtonPressed() {
	qDebug() << "Button pressed!";

	pressTimer.stop();


	pressTimer.start(100);
}

void DNDRandomEncounter::ButtonReleased(int encounterType) {
	pressTimer.stop();

	qDebug() << "here!";

	if (!clicked) {
		qDebug() << "Button released!";

		selectedEncounterType.viewEncounterTypeID = encounterType;

		SwitchPageToSingleEncounterType();
	}

	clicked = false;
	pressTimer.stop();
}

void DNDRandomEncounter::LongPressDetected() {
	qDebug() << "Long press detected!";

	clicked = true;
}

void DNDRandomEncounter::SubmitInsertEncounterType() {
	CreateEncounterTypePage::RegisterEncounterType();
}