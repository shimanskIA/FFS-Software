#include "SampleContext.h"
#include "JsonInteractionHelper.h"

SampleContext::SampleContext()
{
	this->id = JsonInteractionHelper::ReadItemFromJsonFile("sample", configFilePath);
}

void SampleContext::SetName(QString name)
{
	this->name = name;
}

void SampleContext::SetDescription(QString description)
{
	this->description = description;
}

void SampleContext::IncrementId()
{
	JsonInteractionHelper::EditJsonFile("sample", id + 1, configFilePath);
}

int SampleContext::GetId()
{
	return this->id;
}