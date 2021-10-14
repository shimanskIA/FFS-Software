#include "SampleContext.h"
#include "TextFileInteractionHelper.h"

SampleContext::SampleContext(QString stateFilePath) : TableContext(stateFilePath)
{

}

void SampleContext::SetName(QString name)
{
	this->name = name;
}

void SampleContext::SetDescription(QString description)
{
	this->description = description;
}


QString SampleContext::GetName()
{
	return this->name;
}

QString SampleContext::GetDescription()
{
	return this->description;
}