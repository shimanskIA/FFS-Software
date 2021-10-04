#include "MeasurementParameterContext.h"
#include "JsonInteractionHelper.h"

MeasurementParameterContext::MeasurementParameterContext()
{
	this->id = JsonInteractionHelper::ReadItemFromJsonFile("measurement_parameter", configFilePath);
}

void MeasurementParameterContext::SetName(QString name)
{
	this->name = name;
}

void MeasurementParameterContext::SetValue(QString value)
{
	this->value = value;
}

void MeasurementParameterContext::SetFKMeasurement(int fk_measurement)
{
	this->fk_measurement = fk_measurement;
}

void MeasurementParameterContext::IncrementId()
{
	JsonInteractionHelper::EditJsonFile("measurement_parameter", id + 1, configFilePath);
}

int MeasurementParameterContext::GetId()
{
	return this->id;
}