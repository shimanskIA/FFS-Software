#pragma once

#include <QString>

#include "CharacteristicTypeContext.h"
#include "TableContext.h"

class CharacteristicsContext : public TableContext
{
public:
	CharacteristicsContext(QString stateFilePath);
	CharacteristicsContext(int id);
	CharacteristicsContext();
	void SetName(QString name);
	void SetChannel(QString channel);
	void SetWeight(double weight);
	void SetBinTime(double binTime);
	void SetX(QString x);
	void SetY(QString y);
	void SetNumberOfPoints(uint numberOfPoints);
	void AddNewXCoordinate(QString x);
	void AddNewYCoordinate(QString y);
	void SetFKMeasurement(int fk_measurement);
	void SetFKCharacteristicType(CharacteristicTypeContext* fk_characteristic_type);

	QString GetName();
	QString GetChannel();
	uint GetNumberOfPoints();
	QString GetX();
	QString GetY();
	double GetWeight();
	double GetBinTime();
	int GetFKCharacteristicType();
	int GetFKMeasurement();
	QString GetCharacteristicTypeName();

private:
	QString name = "";
	QString channel = "";
	QString x = "";
	QString y = "";
	double weight = 0.0;
	double binTime = 0.0;
	uint numberOfPoints = 0;
	int fk_measurement = 0;
	CharacteristicTypeContext* fk_characteristic_type = nullptr;
};
