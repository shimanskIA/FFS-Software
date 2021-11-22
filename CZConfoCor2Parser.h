#pragma once

#include "ConfoCorParser.h"

class CZConfoCor2Parser : public ConfoCorParser
{
public:
	static CZConfoCor2Parser& GetCZConfoCor2ParserInstance();

	OperationStatusMessage* ParseRawDataFile(DbContext* dbContext, QString fileLink) override;
	void CascadeEquipmentParametersRead(QString line, bool& flag, QString endLine, EquipmentContext*& equipmentItem, DbContext* dbContext) override;
	void CreateNewEquipmentItem(QString name, bool& flag, EquipmentContext*& equipmentItem) override;
	void Bind(MeasuringSystemContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext) override;
	QStringList GetCoordinates(QString line) override;

private:
	CZConfoCor2Parser();
	CZConfoCor2Parser(const CZConfoCor2Parser&) {}
};
