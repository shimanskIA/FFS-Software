#include "MeasurementContext.h"
#include "JsonInteractionHelper.h"

MeasurementContext::MeasurementContext()
{
	this->id = JsonInteractionHelper::ReadItemFromJsonFile("measurement", configFilePath);
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

void MeasurementContext::SetNumberOfPoints(int numberOfPoints)
{
	this->numberOfPoints = numberOfPoints;
}

void MeasurementContext::SetBinTime(double binTime)
{
	this->binTime = binTime;
}

void MeasurementContext::SetFKSample(int fk_sample)
{
	this->fk_sample = fk_sample;
}

void MeasurementContext::SetFKMeasuringSystem(int fk_measuring_system)
{
	this->fk_measuring_system = fk_measuring_system;
}

void MeasurementContext::IncrementId()
{
	JsonInteractionHelper::EditJsonFile("measurement", id + 1, configFilePath);
}

int MeasurementContext::GetId()
{
	return this->id;
}