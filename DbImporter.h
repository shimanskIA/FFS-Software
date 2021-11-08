#pragma once

#include "DbContext.h"
#include "RawDataParser.h"
#include "OperationStatusMessage.h"

class DbImporter
{

public:
    DbImporter(DbContext* dbContext, RawDataParser* rawDataParser);
    ~DbImporter();
    OperationStatusMessage* ImportToDatabase();

private:
    DbContext* dbContext;
    RawDataParser* rawDataParser;
};