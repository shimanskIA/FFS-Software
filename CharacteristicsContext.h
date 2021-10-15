#pragma once

#include <QString>

#include "MeasurementContext.h";
#include "CharacteristicTypeContext.h";
#include "TableContext.h"

class CharacteristicsContext : public TableContext
{
public:
	CharacteristicsContext(QString stateFilePath);
	void SetChannel(QString);
	void SetWeight(double weight);
	void SetBinTime(double binTime);
	void SetNumberOfPoints(int numberOfPoints);
	void AddNewXCoordinate(QString x);
	void AddNewYCoordinate(QString y);
	void SetFKMeasurement(MeasurementContext* fk_measurement);
	void SetFKCharacteristicType(CharacteristicTypeContext* fk_characteristic_type);

	QString GetChannel();
	int GetNumberOfPoints();
	QString GetX();
	QString GetY();
	double GetWeight();
	double GetBinTime();
	int GetFKCharacteristicType();
	int GetFKMeasurement();

private:
	QString channel = "";
	QString x = "";
	QString y = "";
	double weight = 0.0;
	double binTime = 0.0;
	int numberOfPoints = 0;
	MeasurementContext* fk_measurement = nullptr;
	CharacteristicTypeContext* fk_characteristic_type = nullptr;
};
