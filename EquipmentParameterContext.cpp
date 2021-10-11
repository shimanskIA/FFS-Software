#include "EquipmentParameterContext.h"
#include "TextFileInteractionHelper.h"

EquipmentParameterContext::EquipmentParameterContext()
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(stateFilePath);
}

void EquipmentParameterContext::SetName(QString name)
{
	this->name = name;
}

void EquipmentParameterContext::SetValue(QString value)
{
	this->value = value;
}

void EquipmentParameterContext::SetFKEquipment(int fk_equipment)
{
	this->fk_equipment = fk_equipment;
}

void EquipmentParameterContext::IncrementId()
{
	TextFileInteractionHelper::WriteIdToTextFile(id, stateFilePath);
}

int EquipmentParameterContext::GetId()
{
	return this->id;
}