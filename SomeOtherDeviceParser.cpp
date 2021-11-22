#include "SomeOtherDeviceParser.h"

SomeOtherDeviceParser& SomeOtherDeviceParser::GetSomeOtherDeviceParserInstance()
{
	static SomeOtherDeviceParser* someOtherDeviceParserInstance = 0;

	if (someOtherDeviceParserInstance == 0)
	{
		someOtherDeviceParserInstance = new SomeOtherDeviceParser();
	}

	return *someOtherDeviceParserInstance;
}

OperationStatusMessage* SomeOtherDeviceParser::ParseRawDataFile(DbContext* dbContext, QString fileLink)
{
	OperationStatusMessage* errorStatusMessage = new OperationStatusMessage(false);
	errorStatusMessage->SetOperationMessage("Parser for this type of device is not implemented yet.");
	return errorStatusMessage;
}