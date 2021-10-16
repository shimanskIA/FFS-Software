#include "EquipmentParameterContext.h"
#include "TextFileInteractionHelper.h"

EquipmentParameterContext::EquipmentParameterContext(QString stateFilePath) : ParameterTableContext(stateFilePath)
{

}

EquipmentParameterContext::EquipmentParameterContext() : ParameterTableContext()
{

}

void EquipmentParameterContext::SetFKEquipment(int fk_equipment)
{
	this->fk_equipment = fk_equipment;
}

int EquipmentParameterContext::GetFKEquipment()
{
	return this->fk_equipment;
}

