#pragma once

#include <QString>

#include "EquipmentContext.h";
#include "ParameterTableContext.h"

class EquipmentParameterContext : public ParameterTableContext
{
public:
	EquipmentParameterContext(QString stateFilePath);
	void SetFKEquipment(EquipmentContext* fk_equipment);

private:
	EquipmentContext* fk_equipment;

};
