#pragma once

#include "DbContext.h"
#include "OperationStatusMessage.h"

class DbImporter
{

public:
    static DbImporter& GetDbImporterInstance();
    
    OperationStatusMessage* ImportToDatabase(QString fileLink);
    OperationStatusMessage* LinkParser(DbContext* dbContext, QString fileLink);
    QString ReadHeader(QString fileLink);

private:
    DbImporter() {};
    DbImporter(const DbImporter&) {};
};