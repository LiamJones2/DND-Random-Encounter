#pragma once
#include <QByteArray>
#include <QString>

#ifndef ENCOUNTER_H_
#define ENCOUNTER_H_

// Class that contains all encounters info 
class Encounter {
public:
    int ID;
    QString name;
    QString description;

    void SetID(int _ID);
    void SetName(QString _name);
    void SetDescription(QString _description);
};

// Used to store all the data of an individual encounter for use on the single encounter page
class SelectedEncounter : public Encounter {
public:
    QByteArray imageData;

    void SetImage(QByteArray _imageData);
};

// Stores the selected encounters info for single encounters page
namespace SelectedEncounterNamespace {
    extern SelectedEncounter selectedEncounter;
}

#endif // ENCOUNTER_H_