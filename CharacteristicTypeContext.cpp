#include "CharacteristicTypeContext.h"
#include "TextFileInteractionHelper.h"

CharacteristicTypeContext::CharacteristicTypeContext(QString stateFilePath) : TableContext(stateFilePath)
{

}


void CharacteristicTypeContext::SetName(QString name)
{
	this->name = name;
}

void CharacteristicTypeContext::SetDescription(QString description)
{
	this->description = description;
}

QString CharacteristicTypeContext::GetName()
{
	return this->name;
}

QString CharacteristicTypeContext::GetDescription()
{
	return this->description;
}