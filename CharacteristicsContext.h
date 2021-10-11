#pragma once

#include <QString>

class CharacteristicsContext
{
public:
	CharacteristicsContext();
	void SetChannel(QString);
	void SetWeight(double weight);
	void SetBinTime(double binTime);
	void SetNumberOfPoints(int numberOfPoints);
	void AddNewXCoordinate(QString x);
	void AddNewYCoordinate(QString y);
	void SetFKMeasurement(int fk_measurement);
	void SetFKCharacteristicType(int fk_characteristic_type);
	void IncrementId();
	int GetId();

private:
	int id;
	QString channel;
	QString x;
	QString y;
	double weight;
	double binTime;
	int numberOfPoints;
	int fk_measurement;
	int fk_characteristic_type;

	QString stateFilePath = "characteristicstate.txt";
};
