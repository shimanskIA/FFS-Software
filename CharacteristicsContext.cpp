#include "CharacteristicsContext.h"
#include "JsonInteractionHelper.h"

CharacteristicsContext::CharacteristicsContext()
{
	this->id = JsonInteractionHelper::ReadItemFromJsonFile("characteristics", configFilePath);
}

void CharacteristicsContext::SetChannel(QString channel)
{
	this->channel = channel;
}

void CharacteristicsContext::SetPoint(Point point)
{
	this->x = point.x;
	this->y = point.y;
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

void CharacteristicsContext::SetFKMeasurement(int fk_measurement)
{
	this->fk_measurement = fk_measurement;
}

void CharacteristicsContext::SetFKCharacteristicType(int fk_characteristic_type)
{
	this->fk_characteristic_type = fk_characteristic_type;
}

void CharacteristicsContext::IncrementId()
{
	JsonInteractionHelper::EditJsonFile("characteristics", id + 1, configFilePath);
}

int CharacteristicsContext::GetId()
{
	return this->id;
}

