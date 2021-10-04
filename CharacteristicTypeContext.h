#pragma once

#include <QString>

class CharacteristicTypeContext
{
public:
	CharacteristicTypeContext();
	void SetName(QString name);
	void SetDescription(QString description);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;
	QString description;

	QString configFilePath = "tablesstate.json";

};
