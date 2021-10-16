#include "MeasurementParameterContext.h"
#include "TextFileInteractionHelper.h"

MeasurementParameterContext::MeasurementParameterContext(QString stateFilePath) : ParameterTableContext(stateFilePath)
{

}

MeasurementParameterContext::MeasurementParameterContext() : ParameterTableContext()
{

}

void MeasurementParameterContext::SetFKMeasurement(int fk_measurement)
{
	this->fk_measurement = fk_measurement;
}

int MeasurementParameterContext::GetFKMeasurement()
{
	return fk_measurement;
}