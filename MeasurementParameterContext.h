#pragma once

#include <QString>

class MeasurementParameterContext
{
public:
	MeasurementParameterContext();
	void SetName(QString name);
	void SetValue(QString value);
	void SetFKMeasurement(int fk_measurement);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;
	QString value;
	int fk_measurement;

	QString configFilePath = "tablesstate.json";

};
