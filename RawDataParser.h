#pragma once

#include <QString>
#include "DbContext.h"

class RawDataParser
{
public:
	RawDataParser(QString fileLink);
	RawDataParser();
	void SetFileLink(QString fileLink);
	void ParseRawDataFile(DbContext dbContext);
	void CZConfoCor2Parser(DbContext dbContext);
	void CZConfoCor1Parser(DbContext dbContext);
	QString FindParsingType();

private:
	QString fileLink;
};
