#pragma once

#include <QString>

#include "MeasurementContext.h";
#include "CharacteristicTypeContext.h";

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
	void SetFKMeasurement(MeasurementContext* fk_measurement);
	void SetFKCharacteristicType(CharacteristicTypeContext* fk_characteristic_type);
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
	MeasurementContext* fk_measurement;
	CharacteristicTypeContext* fk_characteristic_type;

	QString stateFilePath = "characteristicstate.txt";
};
