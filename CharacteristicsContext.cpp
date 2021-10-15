#include "CharacteristicsContext.h"
#include "TextFileInteractionHelper.h"

CharacteristicsContext::CharacteristicsContext(QString stateFilePath) : TableContext(stateFilePath)
{

}

void CharacteristicsContext::SetChannel(QString channel)
{
	this->channel = channel;
}

void CharacteristicsContext::SetWeight(double weight)
{
	this->weight = weight;
}

void CharacteristicsContext::SetBinTime(double binTime)
{
	this->binTime = binTime;
}

void CharacteristicsContext::SetNumberOfPoints(int numberOfPoints)
{
	this->numberOfPoints = numberOfPoints;
}

void CharacteristicsContext::AddNewXCoordinate(QString x)
{
	this->x += x;
	this->x += " ";
}

void CharacteristicsContext::AddNewYCoordinate(QString y)
{
	this->y += y;
	this->y += " ";
}

void CharacteristicsContext::SetFKMeasurement(MeasurementContext* fk_measurement)
{
	this->fk_measurement = fk_measurement;
}

void CharacteristicsContext::SetFKCharacteristicType(CharacteristicTypeContext* fk_characteristic_type)
{
	this->fk_characteristic_type = fk_characteristic_type;
}

QString CharacteristicsContext::GetChannel()
{
	return this->channel;
}

int CharacteristicsContext::GetNumberOfPoints()
{
	return this->numberOfPoints;
}

QString CharacteristicsContext::GetX()
{
	return this->x;
}

QString CharacteristicsContext::GetY()
{
	return this->y;
}

double CharacteristicsContext::GetWeight()
{
	return this->weight;
}

double CharacteristicsContext::GetBinTime()
{
	return this->binTime;
}

int CharacteristicsContext::GetFKMeasurement()
{
	return this->fk_measurement->GetId();
}

int CharacteristicsContext::GetFKCharacteristicType()
{
	return this->fk_characteristic_type->GetId();
}


