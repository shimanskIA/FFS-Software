#include "EquipmentParameterContext.h"
#include "TextFileInteractionHelper.h"

EquipmentParameterContext::EquipmentParameterContext(QString stateFilePath) : ParameterTableContext(stateFilePath)
{

}

void EquipmentParameterContext::SetFKEquipment(EquipmentContext* fk_equipment)
{
	this->fk_equipment = fk_equipment;
}

