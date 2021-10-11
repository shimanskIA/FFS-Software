#include "SampleContext.h"
#include "TextFileInteractionHelper.h"

SampleContext::SampleContext()
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(stateFilePath);
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