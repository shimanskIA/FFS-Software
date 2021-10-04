#include "EquipmentContext.h"
#include "JsonInteractionHelper.h"

EquipmentContext::EquipmentContext()
{
	this->id = JsonInteractionHelper::ReadItemFromJsonFile("equipment", configFilePath);
}

void EquipmentContext::SetName(QString name)
{
	this->name = name;
}

void EquipmentContext::SetDescription(QString description)
{
	this->description = description;
}

void EquipmentContext::IncrementId()
{
	JsonInteractionHelper::EditJsonFile("equipment", id + 1, configFilePath);
}

int EquipmentContext::GetId()
{
	return this->id;
}