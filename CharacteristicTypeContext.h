#pragma once

#include "TableContext.h"

#include <QString>

class CharacteristicTypeContext : public TableContext
{
public:
	CharacteristicTypeContext(QString stateFilePath);
	void SetName(QString name);
	void SetDescription(QString description);

	QString GetName();
	QString GetDescription();

private:
	QString name = "";
	QString description = "";
};
