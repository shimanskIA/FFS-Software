#include "EquipmentContext.h"
#include "TextFileInteractionHelper.h"

EquipmentContext::EquipmentContext()
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(stateFilePath);
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
	TextFileInteractionHelper::WriteIdToTextFile(id, stateFilePath);
}

int EquipmentContext::GetId()
{
	return this->id;
}