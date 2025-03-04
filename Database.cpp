#include "Database.h"

namespace Database {
	QSqlDatabase db;
}

// Connects database correctly or calls create database if not
void Database::ConnectDatabase() {
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("RandomEncountersDB.db");

	// If we have no db connected to the app then we make one
	if (!db.isOpen()) {
		CreateDatabase();
	}
}

void Database::CreateDatabase() {
	// Drops database tables if exist to reset tables
	DropEncountersTable();
	DropEncounterTypesTable();

	// Creates new tables
	CreateEncounterTypesTable();
	CreateEncountersTable();
}

void Database::DropEncountersTable() {
	// Prepares drop encounters table query
	QSqlQuery dropEncounterQuery;
	dropEncounterQuery.prepare("DROP TABLE IF EXISTS Encounters");

	// Runs query to drop encounters table
	if (dropEncounterQuery.exec()) {
		qDebug() << "Table dropped successfully";
	}
	else {
		qDebug() << "Error creating table:" << dropEncounterQuery.lastError().text();
	}
}

void Database::DropEncounterTypesTable() {
	// Prepares drop encounter types table query
	QSqlQuery dropEncounterTypeQuery;
	dropEncounterTypeQuery.prepare("DROP TABLE IF EXISTS EncounterType");

	// Runs query to drop encounter types table
	if (dropEncounterTypeQuery.exec()) {
		qDebug() << "Table dropped successfully";
	}
	else {
		qDebug() << "Error creating table:" << dropEncounterTypeQuery.lastError().text();
	}
}

void Database::CreateEncounterTypesTable() {
	// Prepares query to create encounter types table with correct datatypes
	QSqlQuery query;
	query.prepare("CREATE TABLE IF NOT EXISTS EncounterType (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name NVARCHAR(255), ImageData BLOB)");

	// Runs query to create encounter types table
	if (query.exec()) {
		qDebug() << "Table created successfully";
	}
	else {
		qDebug() << "Error creating table:" << query.lastError().text();
	}
}

void Database::CreateEncountersTable() {
	// Prepares query to create encounters table with correct datatypes
	QSqlQuery query2;
	query2.prepare("CREATE TABLE IF NOT EXISTS Encounters ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"EncounterTypeID INTEGER,"
		"Name NVARCHAR(255),"
		"Description TEXT,"
		"ImageData BLOB,"
		"FOREIGN KEY (EncounterTypeID) REFERENCES EncounterType(ID)"
		")");

	// Runs query to create encounters table
	if (query2.exec()) {
		qDebug() << "Table created successfully";
	}
	else {
		qDebug() << "Error creating table:" << query2.lastError().text();
	}
}

void Database::GetEncounterTypes(DNDRandomEncounter& randomEncounter) {
	// Check if the database opened successfully
	if (db.open()) {

		// Creates query to get all data from Encounter Types and stores them
		QSqlQuery query;
		query.prepare("SELECT * FROM EncounterType");

		if (query.exec()) {
			while (query.next()) {
				// Gets the name, id and image from each Encounter type
				QString columnName = query.value("Name").toString();
				int columnID = query.value("id").toInt();
				QByteArray imageData = query.value("ImageData").toByteArray();

				// Creates instance of EncounterType to store each encounter type
				EncounterType newEncounterType;
				newEncounterType.SetID(columnID);
				newEncounterType.SetName(columnName);
				newEncounterType.SetImage(imageData);

				EncounterTypesPage::encounterTypesFromDB.push_back(newEncounterType);
			}
		}
	}
	else {
		// Creates table if database cannot be accessed
		CreateDatabase();
	}
}

void Database::GetEncounters() {
	// Clears listOfEncounters to prevent memory leak
	EncountersPage::listOfEncounters.clear();

	// Check if the database opened successfully
	if (Database::db.open()) {
		// Prepares query to get all encounters from a certain encounter types id
		QSqlQuery query;
		QString getEncountersQuery = "SELECT * FROM Encounters WHERE EncounterTypeID = :encounterTypeID";
		query.prepare(getEncountersQuery);
		query.bindValue(":encounterTypeID", selectedEncounterType.viewEncounterTypeID);

		if (query.exec()) {
			while (query.next()) {
				// Gets the name, id and description from each Encounter in that shares the encounter type id
				QString columnName = query.value("Name").toString();
				int columnID = query.value("ID").toInt();
				QString columnDescription = query.value("Description").toString();

				// Creates Encounter instance to store each encounter of that encounter type id
				Encounter newEncounter;
				newEncounter.SetID(columnID);
				newEncounter.SetName(columnName);
				newEncounter.SetDescription(columnDescription);

				EncountersPage::listOfEncounters.push_back(newEncounter);
			}
		}
	}
}

void Database::GetSingleEncounter(int id) {
	// Check if the database opened successfully
	if (db.open()) {
		// Prepares query to get all data from a certain encounter by its id
		QSqlQuery query;
		QString getEncountersQuery = "SELECT * FROM Encounters WHERE ID = :encounterID";
		query.prepare(getEncountersQuery);
		query.bindValue(":encounterID", id);

		if (query.exec()) {
			while (query.next()) {
				// Gets id, name, description and image of the encounter to be shown on single encounter page
				SelectedEncounterNamespace::selectedEncounter.SetName(query.value("Name").toString());
				SelectedEncounterNamespace::selectedEncounter.SetID(query.value("ID").toInt());
				SelectedEncounterNamespace::selectedEncounter.SetDescription(query.value("Description").toString());
				SelectedEncounterNamespace::selectedEncounter.SetImage(query.value("ImageData").toByteArray());
			}
		}
	}
}

void Database::InsertEncounterTypeToTable(QString& name, QByteArray& byteArray) {
	// Check if the database opened successfully
	if (db.open()) {
		// Prepares query to get all data from a certain encounter by its id

		qDebug() << name;

		QSqlQuery query;
		query.prepare("INSERT INTO EncounterType (Name, ImageData) VALUES (?, ?)");

		query.bindValue(0, name);
		query.bindValue(1, QVariant(byteArray));

		if (query.exec()) {
			qDebug() << "Data inserted successfully";
			EncounterTypesPage::AddNewEncounterTypeButton(name, byteArray);
		}
		else {
			qDebug() << "Error inserting data:" << query.lastError().text();
		}
	}
}

void Database::InsertSingleEncounterToTable(int encounterTypeID, QString& name, QByteArray& byteArray, QString& description) {
	if (db.open()) {
		// Prepares query to get all data from a certain encounter by its id

		QSqlQuery query;
		query.prepare("INSERT INTO Encounters (EncounterTypeID, Name, Description, ImageData) VALUES (:encounterTypeID, :name, :description, :imageData )");

		query.bindValue(":encounterTypeID", encounterTypeID);
		query.bindValue(":name", name);
		query.bindValue(":description", description);
		query.bindValue(":imageData", QVariant(byteArray));

		if (query.exec()) {
			qDebug() << "Data inserted successfully";
		}
		else {
			qDebug() << "Error inserting data:" << query.lastError().text();
		}
	}
}