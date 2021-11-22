#pragma once

#include "RawDataParser.h"

class SomeOtherDeviceParser : public RawDataParser
{
public:
	static SomeOtherDeviceParser& GetSomeOtherDeviceParserInstance();

	OperationStatusMessage* ParseRawDataFile(DbContext* dbContext, QString fileLink) override;

protected:
	SomeOtherDeviceParser() {};
	SomeOtherDeviceParser(const SomeOtherDeviceParser&) {}
};
