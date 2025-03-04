#pragma once
#include <QSqlDatabase>
#include "DNDRandomEncounter.h"
#include "Encounter.h"
#include "Main.h"

#ifndef DATABASE_H_
#define DATABASE_H_

class DNDRandomEncounter;

// Stores all aspects of database including the connection to the database and getting the entries from the database
namespace Database {
	extern QSqlDatabase db;
	const QString databaseName = "RandomEncountersDB.db";

	// Connects database correctly or calls create database if not
	void ConnectDatabase();

	// Creates database if currently doesn't have one
	void CreateDatabase();

	// Drops encounters table to reset it
	void DropEncountersTable();

	// Drops encounter types table to reset it
	void DropEncounterTypesTable();

	// Creates encounter types table in database with correct data types
	void CreateEncounterTypesTable();
	 
	// Creates encounters table in database with correct data types
	void CreateEncountersTable();

	// Gets encounter types from database and stores it in vector
	void GetEncounterTypes(DNDRandomEncounter& randomEncounter);

	// Gets encounters from database and stores it in vector
	void GetEncounters();

	// Loads all data about a single encounter including image
	void GetSingleEncounter(int id);

	void InsertEncounterTypeToTable(QString& name, QByteArray& byteArray);

	void InsertSingleEncounterToTable(int encounterTypeID, QString& name, QByteArray& byteArray, QString& description);
}

#endif // !DATABASE_H_