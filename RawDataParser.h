#pragma once

#include <QString>
#include <QObject>

#include "DbContext.h"
#include "OperationStatusMessage.h"

class RawDataParser
{
public:
	virtual OperationStatusMessage* ParseRawDataFile(DbContext* dbContext, QString fileLink) = 0;

protected:
	RawDataParser() {};
};
