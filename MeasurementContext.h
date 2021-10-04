#pragma once

#include <QString>

class MeasurementContext
{
public:
	MeasurementContext();
	void SetName(QString name);
	void SetDateTime(QString dateTime);
	void SetFileLink(QString fileLink);
	void SetNumberOfPoints(int numberOfPoints);
	void SetBinTime(double binTime);
	void SetFKSample(int fk_sample);
	void SetFKMeasuringSystem(int fk_measuring_system);
	void IncrementId();
	int GetId();

private:
	int id;
	QString name;
	QString dateTime;
	QString fileLink;
	int numberOfPoints;
	double binTime;
	int fk_sample;
	int fk_measuring_system;

	QString configFilePath = "tablesstate.json";

};
