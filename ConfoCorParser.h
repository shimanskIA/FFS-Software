#pragma once

#include "RawDataParser.h"

class ConfoCorParser : public RawDataParser
{
public:
	virtual void CascadeEquipmentParametersRead(QString line, bool& flag, QString endLine, EquipmentContext*& equipmentItem, DbContext* dbContext) = 0;
	virtual void CreateNewEquipmentItem(QString name, bool& flag, EquipmentContext*& equipmentItem) = 0;
	virtual void Bind(MeasuringSystemContext* measuringSystem, EquipmentContext*& equipmentItem, DbContext* dbContext) = 0;
	virtual QStringList GetCoordinates(QString line) = 0;
protected:
	ConfoCorParser() : RawDataParser() {};
};
