#include "MeasurementParameterContext.h"
#include "TextFileInteractionHelper.h"

MeasurementParameterContext::MeasurementParameterContext(QString stateFilePath) : ParameterTableContext(stateFilePath)
{

}

void MeasurementParameterContext::SetFKMeasurement(MeasurementContext* fk_measurement)
{
	this->fk_measurement = fk_measurement;
}