#pragma once

#include "TableContext.h"

#include <QString>

class SampleContext : public TableContext
{
public:
	SampleContext(QString stateFilePath);
	SampleContext(int id);
	SampleContext();
	void SetName(QString name);
	void SetDescription(QString description);

	QString GetName();
	QString GetDescription();

private:
	QString name = "";
	QString description = "";
};
