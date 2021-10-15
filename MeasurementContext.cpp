#include "MeasurementContext.h"
#include "TextFileInteractionHelper.h"

MeasurementContext::MeasurementContext(QString stateFilePath) : TableContext(stateFilePath)
{

}

void MeasurementContext::SetName(QString name)
{
	this->name = name;
}

void MeasurementContext::SetDateTime(QString dateTime)
{
	this->dateTime = dateTime;
}

void MeasurementContext::SetFileLink(QString fileLink)
{
	this->fileLink = fileLink;
}

void MeasurementContext::SetNumberOfChannels(int numberOfChannels)
{
	this->numberOfChannels = numberOfChannels;
}

void MeasurementContext::SetRepeatCount(int repeatCount)
{
	this->repeatCount = repeatCount;
}

void MeasurementContext::SetKineticsCount(int kineticsCount)
{
	this->kineticsCount = kineticsCount;
}

void MeasurementContext::SetNumberPositions(int numberPositions)
{
	this->numberPositions = numberPositions;
}

void MeasurementContext::SetFKSample(SampleContext* fk_sample)
{
	this->fk_sample = fk_sample;
}

QString MeasurementContext::GetName()
{
	return this->name;
}

QString MeasurementContext::GetDateTime() 
{
	return this->dateTime;
}

QString MeasurementContext::GetFileLink()
{
	return this->fileLink;
}

int MeasurementContext::GetNumberOfChannels()
{
	return this->numberOfChannels;
}

int MeasurementContext::GetNumberPositions()
{
	return this->numberPositions;
}

int MeasurementContext::GetKineticsCount()
{
	return this->kineticsCount;
}

int MeasurementContext::GetRepeatCount()
{
	return this->repeatCount;
}

int MeasurementContext::GetFKSample()
{
	return this->fk_sample->GetId();
}