#pragma once

#include <QString>

#include "MeasurementContext.h";
#include "ParameterTableContext.h"

class MeasurementParameterContext : public ParameterTableContext
{
public:
	MeasurementParameterContext(QString stateFilePath);
	void SetFKMeasurement(MeasurementContext* fk_measurement);

	int GetFKMeasurement();

private:
	MeasurementContext* fk_measurement = nullptr;
};
