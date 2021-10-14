#include "MeasurementParameterContext.h"
#include "TextFileInteractionHelper.h"

MeasurementParameterContext::MeasurementParameterContext()
{
	this->id = TextFileInteractionHelper::ReadIdFromTextFile(stateFilePath);
}

void MeasurementParameterContext::SetName(QString name)
{
	this->name = name;
}

void MeasurementParameterContext::SetValue(QString value)
{
	this->value = value;
}

void MeasurementParameterContext::SetFKMeasurement(MeasurementContext* fk_measurement)
{
	this->fk_measurement = fk_measurement;
}

void MeasurementParameterContext::IncrementId()
{
	TextFileInteractionHelper::WriteIdToTextFile(id, stateFilePath);
}

int MeasurementParameterContext::GetId()
{
	return this->id;
}