#include "DbImporter.h"

DbImporter::DbImporter(DbContext *dbContext, RawDataParser *rawDataParser)
{
	this->dbContext = dbContext;
	this->rawDataParser = rawDataParser;
}

DbImporter::~DbImporter()
{
	delete dbContext;
	delete rawDataParser;
}

void DbImporter::ImportToDatabase()
{
	rawDataParser->ParseRawDataFile(dbContext);
}