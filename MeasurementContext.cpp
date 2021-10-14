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