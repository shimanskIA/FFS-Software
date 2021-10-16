#pragma once

#include <QString>
#include "DbContext.h"

class RawDataParser
{
public:
	RawDataParser(QString fileLink);
	RawDataParser();
	~RawDataParser();
	void SetFileLink(QString fileLink);
	void ParseRawDataFile(DbContext* dbContext);
	void CZConfoCor2Parser(DbContext* dbContext);
	void CZConfoCor1Parser(DbContext* dbContext);
	void SomeOtherDeviceParser(DbContext* dbContext);
	void CascadeEquipmentParametersRead(QString line, bool& flag, QString endLine, EquipmentContext*& equipmentItem, DbContext* dbContext);
	void CreateNewEquipmentItem(QString name, bool& flag, EquipmentContext*& equipmentItem);
	void Bind(MeasurementContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext);
	QStringList GetCoordinates(QString line);
	QString ReadHeader();

private:
	QString fileLink;
	int dataSetNumber;
	int channelNumber;
	int correlationNumber;
	bool measurementReadFlag;
	bool measureParametersReadFlag;
	bool laserParametersReadFlag;
	bool pinholeParametersReadFlag;
	bool attenuatorPowerParametersReadFlag;
	bool detectorParametersReadFlag;
	bool attenuatorParametersReadFlag;
	bool beamSplitterParametersReadFlag;
	bool collimatorParametersReadFlag;
	bool sampleCarrierReadFlag;
	bool sampleDistributionReadFlag;
	bool characteristicReadFlag;
	bool numberOfPointsReadFlag;

	const QString sampleStatePath = "samplestate.txt";
	const QString measurementStatePath = "measurementstate.txt";
	const QString equipmentStatePath = "equipmentstate.txt";
	const QString measurementParametersStatePath = "measurementparameterstate.txt";
	const QString equipmentParameterStatePath = "equipmentparameterstate.txt";
	const QString characteristicStatePath = "characteristicstate.txt";
	const QString characteristicTypeStatePath = "characteristictypestate.txt";
};
