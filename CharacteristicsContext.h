#pragma once

#include <QString>

struct Point
{
	double x;
	double y;
};

class CharacteristicsContext
{
public:
	CharacteristicsContext();
	void SetChannel(QString);
	void SetPoint(Point point);
	void SetWeight(double weight);
	void SetBinTime(double binTime);
	void SetNumberOfPoints(int numberOfPoints);
	void SetFKMeasurement(int fk_measurement);
	void SetFKCharacteristicType(int fk_characteristic_type);
	void IncrementId();
	int GetId();

private:
	int id;
	QString channel;
	double x;
	double y;
	double weight;
	double binTime;
	int numberOfPoints;
	int fk_measurement;
	int fk_characteristic_type;

	QString configFilePath = "tablesstate.json";
};
