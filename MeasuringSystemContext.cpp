#include "MeasuringSystemContext.h"
#include "JsonInteractionHelper.h"

MeasuringSystemContext::MeasuringSystemContext()
{
	this->id = JsonInteractionHelper::ReadItemFromJsonFile("measuring_system", configFilePath);
}

void MeasuringSystemContext::SetName(QString name)
{
	this->name = name;
}

void MeasuringSystemContext::IncrementId()
{
	JsonInteractionHelper::EditJsonFile("measuring_system", id + 1, configFilePath);
}

int MeasuringSystemContext::GetId()
{
	return this->id;
}