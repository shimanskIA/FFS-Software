#pragma once

#include <QString>

class CharacteristicTypeContext
{
public:
	CharacteristicTypeContext();
	void SetId(int id);
	void SetName(QString name);
	void SetDescription(QString description);
	void IncrementId();
	int GetId();
	QString GetName();
	QString GetDescription();

private:
	int id;
	QString name;
	QString description;

	QString stateFilePath = "characteristictypestate.txt";

};
