#pragma once

#include "ConfoCorParser.h"

class CZConfoCor1Parser : public ConfoCorParser
{
public:
	static CZConfoCor1Parser& GetCZConfoCor1ParserInstance();

	OperationStatusMessage* ParseRawDataFile(DbContext* dbContext, QString fileLink) override;
	void CascadeEquipmentParametersRead(QString line, bool& flag, QString endLine, EquipmentContext*& equipmentItem, DbContext* dbContext) override;
	void CreateNewEquipmentItem(QString name, bool& flag, EquipmentContext*& equipmentItem) override;
	void Bind(MeasuringSystemContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext) override;
	QStringList GetCoordinates(QString line) override;

private:
	CZConfoCor1Parser();
	CZConfoCor1Parser(const CZConfoCor1Parser&) {}
};