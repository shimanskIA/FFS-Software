#pragma once

#include <QString>

#include "TableContext.h"

class ParameterTableContext : public TableContext
{
public:
	ParameterTableContext(int id);

	void SetName(QString name);
	void SetValue(QString value);

	QString GetName();
	QString GetValue();

protected:
	ParameterTableContext(QString stateFilePath);
	ParameterTableContext();
	QString name = "";
	QString value = "";
};
