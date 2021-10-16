#pragma once

#include <QString>

#include "ParameterTableContext.h"

class MeasurementParameterContext : public ParameterTableContext
{
public:
	MeasurementParameterContext(QString stateFilePath);
	MeasurementParameterContext();
	void SetFKMeasurement(int fk_measurement);

	int GetFKMeasurement();

private:
	int fk_measurement = 0;
};
