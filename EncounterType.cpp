#include "EncounterType.h"

// EncounterType
void EncounterType::SetID(int _ID) { encounterTypeID = _ID; }
void EncounterType::SetName(QString _name) { name = _name; }
void EncounterType::SetImage(QByteArray _imageData) { imageData = _imageData; }



// SelectedEncounterType
void SelectedEncounterType::SetEncounterTypeID(int _id) { viewEncounterTypeID = _id; }

SelectedEncounterType selectedEncounterType;