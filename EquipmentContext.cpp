#include "EquipmentContext.h"
#include "TextFileInteractionHelper.h"

EquipmentContext::EquipmentContext(QString stateFilePath) : TableContext(stateFilePath)
{

}

void EquipmentContext::SetName(QString name)
{
	this->name = name;
}

void EquipmentContext::SetDescription(QString description)
{
	this->description = description;
}