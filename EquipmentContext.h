#pragma once

#include <QString>

#include "TableContext.h"

class EquipmentContext : public TableContext
{
public:
	EquipmentContext(QString stateFilePath);
	void SetName(QString name);
	void SetDescription(QString description);

private:
	QString name;
	QString description;
};
