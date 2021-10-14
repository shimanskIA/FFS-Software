#include "CharacteristicTypeContext.h"
#include "TextFileInteractionHelper.h"

CharacteristicTypeContext::CharacteristicTypeContext()
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(stateFilePath);
}

void CharacteristicTypeContext::SetId(int id)
{
	TextFileInteractionHelper::DeleteIdFromTextFile(this->GetId(), stateFilePath);
	this->id = id;
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
	TextFileInteractionHelper::WriteIdToTextFile(id, stateFilePath);
}

int CharacteristicTypeContext::GetId()
{
	return this->id;
}

QString CharacteristicTypeContext::GetName()
{
	return this->name;
}

QString CharacteristicTypeContext::GetDescription()
{
	return this->description;
}