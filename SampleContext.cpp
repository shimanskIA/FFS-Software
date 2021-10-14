#include "SampleContext.h"
#include "TextFileInteractionHelper.h"

SampleContext::SampleContext()
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(stateFilePath);
}

void SampleContext::SetId(int id)
{
	TextFileInteractionHelper::DeleteIdFromTextFile(this->GetId(), stateFilePath);
	this->id = id;
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
	TextFileInteractionHelper::WriteIdToTextFile(id, stateFilePath);
}

int SampleContext::GetId()
{
	return this->id;
}

QString SampleContext::GetName()
{
	return this->name;
}

QString SampleContext::GetDescription()
{
	return this->description;
}