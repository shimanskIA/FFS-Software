#include "DbImporter.h"
#include "DbWriter.h"

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
	DbWriter* dbWriter = new DbWriter();
	dbWriter->AddToDatabase(dbContext);
}