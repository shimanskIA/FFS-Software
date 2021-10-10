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
	void Bind(MeasuringSystemContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext);
	QString ReadHeader();

private:
	QString fileLink;
	int dataSetNumber;
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

	QString sampleTypes[7] = {"DNA", "RhGr", "Rh6G", "Cy5", "Cy4", "CFP", "YFP"};
};
