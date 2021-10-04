#pragma once

#include <QString>

class EquipmentParameterContext
{
public:
	EquipmentParameterContext();
	void SetName(QString name);
	void SetValue(QString value);
	void SetFKEquipment(int fk_equipment);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;
	QString value;
	int fk_equipment;

	QString configFilePath = "tablesstate.json";
};
