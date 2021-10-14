#pragma once

#include <QString>

#include "MeasurementContext.h";

class MeasurementParameterContext
{
public:
	MeasurementParameterContext();
	void SetName(QString name);
	void SetValue(QString value);
	void SetFKMeasurement(MeasurementContext* fk_measurement);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;
	QString value;
	MeasurementContext* fk_measurement;

	QString stateFilePath = "measurementparameterstate.txt";

};
