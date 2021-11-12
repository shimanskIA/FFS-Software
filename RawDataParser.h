#pragma once

#include <QString>
#include <QMap>
#include <QObject>

#include "DbContext.h"
#include "OperationStatusMessage.h"

class RawDataParser : public QObject
{
public:
	RawDataParser(QString fileLink);
	RawDataParser();
	~RawDataParser();

	void SetFileLink(QString fileLink);
	OperationStatusMessage* ParseRawDataFile(DbContext* dbContext);
	OperationStatusMessage* CZConfoCor2Parser(DbContext* dbContext);
	OperationStatusMessage* CZConfoCor1Parser(DbContext* dbContext);
	OperationStatusMessage* SomeOtherDeviceParser(DbContext* dbContext);
	void CascadeEquipmentParametersRead(QString line, bool& flag, QString endLine, EquipmentContext*& equipmentItem, DbContext* dbContext);
	void CreateNewEquipmentItem(QString name, bool& flag, EquipmentContext*& equipmentItem);
	void Bind(MeasuringSystemContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext);
	QStringList GetCoordinates(QString line);
	QString ReadHeader();

private slots:
	void createMeasuringSystem(QMap<QString, QString> credentials);

private:
	QString fileLink;
	MeasuringSystemContext* measuringSystem = nullptr;
	//QMap<QString, QString> measuringSystemCredentials;
	int dataSetNumber = 0;
	int channelNumber = 0;
	int correlationNumber = 0;
	bool measurementReadFlag = false;
	bool measureParametersReadFlag = false;
	bool laserParametersReadFlag = false;
	bool pinholeParametersReadFlag = false;
	bool attenuatorPowerParametersReadFlag = false;
	bool attenuatorParametersReadFlag = false;
	bool beamSplitterParametersReadFlag = false;
	bool collimatorParametersReadFlag = false;
	bool characteristicReadFlag = false;
	bool numberOfPointsReadFlag = false;
	bool firstDataSetReadFlag = true;
};
