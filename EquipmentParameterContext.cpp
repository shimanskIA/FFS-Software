#include "EquipmentParameterContext.h"
#include "JsonInteractionHelper.h"

EquipmentParameterContext::EquipmentParameterContext()
{
	this->id = JsonInteractionHelper::ReadItemFromJsonFile("equipment_parameter", configFilePath);
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
	JsonInteractionHelper::EditJsonFile("equipment_parameter", id + 1, configFilePath);
}

int EquipmentParameterContext::GetId()
{
	return this->id;
}