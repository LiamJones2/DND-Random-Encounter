#pragma once
#include <QByteArray>
#include <QString>

#ifndef EncounterType_H_
#define EncounterType_H_

/*
    Sets the encounter types objects from the database
    Database has three columns:
        ID 
        name
        imageData

    Each Encounter type is stored in an instance of this class
*/
class EncounterType {
public:
    int encounterTypeID;
    QString name;
    QByteArray imageData;

    void SetID(int _ID);
    void SetName(QString _name);
    void SetImage(QByteArray _imageData);
};



/*
    SelectedEncounterType holds the information of what EncounterType the user wants to see
    And then when we go to the encounters page we use the id to query the database
*/
struct SelectedEncounterType {
public:
    int viewEncounterTypeID;

    void SetEncounterTypeID(int _id);
};

extern SelectedEncounterType selectedEncounterType;

#endif // !EncounterType_H_