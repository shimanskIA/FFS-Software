#pragma once

#include "DbContext.h"
#include "RawDataParser.h"

class DbImporter
{

public:
    DbImporter(DbContext* dbContext, RawDataParser* rawDataParser);
    ~DbImporter();
    void ImportToDatabase();

private:
    DbContext* dbContext;
    RawDataParser* rawDataParser;
};