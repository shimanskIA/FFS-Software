#pragma once

#include <QString>

#include "ParameterTableContext.h"

class EquipmentParameterContext : public ParameterTableContext
{
public:
	EquipmentParameterContext(QString stateFilePath);
	EquipmentParameterContext();
	void SetFKEquipment(int fk_equipment);

	int GetFKEquipment();

private:
	int fk_equipment = 0;
};
