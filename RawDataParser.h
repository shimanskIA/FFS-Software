#pragma once

#include <QString>
#include "DbContext.h"

class RawDataParser
{
public:
	RawDataParser(QString fileLink);
	RawDataParser();
	~RawDataParser();
	void SetFileLink(QString fileLink);
	void ParseRawDataFile(DbContext* dbContext);
	void CZConfoCor2Parser(DbContext* dbContext);
	void CZConfoCor1Parser(DbContext* dbContext);
	void SomeOtherDeviceParser(DbContext* dbContext);
	QString ReadHeader();

private:
	QString fileLink;
	int dataSetNumber;
	bool measurementReadFlag;
	bool measureParametersReadFlag;

	QString sampleTypes[7] = {"DNA", "RhGr", "Rh6G", "Cy5", "Cy4", "CFP", "YFP"};
};
