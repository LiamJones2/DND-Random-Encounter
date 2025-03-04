#include "Encounter.h"

// Encounter
void Encounter::SetID(int _ID) { ID = _ID; }
void Encounter::SetName(QString _name) { name = _name; }
void Encounter::SetDescription(QString _description) { description = _description; }


// SelectedEncounter
void SelectedEncounter::SetImage(QByteArray _imageData) { imageData = _imageData; }

namespace SelectedEncounterNamespace {
	SelectedEncounter selectedEncounter;
}