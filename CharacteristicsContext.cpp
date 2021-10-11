#include "CharacteristicsContext.h"
#include "TextFileInteractionHelper.h"

CharacteristicsContext::CharacteristicsContext()
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(stateFilePath);
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
	TextFileInteractionHelper::WriteIdToTextFile(id, stateFilePath);
}

int CharacteristicsContext::GetId()
{
	return this->id;
}

