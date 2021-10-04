#include "FFSDatabaseInterfaceService.h"
#include "DbImporter.h"

void FFSDatabaseInterfaceService::ImportRequestReceiver(QString fileLink)
{
	DbImporter *dbImporter = new DbImporter(*(new DbContext()), *(new RawDataParser(fileLink)));
	dbImporter->ImportToDatabase();
}