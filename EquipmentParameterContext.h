#pragma once

#include <QString>

#include "EquipmentContext.h";

class EquipmentParameterContext
{
public:
	EquipmentParameterContext();
	void SetName(QString name);
	void SetValue(QString value);
	void SetFKEquipment(EquipmentContext* fk_equipment);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;
	QString value;
	EquipmentContext* fk_equipment;

	QString stateFilePath = "equipmentparameterstate.txt";
};
