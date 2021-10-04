#include "CharacteristicTypeContext.h"
#include "JsonInteractionHelper.h"

CharacteristicTypeContext::CharacteristicTypeContext()
{
	this->id = JsonInteractionHelper::ReadItemFromJsonFile("characteristic_type", configFilePath);
}

void CharacteristicTypeContext::SetName(QString name)
{
	this->name = name;
}

void CharacteristicTypeContext::SetDescription(QString description)
{
	this->description = description;
}

void CharacteristicTypeContext::IncrementId()
{
	JsonInteractionHelper::EditJsonFile("characteristic_type", id + 1, configFilePath);
}

int CharacteristicTypeContext::GetId()
{
	return this->id;
}